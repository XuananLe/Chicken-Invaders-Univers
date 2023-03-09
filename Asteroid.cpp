#include "Asteroid.h"
#include <cstring>
// Implement Constructor and Destructor
const double scale_if_health_is_1 = 0.2;
const double scale_if_health_is_2 = 0.3;
const double scale_if_health_is_3 = 0.5;
Asteroid::Asteroid()
{
    random_type = 3 + (double) rand() / RAND_MAX * (5 - 3);
    std::string type =  "res/image/asteroid-"+std::to_string(random_type)+".png";
    texture_ = IMG_LoadTexture(renderer,type.c_str());
    rect_.x = rand() % SCREEN_WIDTH;
    rect_.y = -100 - rand() % 500;
    rect_.w = static_cast<int>(300 * scale_if_health_is_3);
    rect_.h = static_cast<int>(300 * scale_if_health_is_3);
    speed_ = 5;
    v_x = rand() % 5 - 2;
    v_y = rand() % 5 + 2;
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
    if(is_on_screen == false) return;
    rect_.x += v_x;
    rect_.y += v_y;
    if(rect_.y >= SCREEN_HEIGHT)
    {
        rect_.x = rand() % SCREEN_WIDTH;
        rect_.y = -100 - rand() % 45;
        v_x = rand() % 5 - 2;
        v_y = rand() % 5 + 2;
    }
}
void Asteroid::spinning()
{
    if (is_on_screen == false)
        return;
    if (health_ <= 0)
        return;
    spinning_angle_ += 10;
    if (spinning_angle_ > 360)
    {
        spinning_angle_ = 0;
    }
}