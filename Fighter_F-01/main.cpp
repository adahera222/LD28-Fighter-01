/* 
 * File:   main.cpp
 * Author: leon
 *
 * Created on December 14, 2013, 3:45 AM
 */

#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <iostream>
#include "Fighter.h"
#include "Bullet.h"
#include "Enemy.h"
#include "FloatRect.h"
#include "constants.h"
#include "calculations.h"
#include "Explosion.h"
#include <vector>
#include <sstream>

#define STATE_STARTMENU 0
#define STATE_GAME 1
#define STATE_ENDGAME 2

using namespace std;


SDL_Surface *screen = NULL;
SDL_Surface *fighter_sprite = NULL;
SDL_Surface *bullet_sprite = NULL;
SDL_Surface *enemy_sprite = NULL;

SDL_Surface *score_background = NULL;
SDL_Surface *game_background = NULL;
SDL_Surface *welcome_message = NULL;
SDL_Surface *victory_message = NULL;
SDL_Surface *defeat_message = NULL;

SDL_Surface *slot_up = NULL;
SDL_Surface *slot_down = NULL;
SDL_Surface *slot_left = NULL;
SDL_Surface *slot_right = NULL;
SDL_Surface *slot_fire = NULL;
SDL_Surface *score_panel = NULL;
SDL_Surface *score_digits = NULL;

SDL_Surface *explosion_ani = NULL;

TTF_Font *font = NULL;

Mix_Chunk *explosion_sfx = NULL;
Mix_Chunk *fire_sfx = NULL;

SDL_Event event;
SDL_Rect scoreBoard;
SDL_Color textColor = {255, 255, 255};
Fighter f01;

vector<levelSettings> levels;

int enemyOffset;
int background_offset = 0;
int score = 0;
int level = 0;

int game_state = STATE_STARTMENU;
bool victory = false;

SDL_Surface *load_image(std::string filename) {
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load(filename.c_str());
    if (loadedImage != NULL) {
        optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
        SDL_FreeSurface(loadedImage);
    } else {
        cerr << "Error loading image!" << endl;
    }
    return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination) {
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(source, NULL, destination, &offset);
}

void loadLevel(int level) {
    if (level >= levels.size()) {
        victory = true;
        game_state = STATE_ENDGAME;
    } else {
        for (int i = 0; i < levels[level].enemy_count; i++) {
            int max_y = GAME_HEIGHT / 5;
            Enemy e(rand() % (GAME_WIDTH - enemy_sprite->w), rand() % (levels[level].space - enemy_sprite->h) + levels[level].offset, enemy_sprite, levels[level]);
            Enemy::all.push_back(e);
        }
    }
}

void generateLevels() {
    levelSettings ls;

    ls.speed = 1;
    ls.firerate = 2400;
    ls.agility = 20;
    ls.offset = 0;
    ls.progression = 0.05;
    ls.space = GAME_HEIGHT / 5;
    ls.enemy_count = 2;
    levels.push_back(ls);

    ls.speed = 1;
    ls.firerate = 600;
    ls.agility = 20;
    ls.offset = 0;
    ls.progression = 0.05;
    ls.space = GAME_HEIGHT / 5;
    ls.enemy_count = 4;
    levels.push_back(ls);

    ls.speed = 1;
    ls.firerate = 2400;
    ls.agility = 20;
    ls.offset = 0;
    ls.progression = 0.5;
    ls.space = GAME_HEIGHT / 5;
    ls.enemy_count = 2;
    levels.push_back(ls);

    ls.speed = 1;
    ls.firerate = 1800;
    ls.agility = 20;
    ls.offset = 0;
    ls.progression = 0.05;
    ls.space = GAME_HEIGHT / 5;
    ls.enemy_count = 10;
    levels.push_back(ls);

    ls.speed = 5;
    ls.firerate = 60;
    ls.agility = 5;
    ls.offset = 0;
    ls.progression = 0.05;
    ls.space = GAME_HEIGHT / 5;
    ls.enemy_count = 1;
    levels.push_back(ls);
}

