#ifndef PRESENT_H
#define PRESENT_H
#include "CommonVariable.h"
class Present
{
protected:
    SDL_Texture *atomic_power_texture_;
    SDL_Texture *neutron_gift_texture_;
    SDL_Texture *arrow_gift;
    SDL_Texture *boron_gift;
    SDL_Rect rect;
    int speed;
    int kind_of_present;
    bool is_on_screen;

public:
    Present()
    {
        atomic_power_texture_ = IMG_LoadTexture(renderer, "res/image/power_up.png");
        neutron_gift_texture_ = IMG_LoadTexture(renderer, "res/image/neutron_gift.png");
        arrow_gift = IMG_LoadTexture(renderer, "res/image/arrow_gift.png");
        boron_gift = IMG_LoadTexture(renderer, "res/image/boron_gift.png");
        rect = {0, 0, 49, 58};
        is_on_screen = true;
        speed = 5;
    }
    ~Present() {}

    void set_rect_cordinate(const int &x, const int &y)
    {
        rect.x = x;
        rect.y = y;
    }
    SDL_Rect get_rect() { return rect; }

    void set_is_on_screen(bool is_on_screen) { this->is_on_screen = is_on_screen; }
    bool get_is_on_screen() { return is_on_screen; }
    // 0 - atomic power means power up  1 - neutron, 2 - arrow, 3 - boron
    void set_kind_of_present(int kind_of_present) { this->kind_of_present = kind_of_present; }
    // 0 - atomic power 1 - neutron, 2 - arrow, 3 - boron
    int get_kind_of_present() { return kind_of_present; }
    void render()
    {
        if (is_on_screen == false)
            return;
        switch (kind_of_present)
        {
        case 0:
        {
            rect.w = 40;
            rect.h = 50;
            SDL_RenderCopy(renderer, atomic_power_texture_, nullptr, &rect);
            return;
        }
        case 1:
        {
            rect.w = 49;
            rect.h = 58;
            SDL_RenderCopy(renderer, neutron_gift_texture_, nullptr, &rect);
            return;
        }
        case 2:
        {
            rect.w = 49;
            rect.h = 58;
            SDL_RenderCopy(renderer, arrow_gift, nullptr, &rect);
            return;
        }
        case 3:
        {
            rect.w = 49;
            rect.h = 58;
            SDL_RenderCopy(renderer, boron_gift, nullptr, &rect);
            return;
        }
        default:
        {
            return;
        }
        }
    }
    void update()
    {
        if (is_on_screen == false)
            return;
        rect.y += speed;
        if (rect.y > SCREEN_HEIGHT)
        {
            is_on_screen = false;
        }
    }
};
#endif