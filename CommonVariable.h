#ifndef COMMONVARIABLE_H
#define COMMONVARIABLE_H
#include <SDL2/SDL.h>
#include <cmath>
#include <vector>
#include <map>
#include <fstream>
#include <math.h>
#include <cmath>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Event event;
extern const int MIDDLE_X;
extern const int MIDDLE_Y;
extern int times_player_want_to_playagain;

extern const double MAIN_OBJECT_SCALE;
extern const double CHICKEN_OBJECT_SCALE ;

extern const int number_of_asteroid;
extern const int chicken_number;

extern bool is_paused;
extern bool player_want_to_play_again;
extern int level;
extern const int boss_number;
extern bool check_collision_2_rect(const SDL_Rect &a, const SDL_Rect &b);
#endif