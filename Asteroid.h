#ifndef ASTEROID_H_
#define ASTEROID_H_
#include "CommonVariable.h"
extern const double scale_if_health_is_1;
extern const double scale_if_health_is_2;
extern const double scale_if_health_is_3;
class Asteroid
{
protected:
SDL_Texture* texture_;
SDL_Rect rect_;
int random_type;
int v_x;
int v_y;
int speed_;
int health_;

bool is_on_screen;
double spinning_angle_;
public:
// Constructor and Destructor
Asteroid();
~Asteroid();
void set_rect_cordinate(const int& x, const int& y);
void set_rect_cordinate_and_width_height(const int& x, const int& y, const int& width, const int& height);
void set_width_height(const int& width, const int& height);                                                                                                                                                                                                                                                                                                                                                                                                                         
SDL_Rect get_rect() const{return this->rect_;}
void set_speed(const int& speed){this->speed_ = speed;}
int get_speed() const{return this->speed_;}
void set_health(const int& health){this->health_ = health;}
int get_health() const{return this->health_;}
void set_is_on_screen(const bool& is_on_screen){this->is_on_screen = is_on_screen;}
bool get_is_on_screen() const{return this->is_on_screen;}
void render_with_angle();                                                                                                                                                                                                                                                                                                                                                   
void moving_diagonal();
// void moving_downward();
void spinning();
// FREE METHOD
void free()
{
    if (texture_ != NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
        rect_.x = 0;
        rect_.y = 0;
    }
}
};
#endif