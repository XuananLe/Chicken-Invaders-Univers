#ifndef MAINOBJECT_H
#define MAINOBJECT_H
#include <string>
#include <cstring>
#include <string.h>
#include "CommonVariable.h"
#include "AmmoObject.h"
#include <iostream>
#include "Asteroid.h"
#include "Chicken.h"
#include "Boss.h"
#include "Present.h"
#include "explosion.h"
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

const int MAIN_OBJECT_NUMS_FRAME = 4;
extern Uint32 MAIN_OBJECT_startTicks;
extern Uint32 MAIN_OBJECT_spriteIndex;
extern const Uint32 MAIN_OBJECT_spritetime;

class Boss;
class Chicken;
class Explosion;

class MainObject
{
protected:
    SDL_Texture *texture_;
    SDL_Rect rect_;
    bool is_win;
    int spinning_angle;
    SDL_Rect frame_clip[MAIN_OBJECT_NUMS_FRAME];
    int witdth_of_sprite;
    int height_of_sprite;
    std::vector<AmmoObject *> ammo_list;
    Mix_Chunk *shoot_sound;
    Mix_Chunk *eat_wing_sound;
    Mix_Chunk *hit_sound;
    Mix_Chunk *getting_present_sound;
    int number_of_wings = 0;
    Uint32 slow_move_timer;
    bool slow_move;
    int health;
    int ammo_type = 1; // 1 mean BORON , 2 mean NEUTRON
    bool got_hit;
    int ammo_level = 0;

public:
    std::vector<Explosion *> explosion_list;
    MainObject();
    ~MainObject();

    void set_ammo_level(const int &ammo_level) { this->ammo_level = ammo_level; }
    // set and get method for the got hit
    void set_got_hit(const bool &got_hit) { this->got_hit = got_hit; }
    bool get_got_hit() const { return got_hit; }

    // LOADING ANIMATION
    void load_animation_sprite(SDL_Renderer *renderer, const char *file);

    // Setting clips for the animation
    void set_clips();

    // set and get method for the rectangle
    void set_rect_cordinate(const int &x, const int &y);
    void set_rect_cordinate_width_and_height(const int &x, const int &y, const int &width, const int &height);
    void set_rect_width_and_height(const int &width, const int &height);
    SDL_Rect get_rect() const;
    SDL_Rect get_rect_width_height_with_scale(const double &scale) const;

    // Render the animation with scale
    void render_animation(SDL_Renderer *renderer, const double &scale);

    // handling movement
    void handling_movement(SDL_Event &event);

    // handling shooting
    void handling_shooting(SDL_Event &event);

    // RENDERING SHOOTING AMMOR
    void render_shooting();

    // Processing the shooting with chicken
    void process_shooting_if_hit_chicken(Chicken *chicken);

    // Processing if eat wing rect
    void process_if_eat_wing_rect(Chicken *chicken);

    // processing if hit by chicken
    void process_if_hit_by_chicken(Chicken *chicken);
    // processing if hit by eggs
    void process_if_hit_by_eggs(Chicken *chicken);

    void process_if_hit_by_asteroid(Asteroid *asteroid);

    void processing_if_got_present(Present *present);

    void processing_if_hit_by_boss(Boss *boss);
    void processing_if_hit_by_boss_egg(Boss *boss);

    int get_health() const { return health; }
    void set_health(const int &health) { this->health = health; }
    // Free the texture
    void free();

    int get_num_of_wings() const { return number_of_wings; }
    void set_num_of_wings(const int &num_of_wings) { number_of_wings = num_of_wings; }

    void set_is_win(const bool &is_win) { this->is_win = is_win; }
    bool get_is_win() const
    {
        return MainObject::is_win;
    }
    void slowly_move_from_bottom();

    void set_slow_move()
    {
        slow_move = true;
        set_rect_cordinate(835, 1400);
    }

    bool get_slow_move() const { return slow_move;}
};
#endif