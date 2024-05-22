#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Level.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <map>
#include <chrono>

enum class Weapon {
    PISTOL,
    SHOTGUN,
    MACHINEGUN
};

class Player {
public:
    Player(double x, double y, double directionX, double directionY, double planeX, double planeY);

    // Getters
    double getPosX() const { return posX; }
    double getPosY() const { return posY; }
    double getDirX() const { return dirX; }
    double getDirY() const { return dirY; }
    double getPlaneX() const { return planeX; }
    double getPlaneY() const { return planeY; }
    Weapon getWeapon() const { return weapon; }
    sf::Sprite getCurrentWeaponSprite() const;
    unsigned int getLife() const { return life; }
    unsigned int getAmmo() const { return ammo; }   
    unsigned int getMaxAmmo() const { return maxAmmo; }
    sf::Sound& getWeaponSound() { return weaponSound; }

    // Setters
    void setPosX(double posX) { this->posX = posX; }
    void setPosY(double posY) { this->posY = posY; }
    void setDirX(double dirX) { this->dirX = dirX; }
    void setDirY(double dirY) { this->dirY = dirY; }
    void setPlaneX(double planeX) { this->planeX = planeX; }
    void setPlaneY(double planeY) { this->planeY = planeY; }
    void setWeapon(Weapon weapon) { this->weapon = weapon; }
    void setLife(unsigned int life) { this->life = life; }
    void setAmmo(unsigned int ammo) { this->ammo = ammo; }
    void setMaxAmmo(unsigned int maxAmmo) { this->maxAmmo = maxAmmo; }
    void setWeaponSound(sf::Sound weaponSound) { this->weaponSound = weaponSound; }

    // Methods
    void movements(Level& level, std::clock_t oldTime);
    void shoot();
    void updateAnimation();

    double posX, posY;      // Position of the player
    double dirX, dirY;      // Direction vector of the player
    double planeX, planeY;  // Camera plane of the player

private:
    void loadWeaponTextures(Weapon weapon, const std::string& basePath, int frameCount);
    void loadWeaponSounds(Weapon weapon, const std::string& basePath);

    // stats
    unsigned int life;
    unsigned int ammo;
    unsigned int maxAmmo;

    //weapon
    Weapon weapon;
    std::map<Weapon, std::vector<sf::Texture>> weaponTextures;
    std::map<Weapon, sf::Sprite> weaponSprites;
    std::map<Weapon, sf::SoundBuffer> weaponSoundBuffers;
    sf::Sound weaponSound;
    int currentFrame;
    bool isShooting;
    std::chrono::time_point<std::chrono::steady_clock> lastFrameChangeTime;
};

#endif // PLAYER_HPP
