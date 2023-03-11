#include "menu.h"
GameMenu::GameMenu()
{
    menu_texture = IMG_LoadTexture(renderer, "res/image/logo.png");
    if (menu_texture == NULL)
    {
        std::cout << "Error at file menu.cpp " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    game_has_started = false;
    menu_rect.x = 0;
    menu_rect.y = 0;
    menu_rect.w = SCREEN_WIDTH;
    menu_rect.h = SCREEN_HEIGHT;
}
GameMenu::~GameMenu()
{
}

void GameMenu::render_menu()
{
    SDL_RenderCopy(renderer, menu_texture, NULL, &menu_rect);
}
void GameMenu::process_input(SDL_Event &event)
{
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        int x = 0, y = 0;
        SDL_GetMouseState(&x, &y);
        if(x >= 490 && x <= 670 && y >= 900 && y <= 1074)
        {
            game_has_started = true;
            return;
        }
        if(x >= 1830 && x <= 1913 && y >= 8 && y <= 90)
        {
            exit(EXIT_SUCCESS);
        }
    }
}