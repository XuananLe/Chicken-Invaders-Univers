#ifndef EGG_H
#define EGG_H
#include "CommonVariable.h"
class Egg
{
protected:
    SDL_Texture* nice_egg;
    Uint32 last_time_eggs_broken;
    SDL_Texture* broken_egg;
    bool is_broken; // a flag to indicate if the egg is broken
    SDL_Rect rect_;
    int speed_;
    int v_x;
    int v_y;
    bool alive_ = true; // a flag to indicate if the egg is alive
public:
    Egg();
    ~Egg();

    // SET AND GET METHOD FOR RECT
    void set_rect_cordinate(const int &x, const int &y);
    void set_rect_cordinate_width_and_height(const int &x, const int &y, const int &width, const int &height);
    void set_rect_width_and_height(const int &width, const int &height);
    SDL_Rect get_rect() const;
    SDL_Rect get_rect_width_height_with_scale(const double &scale) const;

    // SET AND GET METHOD FOR V_X AND V_Y
    void set_v_x(const int &v_x_){ v_x = v_x_; }
    void set_v_y(const int &v_y_){ v_y = v_y_; }
    int get_v_x() const{ return v_x; }
    int get_v_y() const{ return v_y; }

    // SET AND GET METHOD FOR ALIVE
    int get_alive() const{ return alive_; }
    void set_alive(const int &alive){ alive_ = alive; }
    
    // SET AND GET METHOD FOR SPEED
    int get_speed() const{ return speed_; }
    void set_speed(const int &speed){ speed_ = speed; }

    // SET AND GET METHOD FOR IS_BROKEN 
    bool get_is_broken() const{ return is_broken; }
    void set_is_broken(const bool &is_broken_){ is_broken = is_broken_; }

    void move_diagonally();    
    
    // RENDER METHOD FOR EGG
    void render();

    // UPDATE METHOD FOR EGG
    void update();

    // FREE METHOD
    void free();
};
#endif