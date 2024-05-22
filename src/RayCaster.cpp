#include "../include/RayCaster.hpp"

void RayCaster::sortSprites(int* order, double* dist, int amount) {
    std::vector<std::pair<double, int>> sprites(amount);
    for (int i = 0; i < amount; ++i) {
        sprites[i] = std::make_pair(dist[i], order[i]);
    }

    std::sort(sprites.begin(), sprites.end(), [](const std::pair<double, int>& a, const std::pair<double, int>& b) {
        return a.first > b.first;
    });

    for (int i = 0; i < amount; ++i) {
        dist[i] = sprites[i].first;
        order[i] = sprites[i].second;
    }
}

void RayCaster::castWalls(sf::RenderWindow& window, Level& level, Player& player) {
    const int screenWidth = level.getScreenWidth();
    const int screenHeight = level.getScreenHeight();
    const int texWidth = level.texWidth;
    const int texHeight = level.texHeight;

    for (int x = 0; x < screenWidth; ++x) {
        double cameraX = 2 * x / static_cast<double>(screenWidth) - 1;
        double rayDirX = player.dirX + player.planeX * cameraX;
        double rayDirY = player.dirY + player.planeY * cameraX;

        int mapX = static_cast<int>(player.posX);
        int mapY = static_cast<int>(player.posY);

        double sideDistX;
        double sideDistY;

        double deltaDistX = std::abs(1 / rayDirX);
        double deltaDistY = std::abs(1 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (player.posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player.posX) * deltaDistX;
        }

        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (player.posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player.posY) * deltaDistY;
        }

        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            if (level.map.getMap()[mapX][mapY] > 0) {
                hit = 1;
            }
        }

        if (side == 0) {
            perpWallDist = (mapX - player.posX + (1 - stepX) / 2) / rayDirX;
        } else {
            perpWallDist = (mapY - player.posY + (1 - stepY) / 2) / rayDirY;
        }

        int lineHeight = static_cast<int>(screenHeight / perpWallDist);

        int drawStart = std::max(-lineHeight / 2 + screenHeight / 2, 0);
        int drawEnd = std::min(lineHeight / 2 + screenHeight / 2, screenHeight - 1);

        int texNum = level.map.getMap()[mapX][mapY] - 1;

        double wallX;
        if (side == 0) {
            wallX = player.posY + perpWallDist * rayDirY;
        } else {
            wallX = player.posX + perpWallDist * rayDirX;
        }
        wallX -= std::floor(wallX);

        int texX = static_cast<int>(wallX * texWidth);
        if (side == 0 && rayDirX > 0) {
            texX = texWidth - texX - 1;
        }

        if (side == 1 && rayDirY < 0) {
            texX = texWidth - texX - 1;
        }

        for (int y = drawStart; y < drawEnd; ++y) {
            int d = y * 256 - screenHeight * 128 + lineHeight * 128;
            int texY = ((d * texHeight) / lineHeight) / 256;
            int color = level.textures[texNum][texWidth * texY + texX];
            level.buffer[x][y] = color;
        }

        level.ZBuffer[x] = perpWallDist;
    }
}

void RayCaster::castFloorAndCeiling(sf::RenderWindow& window, Player& player, Level& level) {
    // FLOOR CASTING
    for (int y = 0; y < level.getScreenHeight(); ++y) {
        double rayDirX0 = player.dirX - player.planeX;
        double rayDirY0 = player.dirY - player.planeY;
        double rayDirX1 = player.dirX + player.planeX;
        double rayDirY1 = player.dirY + player.planeY;

        int p = y - level.getScreenHeight() / 2;
        double posZ = 0.5 * level.getScreenHeight();

        double rowDistance = posZ / p;

        double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / level.getScreenWidth();
        double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / level.getScreenWidth();

        double floorX = player.posX + rowDistance * rayDirX0;
        double floorY = player.posY + rowDistance * rayDirY0;

        for (int x = 0; x < level.getScreenWidth(); ++x) {
            int cellX = static_cast<int>(floorX);
            int cellY = static_cast<int>(floorY);

            int tx = static_cast<int>(level.texWidth * (floorX - cellX)) & (level.texWidth - 1);
            int ty = static_cast<int>(level.texHeight * (floorY - cellY)) & (level.texHeight - 1);

            floorX += floorStepX;
            floorY += floorStepY;

            int color = (level.textures[level.map.getIndexCeilingTexture()][level.texWidth * ty + tx]);
            level.buffer[x][level.getScreenHeight() - y - 1] = color;

            color = level.textures[level.map.getIndexFloorTexture()][level.texWidth * ty + tx];
            level.buffer[x][y] = color;
        }
    }
}

