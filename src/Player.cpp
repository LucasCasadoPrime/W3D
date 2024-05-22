#include "../include/Player.hpp"
#include <iostream>

#define screenWidth 640
#define screenHeight 480

Player::Player(double x, double y, double directionX, double directionY, double planeX, double planeY)
    : posX(x), posY(y), dirX(directionX), dirY(directionY), planeX(planeX), planeY(planeY), 
      weapon(Weapon::PISTOL), currentFrame(0), isShooting(false), lastFrameChangeTime(std::chrono::steady_clock::now()) {

    // Load textures for all weapons
    loadWeaponTextures(Weapon::SHOTGUN, "./assets/sprites/weapons/shotgun/shotgun", 5);
    
    // Load sounds for all weapons
    loadWeaponSounds(Weapon::SHOTGUN, "./assets/sounds/shotgun.wav");

    // Set initial sprite for each weapon
    for (auto& pair : weaponTextures) {
        Weapon w = pair.first;
        if (!pair.second.empty()) {
            weaponSprites[w].setTexture(pair.second[0]);
            weaponSprites[w].setScale(3.0f, 3.0f);
            weaponSprites[w].setPosition(screenWidth / 2 - weaponSprites[w].getGlobalBounds().width / 2, screenHeight - weaponSprites[w].getGlobalBounds().height);
        }
    }
}

void Player::loadWeaponTextures(Weapon weapon, const std::string& basePath, int frameCount) {
    sf::Color transparentColor(152, 0, 136);
    std::vector<sf::Texture>& textures = weaponTextures[weapon];
    
    for (int i = 1; i <= frameCount; ++i) {
        sf::Image image;
        if (!image.loadFromFile(basePath + std::to_string(i) + ".bmp")) {
            std::cerr << "Erreur de chargement de l'image " << basePath + std::to_string(i) + ".bmp" << std::endl;
        } else {
            image.createMaskFromColor(transparentColor);
            sf::Texture texture;
            texture.loadFromImage(image);
            textures.push_back(texture);
        }
    }
}

void Player::loadWeaponSounds(Weapon weapon, const std::string& basePath) {
    sf::SoundBuffer& soundBuffer = weaponSoundBuffers[weapon];
    if (!soundBuffer.loadFromFile(basePath)) {
        std::cerr << "Erreur de chargement du son " << basePath << std::endl;
    }

}

sf::Sprite Player::getCurrentWeaponSprite() const {
    auto it = weaponSprites.find(weapon);
    if (it != weaponSprites.end()) {
        return it->second;
    } else {
        std::cerr << "Error: Weapon sprite not found!" << std::endl;
        return sf::Sprite();
    }
}

void Player::shoot() {
    if (!isShooting) {
        auto it = weaponTextures.find(weapon);
        auto itSound = weaponSoundBuffers.find(weapon);
        if (it != weaponTextures.end() && itSound != weaponSoundBuffers.end() && !it->second.empty()) {
            isShooting = true;
            currentFrame = 0;
            weaponSprites[weapon].setTexture(it->second[currentFrame]);
            weaponSprites[weapon].setScale(4.0f, 4.0f);
            weaponSprites[weapon].setPosition(screenWidth / 2 - weaponSprites[weapon].getGlobalBounds().width / 2, screenHeight - weaponSprites[weapon].getGlobalBounds().height);
            weaponSound.setBuffer(itSound->second);
            weaponSound.play();
        }
    }
}



void Player::updateAnimation() {
    if (isShooting) {
        auto currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> frameTime = currentTime - lastFrameChangeTime;
        if (frameTime.count() > 0.1) {
            lastFrameChangeTime = currentTime;
            currentFrame++;
            auto it = weaponTextures.find(weapon);
            if (it != weaponTextures.end() && currentFrame < it->second.size()) {
                weaponSprites[weapon].setTexture(it->second[currentFrame]);
            } else {
                // Animation finished
                currentFrame = 0;
                isShooting = false;
                if (it != weaponTextures.end() && !it->second.empty()) {
                    weaponSprites[weapon].setTexture(it->second[currentFrame]); // Reset to the first frame
                }
            }
        }
    }
}

void Player::movements(Level& level, std::clock_t oldTime) {
    std::clock_t newTime = std::clock();
    double frameTime = double(newTime - oldTime) / CLOCKS_PER_SEC;  
    oldTime = newTime;

    double moveSpeed = frameTime * 5.0;
    double rotSpeed = frameTime * 3.0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        if (level.map.getMap()[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
        if (level.map.getMap()[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if (level.map.getMap()[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
        if (level.map.getMap()[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        double oldDirX = dirX;
        dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
        dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
        planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        double oldDirX = dirX;
        dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
        dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
        planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        if (level.map.getMap()[int(posX + planeX * moveSpeed)][int(posY)] == false) posX += planeX * moveSpeed;
        if (level.map.getMap()[int(posX)][int(posY + planeY * moveSpeed)] == false) posY += planeY * moveSpeed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (level.map.getMap()[int(posX - planeX * moveSpeed)][int(posY)] == false) posX -= planeX * moveSpeed;
        if (level.map.getMap()[int(posX)][int(posY - planeY * moveSpeed)] == false) posY -= planeY * moveSpeed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        shoot();
    }

    updateAnimation();
}
