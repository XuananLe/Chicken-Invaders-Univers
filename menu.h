#ifndef MENU_H
#define MENU_H
#include "CommonVariable.h"
#include "BaseObject.h"
class GameMenu
{
protected:
    SDL_Texture *menu_texture = NULL;
    SDL_Rect menu_rect;
    bool game_has_started;

public:
    GameMenu();
    SDL_Texture* get_texture() const {return menu_texture;}
    ~GameMenu();
    bool get_game_has_started() const { return game_has_started; }
    void process_input(SDL_Event &event);
    void set_game_has_started(const bool & state){game_has_started = state;}
    void render_menu();
};
#endif