void RayCaster::updateSpriteDistances(Level& level, Player& player) {
    int numSprites = level.map.getProps().size();
    for (int i = 0; i < numSprites; ++i) {
        level.spriteOrder[i] = i;
        level.spriteDistance[i] = (player.posX - level.map.getProps()[i].x) * (player.posX - level.map.getProps()[i].x) + 
                                  (player.posY - level.map.getProps()[i].y) * (player.posY - level.map.getProps()[i].y);
    }
    sortSprites(level.spriteOrder, level.spriteDistance, numSprites);
}

void RayCaster::transformSprite(const Player& player, const Props& sprite, double& transformX, double& transformY, int& spriteScreenX, Level& level) {
    double spriteX = sprite.x - player.posX;
    double spriteY = sprite.y - player.posY;

    double invDet = 1.0 / (player.planeX * player.dirY - player.dirX * player.planeY);
    transformX = invDet * (player.dirY * spriteX - player.dirX * spriteY);
    transformY = invDet * (-player.planeY * spriteX + player.planeX * spriteY);

    spriteScreenX = static_cast<int>((level.getScreenWidth() / 2) * (1 + transformX / transformY));
}

void RayCaster::drawSprite(int spriteScreenX, double transformY, const Props& sprite, Level& level) {
    const int screenHeight = level.getScreenHeight();
    const int screenWidth = level.getScreenWidth();
    const int texWidth = level.texWidth;
    const int texHeight = level.texHeight;

    int spriteHeight = std::abs(static_cast<int>(screenHeight / transformY));
    int drawStartY = std::max(-spriteHeight / 2 + screenHeight / 2, 0);
    int drawEndY = std::min(spriteHeight / 2 + screenHeight / 2, screenHeight - 1);

    int spriteWidth = std::abs(static_cast<int>(screenHeight / transformY));
    int drawStartX = std::max(-spriteWidth / 2 + spriteScreenX, 0);
    int drawEndX = std::min(spriteWidth / 2 + spriteScreenX, screenWidth - 1);

    for (int stripe = drawStartX; stripe < drawEndX; ++stripe) {
        int texX = static_cast<int>(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;

        if (transformY > 0 && stripe > 0 && stripe < screenWidth && transformY < level.ZBuffer[stripe]) {
            for (int y = drawStartY; y < drawEndY; ++y) {
                int d = y * 256 - screenHeight * 128 + spriteHeight * 128;
                int texY = ((d * texHeight) / spriteHeight) / 256;
                int color = level.textures[sprite.texture][texWidth * texY + texX];

                if ((color) != 255) {
                    level.buffer[stripe][y] = color;
                }
            }
        }
    }
}

void RayCaster::castSprites(sf::RenderWindow& window, Level& level, Player& player) {
    updateSpriteDistances(level, player);

    for (int i = 0; i < level.map.getProps().size(); ++i) {
        Props sprite = level.map.getProps()[level.spriteOrder[i]]; // Use a copy instead of a reference
        double transformX, transformY;
        int spriteScreenX;

        transformSprite(player, sprite, transformX, transformY, spriteScreenX, level);
        drawSprite(spriteScreenX, transformY, sprite, level);
    }
}

void RayCaster::castRays(sf::RenderWindow& window, Level& level, Player& player) {
    std::clock_t currentTime = std::clock();

    int order[level.map.getProps().size()];
    double dist[level.map.getProps().size()];
    for (int i = 0; i < level.map.getProps().size(); ++i) {
        order[i] = i;
        dist[i] = 0;
    }

    castFloorAndCeiling(window, player, level);

    castWalls(window, level, player);

    castSprites(window, level, player);

    player.movements(level, currentTime);
}
