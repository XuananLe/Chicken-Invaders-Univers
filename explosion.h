#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "CommonVariable.h"
#include "MainObject.h"
const int EXPLOSION_NUMS_FRAME = 8;
class Explosion 
{
private:
SDL_Texture* texture_;
bool is_on_screen_;
SDL_Rect rect_;
SDL_Rect frame_clip[EXPLOSION_NUMS_FRAME];
int width_of_sprite;
int height_of_sprite;
Uint32 EXPLOSION_startTicks = SDL_GetTicks();
Uint32 EXPLOSION_spriteIndex = 0;
const Uint32 EXPLOSION_spritetime = 1;

public:
Explosion();
~Explosion();
void set_is_on_screen(const bool& is_on_screen) { is_on_screen_ = is_on_screen; }
bool get_is_on_screen() const { return is_on_screen_; }
void load_animation_sprite(SDL_Renderer* renderer, const char* file);
void set_clips();
void set_coordinates(const int& x, const int& y);
void render_animation(SDL_Renderer* renderer);
SDL_Rect get_rect() const { return rect_; }
void set_frame(const int& frame) { EXPLOSION_spriteIndex = frame; }
};
#endif