bool init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;
    if (TTF_Init() == -1) return false;
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) return false;
    srand(SDL_GetTicks());
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if (screen == NULL) return false;
    SDL_WM_SetCaption("Fighter 01", NULL);
    scoreBoard.x = GAME_WIDTH;
    scoreBoard.y = 0;
    scoreBoard.w = SCREEN_WIDTH - GAME_WIDTH;
    scoreBoard.h = SCREEN_HEIGHT;

    // Load sprites
    fighter_sprite = load_image("data/Fighter 01.png");
    bullet_sprite = load_image("data/bullet.png");
    enemy_sprite = load_image("data/Enemy.png");
    score_background = load_image("data/score-background.png");
    game_background = load_image("data/game-background.png");
    welcome_message = load_image("data/welcome.png");
    victory_message = load_image("data/victory.png");
    defeat_message = load_image("data/defeat.png");
    slot_up = load_image("data/moveup.png");
    slot_down = load_image("data/movedown.png");
    slot_left = load_image("data/moveleft.png");
    slot_right = load_image("data/moveright.png");
    slot_fire = load_image("data/shootshot.png");
    score_panel = load_image("data/score-panel.png");
    explosion_ani = load_image("data/explosion.png");

    // Load Fonts
    font = TTF_OpenFont("data/DIGITALDREAM.ttf", 37);

    // Load SFX
    explosion_sfx = Mix_LoadWAV("data/explosion.wav");
    fire_sfx = Mix_LoadWAV("data/fire.wav");

    Bullet::sprite = bullet_sprite;
    Bullet::sfx = fire_sfx;
    Explosion::animation = explosion_ani;
    Explosion::sfx = explosion_sfx;

    f01 = Fighter((GAME_WIDTH - fighter_sprite->w) / 2, GAME_HEIGHT - fighter_sprite->h, fighter_sprite);
    generateLevels();
    loadLevel(level);
    return true;
}

void clean_up() {
    SDL_FreeSurface(fighter_sprite);
    SDL_FreeSurface(bullet_sprite);
    SDL_FreeSurface(enemy_sprite);
    SDL_FreeSurface(score_background);
    SDL_FreeSurface(game_background);
    SDL_FreeSurface(welcome_message);
    SDL_FreeSurface(victory_message);
    SDL_FreeSurface(defeat_message);

    SDL_FreeSurface(slot_up);
    SDL_FreeSurface(slot_down);
    SDL_FreeSurface(slot_left);
    SDL_FreeSurface(slot_right);
    SDL_FreeSurface(slot_fire);
    SDL_FreeSurface(score_panel);
    SDL_FreeSurface(score_digits);

    SDL_FreeSurface(explosion_ani);

    Mix_FreeChunk(explosion_sfx);
    Mix_FreeChunk(fire_sfx);
    Mix_CloseAudio();

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_Quit;
}

/*
 * 
 */
