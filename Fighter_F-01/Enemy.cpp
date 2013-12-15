/* 
 * File:   Enemy.cpp
 * Author: leon
 * 
 * Created on December 14, 2013, 6:07 AM
 */

#include "constants.h"
#include "Enemy.h"
#include "SDL/SDL.h"
#include "FloatRect.h"
#include "calculations.h"
#include "Bullet.h"
#include <vector>

std::vector<Enemy> Enemy::all;
int Enemy::nextId = 0;

Enemy::Enemy(int x, int y, SDL_Surface *sprite, levelSettings ls) {
    this->box.x = x;
    this->box.y = y;
    this->sprite = sprite;
    this->box.w = sprite->w;
    this->box.h = sprite->h;
    this->level = ls;
    this->fireCooldown = rand() % level.firerate;
    this->motionChangeCooldown = level.agility;
    this->id = nextId++;
    //update();
}

void Enemy::update() {

    float dist = level.speed * level.agility;

    // <editor-fold defaultstate="collapsed" desc="motion change">
    if (motionChangeCooldown <= 0) {

        int possibilities[4];
        possibilities[UP] = true;
        possibilities[DOWN] = true;
        possibilities[LEFT] = true;
        possibilities[RIGHT] = true;
        for (int i = 0; i < all.size(); i++) {

            // <editor-fold defaultstate="collapsed" desc="border collision check">
            //Check for borders
            if (box.y < dist + level.offset) possibilities[UP] = false;
            if (box.y + box.h > level.space - dist + level.offset) possibilities[DOWN] = false;
            if (box.x < dist) possibilities[LEFT] = false;
            if (box.x + box.w > GAME_WIDTH - dist) possibilities[RIGHT] = false;

            // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="enemy collision check">
            //Check for enemies
            Enemy e = all[i];
            float edist = e.level.speed * e.level.agility;
            FloatRect ezone;
            ezone.x = e.box.x - 2 * edist;
            ezone.w = e.box.w + 4 * edist;
            ezone.y = e.box.y - 2 * edist;
            ezone.h = e.box.h + 2 * edist;

            if (e.id != id && check_collision(box, ezone)) {
                if (box.y > e.box.y + e.box.h && box.y - dist < ezone.y + ezone.h) possibilities[UP] = false;
                if (box.y + box.h < e.box.y && box.y + box.h + dist > ezone.y) possibilities[DOWN] = false;
                if (box.x > e.box.x + e.box.w && box.x - dist < ezone.x + ezone.w) possibilities[LEFT] = false;
                if (box.x + box.w < e.box.x && box.x + box.w + dist > ezone.x) possibilities[RIGHT] = false;
            }

            // <editor-fold defaultstate="collapsed" desc="old enemy collision check">
            /*
                        // check vertically for collision with other enemies
                        if (e.id != id && !(e.box.x > box.x + box.w) && !(e.box.x + e.box.w < box.x)) {
                            if (e.box.y + e.box.h + dist > box.y - dist) possibilities[UP] = false;
                            if (e.box.y - edist < box.y + box.h + dist) possibilities[DOWN] = false;
                        }
                        // check horizontally for collision with other enemies
                        if (e.id != id && !(e.box.y > box.y + box.h) && !(e.box.y + e.box.h < box.y)) {
                            if (e.box.x + e.box.w + dist > box.x - dist) possibilities[LEFT] = false;
                            if (e.box.x - edist < box.x + box.w + dist) possibilities[RIGHT] = false;
                        }
             */
            // </editor-fold>

            // </editor-fold>

        }
        std::vector<int> possRand;
        for (int i = 0; i < 4; i++) {
            if (possibilities[i]) possRand.push_back(i);
        }
        if (possRand.size() == 0) direction = NOP;
        else {
            direction = possRand[rand() % possRand.size()];
        }

        motionChangeCooldown = level.agility;
    }// </editor-fold>

    if (fireCooldown <= 0) {
        Bullet b(box.x + box.w/2, box.y+box.h, Bullet::DOWN);
        Bullet::allEnemy.push_back(b);
        fireCooldown = level.firerate;
    }
    
    if (direction == UP) box.y -= level.speed;
    if (direction == DOWN) box.y += level.speed;
    if (direction == LEFT) box.x -= level.speed;
    if (direction == RIGHT) box.x += level.speed;

    level.offset += level.progression;
    motionChangeCooldown--;
    fireCooldown--;
}
