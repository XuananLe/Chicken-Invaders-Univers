#include "Asteroid.h"
// Implement Constructor and Destructor
const double scale_if_health_is_1 = 0.2;
const double scale_if_health_is_2 = 0.3;
const double scale_if_health_is_3 = 0.5;
Asteroid::Asteroid()
{
    texture_ = IMG_LoadTexture(renderer, "res/image/asteroid-3.png");
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = static_cast<int>(300 * scale_if_health_is_3);
    rect_.h = static_cast<int>(300 * scale_if_health_is_3);
    speed_ = 5;
    health_ = 3;
    is_on_screen = true;
    spinning_angle_ = 0;
}
Asteroid::~Asteroid()
{
}
void Asteroid::set_rect_cordinate(const int &x, const int &y)
{
    rect_.x = x;
    rect_.y = y;
}
void Asteroid::set_rect_cordinate_and_width_height(const int &x, const int &y, const int &width, const int &height)
{
    rect_.x = x;
    rect_.y = y;
    rect_.w = width;
    rect_.h = height;
}
void Asteroid::set_width_height(const int &width, const int &height)
{
    rect_.w = width;
    rect_.h = height;
}
void Asteroid::render_with_angle()
{
    if (is_on_screen == false || health_ <= 0)
        return;
    if (health_ == 3)
    {
        rect_.w = static_cast<int>(300 * scale_if_health_is_3);
        rect_.h = static_cast<int>(300 * scale_if_health_is_3);
        SDL_RenderCopyEx(renderer, texture_, NULL, &rect_, spinning_angle_, NULL, SDL_FLIP_NONE);
    }
    else if (health_ == 2)
    {
        rect_.w = static_cast<int>(300 * scale_if_health_is_2);
        rect_.h = static_cast<int>(300 * scale_if_health_is_2);
        SDL_RenderCopyEx(renderer, texture_, NULL, &rect_, spinning_angle_, NULL, SDL_FLIP_NONE);
    }
    else if (health_ == 1)
    {
        rect_.w = static_cast<int>(300 * scale_if_health_is_1);
        rect_.h = static_cast<int>(300 * scale_if_health_is_1);
        SDL_RenderCopyEx(renderer, texture_, NULL, &rect_, spinning_angle_, NULL, SDL_FLIP_NONE);
    }
}
void Asteroid::moving_diagonal()
{
    rect_.x += speed_;
    rect_.y += speed_;
}
void Asteroid::moving_downward()
{
    if (is_on_screen == false)
        return;
    if (health_ <= 0)
        return;
    rect_.y += speed_;
}
void Asteroid::update()
{
    if (is_on_screen == false)
        return;
    if (health_ <= 0)
        return;
    spinning_angle_ += 24;
    if (spinning_angle_ > 360)
    {
        spinning_angle_ = 0;
    }
    if (rect_.x > SCREEN_WIDTH || rect_.y > SCREEN_HEIGHT)
    {
        rect_.x = rand() % SCREEN_WIDTH;
        rect_.y = 0;
    }
}