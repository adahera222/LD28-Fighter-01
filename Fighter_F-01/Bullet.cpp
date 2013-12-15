/* 
 * File:   Bullet.cpp
 * Author: leon
 * 
 * Created on December 14, 2013, 5:24 AM
 */

#include "Bullet.h"

std::vector<Bullet> Bullet::allFighter;
std::vector<Bullet> Bullet::allEnemy;
SDL_Surface *Bullet::sprite;
Mix_Chunk *Bullet::sfx;

Bullet::Bullet(int x, int y, int dir) {
    this->box.x = x;
    this->box.y = y;
    this->box.w = sprite->w;
    this->box.h = sprite->h;
    this->speed = 10;
    this->direction = dir;
    Mix_PlayChannel(-1, sfx, 0);
}

void Bullet::update() {
    if (direction == DOWN) box.y += speed;
    else if (direction == UP) box.y -= speed;
}
