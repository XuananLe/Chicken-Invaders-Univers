#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <iostream>
#include "CommonVariable.h"
#include <SDL2/SDL.h>
class BackGround
{
protected:
    SDL_Renderer* renderer_;
    SDL_Texture* image_;
    int y_;
    double speed_;
public:
    BackGround();
    ~BackGround();
    // LOAD BACKGROUND WITH A CERTAIN SPEED
    void loading_background(SDL_Renderer* renderer, const char* file_path);
    void render_background_scroll(SDL_Renderer* renderer);
    void update_background_scroll();

    void set_speed(double speed) {speed_ = speed;}
    double get_speed() {return speed_;}

};
#endif
