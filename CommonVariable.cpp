#include "CommonVariable.h"
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
SDL_Event event;
SDL_Window *window = SDL_CreateWindow("Chicken Invaders ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
const int MIDDLE_X = SCREEN_WIDTH / 2;
const int MIDDLE_Y = SCREEN_HEIGHT / 2;
int times_player_want_to_playagain = 0;

const double MAIN_OBJECT_SCALE = 0.35;
const double CHICKEN_OBJECT_SCALE = 1.55;

const int number_of_asteroid = 1;
const int chicken_number = 1;

bool is_paused = false;
bool player_want_to_play_again = false;
int level = 0;
const int boss_number = 2;
bool check_collision_2_rect(const SDL_Rect &a, const SDL_Rect &b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    return true;
}