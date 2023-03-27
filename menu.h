#ifndef MENU_H
#define MENU_H
#include "CommonVariable.h"
#include "BaseObject.h"
#include "MainObject.h"
#include <unistd.h>
#include "BackGround.h"
class Background;
class MainObject;
class GameMenu
{
protected:
    SDL_Texture *menu_texture = NULL;
    int player_hit_option = -1; // -1 mean no option is selected 1 mean hit
    SDL_Texture* option_texture = IMG_LoadTexture(renderer,"res/image/guidance.png");
    SDL_Rect option_rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    SDL_Texture *before_level_texture = NULL;
    SDL_Texture *health_bar_texture = NULL;
    TTF_Font* transition_level = NULL;
    SDL_Rect menu_rect;    
    SDL_Color color = {102, 102, 225}; // blue
    SDL_Rect health_bar;    
    SDL_Rect before_level;
    TTF_Font* new_font = TTF_OpenFont("res/font/arial.ttf", 100);
    Uint32 last_time = SDL_GetTicks();
    Uint32 start_time = last_time;
    Uint32 elapsed_time = 0;
    bool game_has_started;
    char time_text[16];
    Mix_Chunk *game_over = Mix_LoadWAV("res/sound/game_over.wav");
public:
    GameMenu();
    SDL_Texture* get_texture() const {return menu_texture;}
    ~GameMenu();
    bool get_game_has_started() const { return game_has_started; }
    void process_input_menu(SDL_Event &event);
    void render_before_level(int level);
    void set_game_has_started(const bool & state){game_has_started = state;}
    void render_menu();
    void render_game_over(MainObject* player);
    void render_health_bar(MainObject* player);
    void render_time(MainObject* player);
};
#endif