int main(int argc, char** argv) {
    if (!init()) return 1;
    bool running = true;
    while (running) {
        if (game_state == STATE_STARTMENU) {
            Enemy::all.clear();
            Bullet::allEnemy.clear();
            Bullet::allFighter.clear();
            score = 0;
            level = 0;
            loadLevel(level);
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) running = false;
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                    game_state = STATE_GAME;
                }
            }
            apply_surface(0, background_offset, game_background, screen);
            apply_surface(GAME_WIDTH, 0, score_background, screen);
            apply_surface(GAME_WIDTH / 4, GAME_HEIGHT / 3, welcome_message, screen);
            SDL_Flip(screen);
        } else if (game_state == STATE_GAME) {
            unsigned int frameStart = SDL_GetTicks();
            // Event handling
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) running = false;
            }

            Uint8 *keystate = SDL_GetKeyState(NULL);
            f01.update(keystate);

            for (int i = 0; i < Enemy::all.size(); i++) {
                Enemy::all[i].update();
                if (check_collision(Enemy::all[i].box, f01.box)
                        || Enemy::all[i].box.y + Enemy::all[i].box.h > GAME_HEIGHT) {
                    victory = false;
                    game_state = STATE_ENDGAME;
                }
            }

            for (int i = 0; i < Bullet::allFighter.size(); i++) {
                Bullet::allFighter[i].update();
                if (Bullet::allFighter[i].box.y <= 0) {
                    Bullet::allFighter.erase(Bullet::allFighter.begin() + i);
                    i = 0;
                }
                for (int j = 0; j < Enemy::all.size(); j++) {
                    if (check_collision(Bullet::allFighter[i].box, Enemy::all[j].box)) {
                        // Enemy hit
                        Bullet::allFighter.erase(Bullet::allFighter.begin() + i);
                        Explosion e(Enemy::all[j].box.x, Enemy::all[j].box.y);
                        Explosion::all.push_back(e);
                        Enemy::all.erase(Enemy::all.begin() + j);
                        score++;
                        i -= 1;
                        j = 0;
                        if (Enemy::all.size() == 0) {
                            loadLevel(++level);
                        }
                        continue;
                    }
                }
            }

            for (int i = 0; i < Bullet::allEnemy.size(); i++) {
                Bullet::allEnemy[i].update();
                if (Bullet::allEnemy[i].box.y + Bullet::allEnemy[i].box.h >= GAME_HEIGHT) {
                    Bullet::allEnemy.erase(Bullet::allEnemy.begin() + i);
                    i = 0;
                }
                if (check_collision(Bullet::allEnemy[i].box, f01.box)) {
                    // Player hit
                    Explosion e(f01.box.x, f01.box.y);
                    Explosion::all.push_back(e);
                    Bullet::allEnemy.erase(Bullet::allEnemy.begin() + i);
                    i -= 1;
                    victory = false;
                    game_state = STATE_ENDGAME;
                }
            }

            for (int i = 0; i < Explosion::all.size(); i++) {
                Explosion::all[i].update();
            }

            background_offset += f01.speed;
            if (background_offset >= game_background->h) {
                background_offset = 0;
            }

            // Rendering
            //SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
            apply_surface(0, background_offset, game_background, screen);
            apply_surface(0, background_offset - game_background->h, game_background, screen);
            apply_surface(GAME_WIDTH, 0, score_background, screen);
            SDL_Surface *current_slot;
            SDL_Surface *next_slot;
            if (f01.get_current() == Fighter::UP) current_slot = slot_up;
            if (f01.get_current() == Fighter::DOWN) current_slot = slot_down;
            if (f01.get_current() == Fighter::LEFT) current_slot = slot_left;
            if (f01.get_current() == Fighter::RIGHT) current_slot = slot_right;
            if (f01.get_current() == Fighter::SHOOT) current_slot = slot_fire;
            int current_slot_x = GAME_WIDTH + (SCREEN_WIDTH - GAME_WIDTH) / 4 - current_slot->w / 2;

            if (f01.get_next() == Fighter::UP) next_slot = slot_up;
            if (f01.get_next() == Fighter::DOWN) next_slot = slot_down;
            if (f01.get_next() == Fighter::LEFT) next_slot = slot_left;
            if (f01.get_next() == Fighter::RIGHT) next_slot = slot_right;
            if (f01.get_next() == Fighter::SHOOT) next_slot = slot_fire;
            int next_slot_x = GAME_WIDTH + (SCREEN_WIDTH - GAME_WIDTH)*3 / 4 - next_slot->w / 2;

            apply_surface(current_slot_x, 16, current_slot, screen);
            apply_surface(next_slot_x, 16, next_slot, screen);

            stringstream score_ss;
            score_ss << score / 1000 % 10;
            score_ss << score / 100 % 10;
            score_ss << score / 10 % 10;
            score_ss << score % 10;
            score_digits = TTF_RenderText_Solid(font, score_ss.str().c_str(), textColor);
            apply_surface(current_slot_x, 112, score_panel, screen);
            apply_surface(current_slot_x + 10, 122, score_digits, screen);


            apply_surface(f01.box.x, f01.box.y, f01.sprite, screen);
            for (int i = 0; i < Explosion::all.size(); i++) {
                Explosion::all[i].draw(screen);
            }
            for (int i = 0; i < Enemy::all.size(); i++) {
                apply_surface(Enemy::all[i].box.x, Enemy::all[i].box.y, Enemy::all[i].sprite, screen);
            }
            for (int i = 0; i < Bullet::allFighter.size(); i++) {
                apply_surface(Bullet::allFighter[i].box.x, Bullet::allFighter[i].box.y, Bullet::allFighter[i].sprite, screen);
            }
            for (int i = 0; i < Bullet::allEnemy.size(); i++) {
                apply_surface(Bullet::allEnemy[i].box.x, Bullet::allEnemy[i].box.y, Bullet::allEnemy[i].sprite, screen);
            }
            SDL_Flip(screen);

            unsigned int frameDuration = SDL_GetTicks() - frameStart;

            if (frameDuration < FRAME_RATE) {
                SDL_Delay(FRAME_RATE - frameDuration);
            }
        } else if (game_state == STATE_ENDGAME) {
            apply_surface(0, background_offset, game_background, screen);
            apply_surface(GAME_WIDTH, 0, score_background, screen);
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) running = false;
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                    game_state = STATE_STARTMENU;
                }
            }
            if (victory)
                apply_surface(GAME_WIDTH / 4, GAME_HEIGHT / 3, victory_message, screen);
            else
                apply_surface(GAME_WIDTH / 4, GAME_HEIGHT / 3, defeat_message, screen);

            SDL_Flip(screen);
        }
    }
    clean_up();

    return 0;
}

