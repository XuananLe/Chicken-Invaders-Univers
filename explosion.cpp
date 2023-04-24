#include "explosion.h"
Explosion::Explosion()
{
    is_on_screen_ = false;
    width_of_sprite = 0;
    height_of_sprite = 0;
    texture_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}
Explosion::~Explosion()
{
}
void Explosion::load_animation_sprite(SDL_Renderer *renderer, const char *file)
{
    SDL_Surface *surface = IMG_Load(file);
    if (surface != NULL)
    {
        texture_ = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture_ != NULL)
        {
            width_of_sprite = surface->w / EXPLOSION_NUMS_FRAME;
            height_of_sprite = surface->h;
        }
        SDL_FreeSurface(surface);
    }
    else
    {
        std::cout << "Unable to load image " << file << " SDL_image Error: " << IMG_GetError() << std::endl;
    }
}
void Explosion::set_clips()
{
    if (width_of_sprite >= 0 && height_of_sprite >= 0)
    {
        for (int i = 0; i < EXPLOSION_NUMS_FRAME; i++)
        {
            frame_clip[i].x = i * width_of_sprite;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_of_sprite;
            frame_clip[i].h = height_of_sprite;
        }
        rect_.w = width_of_sprite;
        rect_.h = height_of_sprite;
    }
}
void Explosion::render_animation(SDL_Renderer *renderer)
{
    if(EXPLOSION_spriteIndex == 7) 
    {
        is_on_screen_ = false;
        return;
    }
    if (is_on_screen_)
    {
        Uint32 currentTicks = SDL_GetTicks();
        if (currentTicks > EXPLOSION_startTicks + EXPLOSION_spritetime)
        {
            EXPLOSION_startTicks = currentTicks;
            EXPLOSION_spriteIndex = (EXPLOSION_spriteIndex + 1) % EXPLOSION_NUMS_FRAME;
            if (EXPLOSION_spriteIndex == EXPLOSION_NUMS_FRAME - 1)
            {
                is_on_screen_ = false;
            }
            std::cout << EXPLOSION_spriteIndex << std::endl;
            rect_.w = static_cast<int>(width_of_sprite * 2.75);
            rect_.h = static_cast<int>(height_of_sprite * 2.75);
            SDL_RenderCopy(renderer, texture_, &frame_clip[EXPLOSION_spriteIndex], &rect_);
        }
    }
}
void Explosion::set_coordinates(const int &x, const int &y)
{
    rect_.x = x;
    rect_.y = y;
}