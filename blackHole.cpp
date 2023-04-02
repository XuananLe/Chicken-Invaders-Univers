#include "blackHole.h"
blackHole::blackHole()
{
    black_hole_rect.x = 0;
    black_hole_rect.y = 0;
    black_hole_rect.w = 200;
    black_hole_rect.h = 200;
    is_on_screen = false;
    last_time_spinning = SDL_GetTicks();
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    black_hole_texture = IMG_LoadTexture(renderer, "res/image/black_hole.png");
    black_hole_sound = Mix_LoadWAV("res/sound/wormHole.wav");
    if(black_hole_texture == NULL || black_hole_sound == NULL)
    {
        printf("Error: %s\n at file blackHole.cpp", SDL_GetError());
        exit(EXIT_SUCCESS);
    }
}
blackHole::~blackHole()
{
}
void blackHole::set_black_hole_rect(const int &x, const int &y)
{
    black_hole_rect.x = x;
    black_hole_rect.y = y;
}
void blackHole::free()
{
    SDL_DestroyTexture(black_hole_texture);
    // Mix_FreeChunk(black_hole_sound);
}
void blackHole::move()
{
    if (is_on_screen == false)
        return;
}

void blackHole::render()
{
    if (is_on_screen == true)
    {
        SDL_RenderCopyEx(renderer, black_hole_texture, NULL, &black_hole_rect, spinning_angle, NULL, SDL_FLIP_NONE);
        spinning_angle += 5;
        if (black_hole_rect.y > SCREEN_HEIGHT)
            is_on_screen = false;
        if (spinning_angle > 360)
            spinning_angle = 0;
    }
    else
    {
        black_hole_rect.x = 0;
        black_hole_rect.y = 0;
        black_hole_rect.w = 0;
        black_hole_rect.h = 0;
        SDL_RenderCopy(renderer, black_hole_texture, NULL, &black_hole_rect);
    }
}
void blackHole::spinnning_for_10_secs()
{
    if (is_on_screen == false)
        return;
    Uint32 current_time = SDL_GetTicks();
    black_hole_rect.y += 10;
    if(black_hole_rect.y > SCREEN_HEIGHT) is_on_screen = false;
    if (current_time - last_time_spinning > 10000)
    {
        is_on_screen = false;
        last_time_spinning = SDL_GetTicks();
    }
}