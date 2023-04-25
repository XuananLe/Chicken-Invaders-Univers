#include "menu.h"
GameMenu::GameMenu()
{
    TTF_Init();
    menu_texture = IMG_LoadTexture(renderer, "res/image/logo.png");
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    game_has_started = false;
    menu_rect.x = 0;
    transition_level = TTF_OpenFont("res/font/RopaSans-Italic.ttf", 100);
    menu_rect.y = 0;
    menu_rect.w = SCREEN_WIDTH;
    menu_rect.h = SCREEN_HEIGHT;
    before_level_texture = NULL;
    before_level.w = 800;
    before_level.h = 200;
    before_level.x = SCREEN_WIDTH / 2 - before_level.w / 2;
    before_level.y = SCREEN_HEIGHT / 2 - before_level.h / 2 - 300;

    health_bar_texture = IMG_LoadTexture(renderer, "res/image/hp_bar.png");
    health_bar.w = 300;
    health_bar.h = 30;
    health_bar.x = 0;
    health_bar.y = SCREEN_HEIGHT - health_bar.h;

    new_font = TTF_OpenFont("res/font/arial.ttf", 100);
    game_over = Mix_LoadWAV("res/sound/game_over.wav");

    if (user_texture == NULL)
    {
        std::cout << "Error: " << SDL_GetError() << std::endl;
    }
}
GameMenu::~GameMenu()
{
}

void GameMenu::render_menu()
{
    if (player_hit_option == 1)
    {
        SDL_RenderCopy(renderer, option_texture, NULL, &option_rect);
    }
    else if (logged_in == true)
    {
        SDL_Rect user_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, user_texture, NULL, &user_rect);
    }
    else if (game_has_started == false)
    {
        SDL_RenderCopy(renderer, menu_texture, NULL, &menu_rect);
    }
}
void GameMenu::render_user()
{
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
    // if(event.type == SDL_KEYDOWN)
    // {
    //     if(event.key.keysym.sym == SDLK_b && level == 4)
    //     {
    //         player_pressed_b = true;
    //     }
    // }

    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
    {
        exit(EXIT_SUCCESS);
    }
    if (event.type == SDL_MOUSEMOTION)
    {
        int x = 0, y = 0;
        SDL_GetMouseState(&x, &y);
        // std::cout << x << " " << y << std::endl;
    }
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        int x = 0, y = 0;
        SDL_GetMouseState(&x, &y);
        if (logged_in == true && 11 <= x && x <= 188 && y >= 9 && y <= 189)
        {
            logged_in = false;
            return;
        }
        if (player_hit_option == 1)
        {
            player_hit_option = -1;
            return;
        }
        if (x >= 490 && x <= 670 && y >= 900 && y <= 1074)
        {
            game_has_started = true;
            return;
        }
        if (x >= 870 and x <= 1050 and 895 <= y and y <= 1074 && player_hit_option == -1)
        {
            player_hit_option = 1;
        }
        if (x >= 1830 && x <= 1913 && y >= 8 && y <= 90)
        {
            exit(EXIT_SUCCESS);
            return;
        }
        if (1 <= x && x <= 390 && y >= 47 && y <= 90)
        {
            const std::string url = "https://github.com/XuananLe";
            const std::string cmd = "xdg-open " + url;
            system(cmd.c_str());
            return;
        }
        if (600 <= x && x <= 849 && y >= 900 && y <= 1070 && logged_in == false)
        {
            logged_in = true;
        }
        if (logged_in == true && 392 <= x and x <= 572 and 390 <= y and y <= 570)
        {
            player_add_account = true;
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

    before_level_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, before_level_texture, NULL, &before_level);
}
void GameMenu::render_time(MainObject *player)
{
    if (player->get_health() <= 0)
        return;
    if(player_pressed_b == true)
    {
        start_time = SDL_GetTicks() - start_time;
    }
    if (is_paused == false)
    {
        last_time = start_time;
        start_time = SDL_GetTicks();
        elapsed_time = start_time - last_time;
        int seconds = (start_time / (1000)) % 60;          // Calculate the number of seconds
        int minutes = start_time / ((1000 * 60));          // Calculate the number of minutes
        sprintf(time_text, "%02d:%02d", minutes, seconds); // Format the time as mm:ss
    }
    SDL_Color color = {255, 0, 0, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(GameMenu::new_font, time_text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstrect = {10, 10, 100, 60};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}

void GameMenu::render_game_over(MainObject *player)
{
    if (player->get_health() > 0)
        return;
    std::string message = "GAME OVER";
    std::string message2 = "YOU HAVE SURVIVED FOR " + std::string(time_text);
    std::string message3 = "PRESS C TO CONTINUE OR ESC TO EXIT";

    SDL_Rect next_line = {before_level.x - 100, before_level.y + 200, before_level.w + 200, before_level.h};
    SDL_Rect next_line2 = {before_level.x - 100, before_level.y + 400, before_level.w + 200, before_level.h};

    SDL_Surface *surface = TTF_RenderText_Solid(transition_level, message.c_str(), color);
    SDL_Surface *surface2 = TTF_RenderText_Solid(transition_level, message2.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_Surface *surface3 = TTF_RenderText_Solid(transition_level, message3.c_str(), color);
    SDL_Texture *texture3 = SDL_CreateTextureFromSurface(renderer, surface3);

    Mix_VolumeChunk(GameMenu::game_over, 12);
    Mix_PlayChannelTimed(1, GameMenu::game_over, 1, 1000);

    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface2);

    SDL_RenderCopy(renderer, texture2, NULL, &next_line);
    SDL_RenderCopy(renderer, texture3, NULL, &next_line2);
    SDL_RenderCopy(renderer, texture, NULL, &before_level);
}
void GameMenu::render_game_win(MainObject *player)
{
    if(level <= 3) return;
    GameMenu::User->numbers_player_want_to_play_again = player_want_to_play_again;
    GameMenu::User->nums_of_wings = player->get_num_of_wings();
    GameMenu::User->time = time_text;

    std::string message = "YOU HAVE WON THE GAME";
    std::string message2 = "YOU HAVE SURVIVED FOR " + std::string(time_text);
    std::string message3 = "PRESS B TO BACK THE MENU";

    SDL_Rect next_line = {before_level.x - 100, before_level.y + 200, before_level.w + 200, before_level.h};
    SDL_Rect next_line2 = {before_level.x - 100, before_level.y + 400, before_level.w + 200, before_level.h};

    SDL_Surface *surface = TTF_RenderText_Solid(transition_level, message.c_str(), color);
    SDL_Surface *surface2 = TTF_RenderText_Solid(transition_level, message2.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_Surface *surface3 = TTF_RenderText_Solid(transition_level, message3.c_str(), color);
    SDL_Texture *texture3 = SDL_CreateTextureFromSurface(renderer, surface3);

    Mix_VolumeChunk(GameMenu::game_over, 12);
    Mix_PlayChannelTimed(1, GameMenu::game_over, 1, 1000);

    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface2);

    SDL_RenderCopy(renderer, texture2, NULL, &next_line);
    SDL_RenderCopy(renderer, texture3, NULL, &next_line2);
    SDL_RenderCopy(renderer, texture, NULL, &before_level);
}