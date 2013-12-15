/* 
 * File:   Fighter.h
 * Author: leon
 *
 * Created on December 14, 2013, 4:56 AM
 */

#ifndef FIGHTER_H
#define	FIGHTER_H

#include "SDL/SDL.h"
#include "FloatRect.h"

class Fighter {
public:

    Fighter() {
    }
    Fighter(int x, int y, SDL_Surface *sprite);

    void update(Uint8 *keystate);

    bool keyPressed;
    FloatRect box;
    int current_move;
    float speed;
    float firerate;

    SDL_Surface *sprite;

    enum states {
        UP = 0,
        DOWN = 1,
        LEFT = 2,
        RIGHT = 3,
        SHOOT = 4,
        MAX = 5
    };
    
    int get_current();
    int get_next();
private:
    void roll_next_move();
    int skip[MAX];
    bool fired;
    int next_move;
    int min_y;
};

#endif	/* FIGHTER_H */

