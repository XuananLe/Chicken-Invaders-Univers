#ifndef BOSS_H
#define BOSS_H
#include "CommonVariable.h"
#include "Chicken.h"
#include "Egg.h"
#include "MainObject.h"
#include <vector>
extern const double BOSS_SCALE;
const int BOSS_NUMS_FRAME = 10;
extern Uint32 BOSS_startTicks;
extern const Uint32 BOSS_NUMBER_OF_EGGS;
extern Uint32 BOSS_spriteIndex;
extern const Uint32 BOSS_spritetime;
class MainObject;
class Boss
{
protected:
SDL_Rect frame_clip[BOSS_NUMS_FRAME];
SDL_Rect rect_;
SDL_Texture* texture_;
int health_;
int x_direction_;
bool is_on_screen;
bool has_present;
int speed_;
int width_of_sprite;
int last_egg_firing_time;
int height_of_sprite;
int last_egg_time;
Uint32 last_time_move;
int v_x;
int v_y;
std::vector<Egg*> egg_list;
Present* present = new Present();
//SDL_TimerID move_timer_; // how often the boss moves
Uint32 last_move_ticks_; // the last time the boss moved
Uint32 move_interval_;
Uint32 last_fire_ticks_; // the last time the boss fired
Mix_Chunk* shooting_egg_sound_;
Mix_Chunk* boss_shit;
public:
Boss();
~Boss();

std::vector<Egg*> get_egg_list() const { return egg_list; }
void set_egg_list(const std::vector<Egg*> &egg_list){ this->egg_list = egg_list; }

void set_clips();
void load_animation_sprite(SDL_Renderer *renderer, const char* file);
void set_rect_cordinate(const int &x, const int &y)
{
    rect_.x = x;
    rect_.y = y;
}
void set_rect_cordinate_width_and_height(const int &x, const int &y, const int &width, const int &height)
{
    rect_.x = x;
    rect_.y = y;
    rect_.w = 200;
    rect_.h = 117;
}
void set_rect_width_and_height(const int &width, const int &height)
{
    rect_.w = width;
    rect_.h = height;
}
SDL_Rect get_rect() const
{
    return rect_;
}
SDL_Rect get_rect_width_height_with_scale(const double &scale) const
{
    SDL_Rect temp;
    temp.x = rect_.x;
    temp.y = rect_.y;
    temp.w = 200 * scale;
    temp.h = 117 * scale;
    return temp;
}
void render_animation(SDL_Renderer* renderer, const double &scale);
Present* get_present() const 
{
    if(has_present == true)
    {
    return present;
    }
}
SDL_Texture* get_texture() const {return texture_;}
void set_has_present(const bool &has_present){ this->has_present = has_present; }
bool get_has_a_present() const { return has_present; }  



// SET AND GET METHOD FOR HEALTH AND ON SCREEN
void set_on_screen(const bool &on_screen){ is_on_screen = on_screen; }
bool get_on_screen() const{ return is_on_screen; }
void set_health(const int &health){ health_ = health; }
int get_health() const{ return health_; }
void move_randomly_up_down_left_right();
void firing_eggs(MainObject* main_object);
void moving_toward_player(MainObject * main_object);
void moving_toward_player();


void update_the_eggs()
{
    for(int i = 0; i < egg_list.size(); i++)
    {
        egg_list[i]->move_diagonally();
    }
}

void render_the_eggs()
{
    for(int i = 0; i < egg_list.size(); i++)
    {
        egg_list[i]->render();
    }
}

};
#endif