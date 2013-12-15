/* 
 * File:   Bullet.h
 * Author: leon
 *
 * Created on December 14, 2013, 5:24 AM
 */

#ifndef BULLET_H
#define	BULLET_H

#include "SDL/SDL.h"
#include "FloatRect.h"
#include "SDL/SDL_mixer.h"
#include <vector>

class Bullet {
public:

    Bullet() {
    }
    Bullet(int x, int y, int dir);

    void update();

    static std::vector<Bullet> allFighter;
    static std::vector<Bullet> allEnemy;
    static SDL_Surface *sprite;
    static Mix_Chunk *sfx;
    
    FloatRect box;
    float speed;
    int direction;

    enum direction {
        UP = 0,
        DOWN = 1
    };

private:

};

#endif	/* BULLET_H */

