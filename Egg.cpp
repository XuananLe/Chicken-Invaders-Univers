#include "Egg.h"
Egg::Egg()
{
    is_broken = false;
    alive_ = true;
    speed_ = 5;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 32;
    rect_.h = 41;
    last_time_eggs_broken = SDL_GetTicks();
    nice_egg = IMG_LoadTexture(renderer, "res/image/egg.png");
    broken_egg = IMG_LoadTexture(renderer, "res/image/egg2.png");
}
Egg::~Egg()
{
    SDL_DestroyTexture(nice_egg);
    SDL_DestroyTexture(broken_egg);
}
// IMPLEMENTATION OF SET AND GET METHOD FOR RECT
void Egg::set_rect_cordinate(const int &x, const int &y)
{
    rect_.x = x;
    rect_.y = y;
}
void Egg::set_rect_cordinate_width_and_height(const int &x, const int &y, const int &width, const int &height)
{
    rect_.x = x;
    rect_.y = y;
    rect_.w = 32;
    rect_.h = 41;
}
void Egg::set_rect_width_and_height(const int &width, const int &height)
{
    rect_.w = width;
    rect_.h = height;
}
SDL_Rect Egg::get_rect() const
{
    return rect_;
}
SDL_Rect Egg::get_rect_width_height_with_scale(const double &scale) const
{
    SDL_Rect temp;
    temp.x = rect_.x;
    temp.y = rect_.y;
    temp.w = 32 * scale;
    temp.h = 41 * scale;
    return temp;
}

// IMPLEMENTATION OF RENDER METHOD FOR EGG
void Egg::render()
{
    if (alive_ == false)
        return;
    if (is_broken == false)
    {
        SDL_RenderCopy(renderer, nice_egg, NULL, &rect_);
        last_time_eggs_broken = SDL_GetTicks();
    }
    else
    {
        Uint32 current_time = SDL_GetTicks();
        if(current_time - last_time_eggs_broken <= 2000)
        {
        SDL_RenderCopy(renderer, broken_egg, NULL, &rect_);
        }
        else alive_ = false;
    }
}
// IMPLEMENTATION OF UPDATE METHOD FOR EGG
void Egg::move_horizontally()
{
    speed_ = 10;
    if (alive_ == false)
        return;
    if (is_broken == false)
        rect_.y += speed_;
    if (rect_.y >= 1035)
    {
        rect_.w = 76;
        rect_.h = 57;
        // The egg has reached the bottom, so it should break
        is_broken = true;
    }
}
void Egg::move_diagonally()
{
    if (is_broken == true)
        return;
    rect_.x += v_x;
    rect_.y += v_y;
    if (rect_.y >= 1035)
    {
        rect_.w = 76;
        rect_.h = 57;
        // The egg has reached the bottom, so it should break
        is_broken = true;
    }
}

// IMPLEMENTATION OF FREE METHOD
void Egg::free()
{
    SDL_DestroyTexture(nice_egg);
    SDL_DestroyTexture(broken_egg);
    nice_egg = NULL;
    broken_egg = NULL;
}