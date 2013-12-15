/* 
 * File:   Explosion.cpp
 * Author: leon
 * 
 * Created on December 15, 2013, 7:45 AM
 */

#include "Explosion.h"
#include <algorithm>
#include <ios>

std::vector<Explosion> Explosion::all;
SDL_Surface *Explosion::animation;
Mix_Chunk *Explosion::sfx;

Explosion::Explosion(int x, int y) {
    this->x = x;
    this->y = y;
    this->frame = 0;
    this->framerate = 5;
    this->frameCooldown = framerate;
    Mix_PlayChannel(-1, sfx, 0);
}

void Explosion::update() {
    if (--frameCooldown <= 0) {
        frameCooldown = framerate;
        frame++;
    }

    if (frame == 6) {
        std::vector<Explosion>::iterator it = std::find(all.begin(), all.end(), this);
        all.erase(it);
    }

}

void Explosion::draw(SDL_Surface *screen) {
    SDL_Rect srcrect;
    srcrect.x = frame % 3 * 32;
    srcrect.y = frame / 3 * 32;
    srcrect.w = 32;
    srcrect.h = 32;

    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = 32;
    dstrect.h = 32;

    SDL_BlitSurface(animation, &srcrect, screen, &dstrect);
}
