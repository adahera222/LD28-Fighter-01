/* 
 * File:   Explosion.h
 * Author: leon
 *
 * Created on December 15, 2013, 7:45 AM
 */

#ifndef EXPLOSION_H
#define	EXPLOSION_H

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <vector>

class Explosion {
public:

    Explosion() {
    }
    Explosion(int x, int y);

    static std::vector<Explosion> all;
    static SDL_Surface *animation;
    static Mix_Chunk *sfx;

    void update();
    void draw(SDL_Surface *screen);

    bool operator == (const Explosion* object) {return object == this; }
    
private:
    int x;
    int y;
    int framerate;
    int frameCooldown;
    int frame;
};

#endif	/* EXPLOSION_H */

