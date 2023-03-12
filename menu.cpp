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
    font = TTF_OpenFont("res/font/RopaSans-Italic.ttf", 100);
    // Set font hinting mode to TTF_HINTING_NORMAL
    TTF_SetFontHinting(font, TTF_HINTING_NORMAL);
    // Enable font kerning
    TTF_SetFontKerning(font, 1);
    menu_rect.y = 0;
    menu_rect.w = SCREEN_WIDTH;
    menu_rect.h = SCREEN_HEIGHT;
    after_level_1 = NULL;
    after_level_1_rect.w = 800;
    after_level_1_rect.h = 200;
    after_level_1_rect.x = SCREEN_WIDTH / 2 - after_level_1_rect.w / 2;
    after_level_1_rect.y = SCREEN_HEIGHT / 2 - after_level_1_rect.h / 2;
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
void GameMenu::render_after_level_1()
{
    SDL_Color color = {102,102, 225};
    SDL_Surface *surface = TTF_RenderText_Solid(font, "WELCOME TO LEVEL 1", color);
    SDL_Surface *blurred_surface = SDL_CreateRGBSurface(0, after_level_1_rect.w, after_level_1_rect.h, 32, 0, 0, 0, 0);
    SDL_Rect rect = {0, 0, after_level_1_rect.w, after_level_1_rect.h};
    SDL_BlitSurface(surface, &rect, blurred_surface, &rect);

    if (font == NULL)
    {
        std::cout << "Error at file menu.cpp " << TTF_GetError() << std::endl;
    }
    if (surface == NULL)
    {
        std::cout << "Error at file menu.cpp " << SDL_GetError() << std::endl;
        std::cout << "WHAT THE FUCK" << std::endl;
        exit(EXIT_FAILURE);
    }
    after_level_1 = SDL_CreateTextureFromSurface(renderer, surface);
    if (after_level_1 == NULL)
    {
        std::cout << "Error at file menu.cpp " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, after_level_1, NULL, &after_level_1_rect);
}
void GameMenu::render_after_level_2()
{
    after_level_2 = IMG_LoadTexture(renderer, "res/image/after_level_2.png");
    if (after_level_2 == NULL)
    {
        std::cout << "Error at file menu.cpp " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    SDL_RenderCopy(renderer, after_level_2, NULL, &menu_rect);
}