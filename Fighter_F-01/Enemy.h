/* 
 * File:   Enemy.h
 * Author: leon
 *
 * Created on December 14, 2013, 6:07 AM
 */

#ifndef ENEMY_H
#define	ENEMY_H

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "FloatRect.h"
#include <vector>

struct levelSettings {
    float speed;
    int firerate;
    int agility;
    float offset;
    float progression;
    int space;
    int enemy_count;
};

class Enemy {
public:

    Enemy() {
    }
    Enemy(int x, int y, SDL_Surface *sprite, levelSettings ls);

    levelSettings level;
    static std::vector<Enemy> all;
    static int nextId;
    FloatRect box;
    int id;

    SDL_Surface *sprite;
    
    void update();

private:
    int direction;
    int motionChangeCooldown;
    int fireCooldown;

    enum direction {
        UP = 0,
        DOWN = 1,
        LEFT = 2,
        RIGHT = 3,
        NOP = 4
    };
};

#endif	/* ENEMY_H */

