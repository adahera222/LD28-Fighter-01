/* 
 * File:   Fighter.cpp
 * Author: leon
 * 
 * Created on December 14, 2013, 4:56 AM
 */

#include "Fighter.h"
#include "Bullet.h"
#include "constants.h"

Fighter::Fighter(int x, int y, SDL_Surface *sprite) {
    this->box.x = x;
    this->box.y = y;
    this->sprite = sprite;
    this->box.w = sprite->w;
    this->box.h = sprite->h;
    this->current_move = UP;
    this->speed = 5;
    this->firerate = 30;
    this->keyPressed = 0;
    this->min_y = GAME_HEIGHT - GAME_HEIGHT / 4;
    this->fired = false;
    skip[UP] = 0;
    skip[DOWN] = 0;
    skip[LEFT] = 0;
    skip[RIGHT] = 0;
    skip[SHOOT] = 0;
    roll_next_move();
    roll_next_move();
}

int Fighter::get_current() {
    return current_move;
}

int Fighter::get_next() {
    return next_move;
}

void Fighter::update(Uint8 *keystate) {
    if (keystate[SDLK_SPACE]) {
        if (current_move == UP && box.y > min_y) {
            box.y -= speed;
        }
        if (current_move == DOWN && box.y + box.h < GAME_HEIGHT) {
            box.y += speed;
        }
        if (current_move == LEFT && box.x > 0) {
            box.x -= speed;
        }
        if (current_move == RIGHT && box.x + box.w < GAME_WIDTH) {
            box.x += speed;
        }
        if (current_move == SHOOT) {
            if (!fired) {
                Bullet b(box.x + box.w / 2, box.y, Bullet::UP);
                Bullet::allFighter.push_back(b);
                fired = true;
            }
        }
        keyPressed = true;
    } else {
        if (keyPressed) {
            roll_next_move();
        }
        fired = false;
        keyPressed = false;
    }
}

void Fighter::roll_next_move() {
    int temp_move = rand() % MAX;

    if (skip[temp_move] > 0) {
        skip[temp_move]--;
        roll_next_move();
    } else {
        current_move = next_move;
        next_move = temp_move;
        skip[temp_move]++;
    }

    //    next_move = rand() % SHOOT;
    //    if (!(rand() % 3)) next_move = SHOOT;
    //    
    //    if (++current_move >= MAX) {
    //        current_move = UP;
    //    }
}
