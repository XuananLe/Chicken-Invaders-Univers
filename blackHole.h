#ifndef BLACK_HOLE
#define BLACK_HOLE
#include "CommonVariable.h"
#include "MainObject.h"
class blackHole
{
private:
    SDL_Rect black_hole_rect;
    SDL_Texture *black_hole_texture;
    Mix_Chunk *black_hole_sound;
    bool is_on_screen;
    Uint32 last_time_spinning = SDL_GetTicks();
    int spinning_angle;
public:
    blackHole();
    ~blackHole();
    void set_black_hole_rect(const int &x, const int &y);
    void move();
    SDL_Rect get_black_hole_rect() { return black_hole_rect; }
    void render();
    void free();
    void init_time()
    {
        last_time_spinning = SDL_GetTicks();
    }
    void set_is_on_screen(const bool & is_on_screen)
    {
        this -> is_on_screen = is_on_screen;
    }
    bool get_is_on_screen() { return is_on_screen;}
    void play_black_hole_sound()
    {
        if(is_on_screen == false) return;
        Mix_VolumeChunk(black_hole_sound, 2); // Reduce volume by 50%
        Mix_PlayChannelTimed(-1, black_hole_sound, 1, 1000);
    }
    void spinnning_for_10_secs();
    SDL_Texture *get_black_hole_texture() { return black_hole_texture; }
};

#endif