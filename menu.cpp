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
    if (transition_level == NULL)
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

    health_bar_texture = IMG_LoadTexture(renderer, "res/image/hp_bar.png");
    if (health_bar_texture == NULL)
    {
        std::cout << "Error at file menu.cpp " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    health_bar.w = 300;
    health_bar.h = 30;
    health_bar.x = 0;
    health_bar.y = SCREEN_HEIGHT - health_bar.h;

    new_font = TTF_OpenFont("res/font/arial.ttf", 100);
    if (new_font == NULL)
    {
        std::cout << "Error at file menu.cpp " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
}
GameMenu::~GameMenu()
{
}

void GameMenu::render_menu()
{
    SDL_RenderCopy(renderer, menu_texture, NULL, &menu_rect);
}
void GameMenu::render_health_bar(MainObject *player)
{
    if (player->get_health() <= 0)
        return;
    color = {255, 0, 0}; // red
    SDL_Surface *wings_text = TTF_RenderText_Solid(new_font, std::to_string(player->get_num_of_wings()).c_str(), color);
    SDL_Texture *wings_texture__ = SDL_CreateTextureFromSurface(renderer, wings_text);
    SDL_Rect wings_render_rect = {65, 1048, 40, 30};

    SDL_Surface *health_text = TTF_RenderText_Solid(new_font, std::to_string(player->get_health()).c_str(), color);
    SDL_Texture *health_texture = SDL_CreateTextureFromSurface(renderer, health_text);
    SDL_Rect health_render_rect = {212, 1051, 35, 30};

    SDL_RenderCopy(renderer, health_texture, NULL, &health_render_rect);
    SDL_RenderCopy(renderer, wings_texture__, NULL, &wings_render_rect);
    SDL_RenderCopy(renderer, health_bar_texture, NULL, &health_bar);
    color = {102, 102, 225}; // blue
}
void GameMenu::process_input_menu(SDL_Event &event)
{
    if (event.type == SDL_QUIT)
    {
        exit(EXIT_SUCCESS);
    }
    if (event.type == SDL_MOUSEMOTION)
    {
        int x = 0, y = 0;
        SDL_GetMouseState(&x, &y);
        std::cout << x << " " << y << std::endl;
    }
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
            return;
        }
        if (1 <= x && x <= 390 && y >= 47 && y <= 90)
        {
            const std::string url = "https://xuananle.github.io/demowebpage/";
            const std::string cmd = "xdg-open" + url;
            system(cmd.c_str());
        }
    }
}
void GameMenu::render_before_level(int level)
{
    std::string message;
    if (level == 1)
    {
        message = "GET READY FOR THE EGGS";
    }
    else if (level == 2)
    {
        message = "WATCH OUT FOR THE ASTEROID RAIN";
    }
    else if (level == 3)
    {
        message = "WELCOME TO FINAL LEVEL";
    }
    SDL_Surface *surface = TTF_RenderText_Solid(transition_level, message.c_str(), color);
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
void GameMenu::render_time()
{
    last_time = start_time;
    start_time = SDL_GetTicks();
    elapsed_time = start_time - last_time;
    int seconds = (start_time / (1000)) % 60;          // Calculate the number of seconds
    int minutes = start_time / ((1000 * 60));          // Calculate the number of minutes
    sprintf(time_text, "%02d:%02d", minutes, seconds); // Format the time as mm:ss
    SDL_Color color = {255,0,0, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(GameMenu::new_font, time_text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstrect = {10, 10, 60, 60};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}