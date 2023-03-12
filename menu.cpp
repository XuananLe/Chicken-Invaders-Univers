#include "menu.h"
GameMenu::GameMenu()
{
    TTF_Init();
    menu_texture = IMG_LoadTexture(renderer, "res/image/logo.png");
    if (menu_texture == NULL)
    {
        std::cout << "Error at file menu.cpp " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    game_has_started = false;
    menu_rect.x = 0;
    transition_level = TTF_OpenFont("res/font/RopaSans-Italic.ttf", 100);
    if(transition_level == NULL)
    {
        std::cout << "Error at file menu.cpp " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    // Set font hinting mode to TTF_HINTING_NORMAL
    TTF_SetFontHinting(transition_level, TTF_HINTING_NORMAL);
    // Enable font kerning
    TTF_SetFontKerning(transition_level, 1);
    menu_rect.y = 0;
    menu_rect.w = SCREEN_WIDTH;
    menu_rect.h = SCREEN_HEIGHT;
    before_level_texture = NULL;
    before_level.w = 800;
    before_level.h = 200;
    before_level.x = SCREEN_WIDTH / 2 - before_level.w / 2;
    before_level.y = SCREEN_HEIGHT / 2 - before_level.h / 2;
}
GameMenu::~GameMenu()
{
}

void GameMenu::render_menu()
{
    SDL_RenderCopy(renderer, menu_texture, NULL, &menu_rect);
}
void GameMenu::process_input_menu(SDL_Event &event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        int x = 0, y = 0;
        SDL_GetMouseState(&x, &y);
        if (x >= 490 && x <= 670 && y >= 900 && y <= 1074)
        {
            game_has_started = true;
            return;
        }
        if (x >= 1830 && x <= 1913 && y >= 8 && y <= 90)
        {
            exit(EXIT_SUCCESS);
        }
    }
}
void GameMenu::render_before_level(int level)
{
    std::string message;
    SDL_Color color = {102,102, 225};
    if(level == 1)
    {
        message = "GET READY FOR THE EGGS";
    }
    else if(level == 2)
    {
        message = "WATCHOUT FOR THE ASTEROID RAIN";
    }
    else if(level == 3)
    {
        message = "WELCOME TO FINAL LEVEL";
    }
    SDL_Surface *surface = TTF_RenderText_Solid(transition_level,message.c_str(), color);
    SDL_Surface *blurred_surface = SDL_CreateRGBSurface(0, before_level.w, before_level.h, 32, 0, 0, 0, 0);
    SDL_Rect rect = {0, 0, before_level.w, before_level.h};
    SDL_BlitSurface(surface, &rect, blurred_surface, &rect);

    if (transition_level == NULL)
    {
        std::cout << "Error at file menu.cpp " << TTF_GetError() << std::endl;
    }
    if (surface == NULL)
    {
        std::cout << "Error at file menu.cpp " << SDL_GetError() << std::endl;
        std::cout << "WHAT THE FUCK" << std::endl;
        exit(EXIT_FAILURE);
    }
    before_level_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (before_level_texture == NULL)
    {
        std::cout << "Error at file menu.cpp " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, before_level_texture, NULL, &before_level);
}

