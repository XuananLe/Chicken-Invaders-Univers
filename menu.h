#ifndef MENU_H
#define MENU_H
#include "CommonVariable.h"
#include "BaseObject.h"
#include "BackGround.h"
class Background;
class GameMenu
{
protected:
    SDL_Texture *menu_texture = NULL;
    SDL_Texture *after_level_1 = NULL;
    SDL_Texture *after_level_2 = NULL;
    TTF_Font* transition_level = TTF_OpenFont("arial.ttf", 32);
    SDL_Rect menu_rect;
    SDL_Rect after_level_1_rect;
    bool game_has_started;

public:
    GameMenu();
    SDL_Texture* get_texture() const {return menu_texture;}
    ~GameMenu();
    bool get_game_has_started() const { return game_has_started; }
    void process_input_menu(SDL_Event &event);
    void render_after_level_1();
    void render_after_level_2();
    void set_game_has_started(const bool & state){game_has_started = state;}
    void render_menu();
};
#endif