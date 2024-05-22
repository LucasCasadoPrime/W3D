#ifndef MAP_HPP
#define MAP_HPP

#include "IMap.hpp"

class Map : public IMap {
public:
    Map(std::string path, int indexFloorTexture, int indexCeilingTexture, std::vector<Props> props) {
        this->height = getHeightFromText(path);
        this->width = getWidthFromText(path);
        this->map = getMapFromText(path, height, width);
        this->playerStartPosX = getPlayerStartPosXFromText(path);
        this->playerStartPosY = getPlayerStartPosYFromText(path);
        this->floorTexture = indexFloorTexture;
        this->ceilingTexture = indexCeilingTexture;
        this->props = props;
    }

    Map() {}

    // Getters
    int getHeight() const {
        return height;
    }

    int getWidth() const {
        return width;
    }

    int getPlayerStartPosX() const {
        return playerStartPosX;
    }

    int getPlayerStartPosY() const {
        return playerStartPosY;
    }

    int** getMap() const {
        return map;
    }

    int getIndexFloorTexture() const {
        return floorTexture;
    }

    int getIndexCeilingTexture() const {
        return ceilingTexture;
    }

    std::vector<Props> getProps() const {
        return props;
    }

    // Setters
    void setHeight(int height) {
        this->height = height;
    }

    void setWidth(int width) {
        this->width = width;
    }

    void setPlayerStartPosX(int playerStartPosX) {
        this->playerStartPosX = playerStartPosX;
    }

    void setPlayerStartPosY(int playerStartPosY) {
        this->playerStartPosY = playerStartPosY;
    }

    void setMap(int** map) {
        this->map = map;
    }

    void setIndexFloorTexture(int indexFloorTexture) {
        this->floorTexture = indexFloorTexture;
    }

    void setIndexCeilingTexture(int indexCeilingTexture) {
        this->ceilingTexture = indexCeilingTexture;
    }

    void setProps(std::vector<Props> props) {
        this->props = props;
    }

    // Methods
    int** getMapFromText(std::string path, int height, int width) {
        std::ifstream file(path);
        std::string line;
        int** map = new int*[height];
        for(int i = 0; i < height; i++) {
            map[i] = new int[width];
        }

        std::getline(file, line);
        std::getline(file, line);

        int i = 0;
        while(std::getline(file, line) && i < height) {
            for(int j = 0; j < width; j++) {
                map[i][j] = line[j] - '0';
            }
            i++;
        }

        return map;
    }

    int getHeightFromText(std::string path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Échec de l'ouverture du fichier : " << path << std::endl;
            return -1;
        }

        std::string line;
        std::getline(file, line);
        std::getline(file, line);

        int height = 0;
        while (std::getline(file, line)) {
            height++;
        }

        file.close();
        return height;
    }

    int getWidthFromText(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Échec de l'ouverture du fichier : " << path << std::endl;
            return -1;
        }

        std::string line;
        std::getline(file, line);
        std::getline(file, line);

        if (std::getline(file, line)) {
            int width = line.size();
            file.close();
            return width;
        } else {
            std::cerr << "Échec de la lecture de la troisième ligne du fichier : " << path << std::endl;
            file.close();
            return -1;
        }
    }

    int getPlayerStartPosXFromText(std::string path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Échec de l'ouverture du fichier : " << path << std::endl;
            return -1;
        }

        std::string line;
        int playerStartPosX = 0;

        if (std::getline(file, line)) {
            std::string delimiter = "=";
            size_t pos = 0;
            std::string token;
            while ((pos = line.find(delimiter)) != std::string::npos) {
                token = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
            }
            playerStartPosX = std::stoi(line);
        } else {
            std::cerr << "Échec de la lecture de la première ligne du fichier : " << path << std::endl;
            file.close();
            return -1;
        }

        file.close();
        return playerStartPosX;
    }

        int getPlayerStartPosYFromText(std::string path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Échec de l'ouverture du fichier : " << path << std::endl;
            return -1;
        }

        std::string line;
        int playerStartPosX = 0;

        std::getline(file, line);

        if (std::getline(file, line)) {
            std::string delimiter = "=";
            size_t pos = 0;
            std::string token;
            while ((pos = line.find(delimiter)) != std::string::npos) {
                token = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
            }
            playerStartPosX = std::stoi(line);
        } else {
            std::cerr << "Échec de la lecture de la première ligne du fichier : " << path << std::endl;
            file.close();
            return -1;
        }

        file.close();
        return playerStartPosX;
    }

};

#endif // MAP_HPP