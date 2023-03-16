#ifndef CHICKEN_H
#define CHICKEN_H
#include "Present.h"
#include "MainObject.h"
#include "AmmoObject.h"
#include "CommonVariable.h"
#include "Egg.h"
class MainObject;
const int CHICKEN_NUMS_FRAME = 18;
extern Uint32 CHICKEN_startTicks;
extern Uint32 CHICKEN_spriteIndex;
extern const Uint32 CHICKEN_spritetime;

class Chicken
{
protected:
    const int wing_fall_speed_ = 10;
    int egg_shooting_prob_; // the probability of the chicken to shoot an egg
    int health_;
    int angle_;
    int speed_;
    int radius_;
    double angle_increment;
    int x_direction_; // flags to indicate the direction of the chicken left or right, 1 for right and -1 for left
    bool is_alive;
    bool is_on_screen;
    bool has_present;
    double scale;
    double direction_;
    int damage_;
    int type_;
    bool alive_;
    int width_of_sprite;
    int height_of_sprite;
    double v_x;
    double v_y;
    int dir_x;
    int dir_y;
    Uint32 last_move_time_; // time since last move
    Uint32 last_egg_time_; // time since last egg was laid
    Uint32 broken_egg_time_; // time since last egg was broken


    Mix_Chunk *chicken_got_hit_sound = NULL;
    Mix_Chunk *chicken_laying_eggs_sound = NULL;
    Mix_Chunk *eggs_get_destroyed_sound = NULL;

    SDL_Rect frame_clip[CHICKEN_NUMS_FRAME];
    SDL_Rect rect_;
    SDL_Texture *texture_;
    SDL_Texture *wing_texture_;
    SDL_Rect wing_rect_;

    std::vector<Egg *> eggs_list;
    Present *present = new Present();

public:
    // Constructor and Destructor
    Chicken();
    ~Chicken();

    // Setting the clips for the animation
    void set_clips();

    void set_speed(const int &speed) { speed_ = speed; }
    int get_speed() const { return speed_; }

    std::vector<Egg *> get_eggs_list() const { return eggs_list; }
    // Loading the animation sprite
    void load_animation_sprite(SDL_Renderer *renderer, const char *file);

    // SET AND GET METHOD FOR RECT
    void set_rect_cordinate(const int &x, const int &y);
    void set_rect_cordinate_width_and_height(const int &x, const int &y, const int &width, const int &height);
    void set_rect_width_and_height(const int &width, const int &height);
    SDL_Rect get_rect() const;
    SDL_Rect get_rect_width_height_with_scale(const double &scale) const;
    // RENDERING THE ANIMATION
    void render_animation(SDL_Renderer *renderer, const double &scale);

    // GET METHOD FOR TEXTURE
    SDL_Texture *get_texture() const { return texture_; }

    // SET AND GET METHOD FOR ALIVE
    void set_alive(const bool &alive) { alive_ = alive; }
    bool get_alive() const 
    {
        if(health_ <= 0) return false; 
        return alive_; 
    }

    // CHICKEN MOVING BACK AND FORTH IN THE SCREEN
    void moving_back_and_forth();

    // CHICKEN MOVING LIKE A CIRCLE
    void moving_like_a_circle();

    // CHICKEN HANDLE SHOOTING EGGS AT RANDOM TIME
    void handle_shooting_eggs(MainObject* main_object);

    // UPDATE THE EGGS
    void update_the_eggs();

    // RENDER THE EGGS
    void render_the_eggs();

    // PLAY HIT SOUND
    void play_hit_sound();

    // SOUND WHEN LAYING EGGS
    void play_laying_eggs_sound() {}

    // SET AND GET METHOD FOR HEALTH
    void set_health(const int &health) { health_ = health; }
    int get_health() const { return health_; }

    // SET AND GET METHOD FOR ON SCREEN
    void set_on_screen(const bool &on_screen) { is_on_screen = on_screen; }
    bool get_on_screen() const { return is_on_screen; }

    void generate_present();

    Present *get_present() const
    {
        if (has_present == true)
        {
            return present;
        }
    }

    Uint32 get_last_egg_time() const { return last_egg_time_; }

    void set_has_present(const bool &has_present) { this->has_present = has_present; }
    bool get_has_a_present() const { return has_present; }
    // GET Wing rect
    SDL_Rect get_wing_rect() const { return wing_rect_; }


    void moving_toward_the_player(MainObject* main_object);

    void moving_toward_the_player();

    void moving_diagnoally();

    // FREE METHOD
    void free();
};
#endif