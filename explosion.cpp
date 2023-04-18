#include "explosion.h"
Uint32 EXPLOSION_startTicks = 0;
Uint32 EXPLOSION_spriteIndex = 0;
const Uint32 EXPLOSION_spritetime = 10;
Explosion::Explosion()
{
    is_on_screen_ = false;
    rect_.w = 300; // the width of the mainObject / 2
    rect_.h = 300; // the height of the mainObject / 2
}
Explosion::~Explosion()
{
    SDL_DestroyTexture(texture_);
}

void Explosion::set_coordinates(const int &x, const int &y)
{
    rect_.x = x;
    rect_.y = y;
}
void Explosion::load_animation_sprite(SDL_Renderer *renderer, const char *file)
{
    SDL_Surface *surface = IMG_Load(file);
    if(surface == NULL)
    {
        std::cout << "Error at file Explosion.cpp" << std::endl;
        std::cout << "Unable to load image " << file << " SDL_image Error: " << IMG_GetError() << std::endl;
    }
    texture_ = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}
void Explosion::set_clips()
{
    for (int i = 0; i < EXPLOSION_NUMS_FRAME; i++)
    {
        frame_clip[i].x = i * (500 / EXPLOSION_NUMS_FRAME);
        frame_clip[i].y = 0;
        frame_clip[i].w = 500 / EXPLOSION_NUMS_FRAME;
        frame_clip[i].h = 68;
    }
}
void Explosion::render_animation(SDL_Renderer * renderer)
{
    if(is_on_screen_ == false) return;
    std::cout << "We can reach here" << std::endl;
    if(EXPLOSION_spriteIndex == 7) 
    {
        std::cout << "Reached end of the frame" << std::endl;
        is_on_screen_ = false;
    }
    Uint32 currentTicks = SDL_GetTicks();
    if (currentTicks > EXPLOSION_startTicks + EXPLOSION_spritetime)
    {
        EXPLOSION_spriteIndex = (EXPLOSION_spriteIndex + 1) % EXPLOSION_NUMS_FRAME;
        EXPLOSION_startTicks = currentTicks;
    }
    SDL_Rect destRect = {rect_.x, rect_.y, rect_.w, rect_.h};
    SDL_RenderCopy(renderer, texture_, &frame_clip[EXPLOSION_spriteIndex], &destRect);
}
void Explosion::render_specific_frame(SDL_Renderer *renderer, const int &frame)
{
    SDL_Rect destRect = {rect_.x, rect_.y, rect_.w, rect_.h};
    SDL_RenderCopy(renderer, texture_, &frame_clip[frame], &destRect);
}
