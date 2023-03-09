#ifndef AMMOOBJECT_H_
#define AMMOOBJECT_H_
#include "CommonVariable.h"
// DEFINE THE WIDTH AND HEIGHT OF THE ARROW
extern const int ARROW_WIDTH;
extern const int ARROW_HEIGHT;
class AmmoObject
{
protected:
    SDL_Texture* texture_;
    bool can_move = true;
    SDL_Rect rect_; 
    int life_time_; // the life time of the ammo
    double direction_; // the direction of the ammo
    int speed_; // SPEED OF THE AMMO
    int power;
    Uint32 startTicks_; // the time when the ammo is created
    int damage_; // the damage of the ammo
    bool alive_; // the status of the ammo, is it on the screen or not
public:
    enum AmmoType
    {
        ARROW = 1,
        BLASER = 2,
        BORON = 3,
        NEURON = 4
    };
    AmmoType type_;
    void set_type(const AmmoType type) {type_ = type;}
    AmmoType get_type() const {return type_;}
    // CONSTRUCTOR AND DESTRUCTOR
    AmmoObject();
    ~AmmoObject();

    // RENDER AND UPDATE METHOD
    virtual void render(SDL_Renderer* renderer);
    virtual void update();
    
    // Loading texture from file
    void load_static_ammo_picture(SDL_Renderer* renderer, const char *file_path);

    void set_can_move(const bool &can_move_) {can_move = can_move_;}
    bool get_can_move() const {return can_move;}

    // SET AND GET METHOD FOR SPEED
    int get_speed() const {return speed_;}
    void set_speed(const int &speed) {speed_ = speed;}


    // SET AND GET METHOD FOR RECT
    SDL_Rect get_rect() const {return rect_;}
    void set_rect_cordinate(const int &x, const int &y) {rect_.x = x; rect_.y = y;}
    void set_rect_width_height(const int &w, const int &h) {rect_.w = w; rect_.h = h;}
    void set_rect_cordinate_width_height(const int &x, const int &y, const int &w, const int &h) {rect_.x = x; rect_.y = y; rect_.w = w; rect_.h = h;}


    // SET AND GET METHOD FOR ALIVE (STATUS OF THE AMMO)
    bool is_alive() const{ return alive_;}
    void set_alive(const bool &alive){alive_ = alive;}

    // SET AND GET METHOD FOR THE DAMAGE    
    int get_damage() const {return damage_;}
    void set_damage(const int &damage) {damage_ = damage;}

    // SET AND GET METHOD FOR THE DIRECTION
    void set_direction(const double &direction) {direction_ = direction;}
    double get_direction() const {return direction_;}

    // GET METHOD FOR TEXTURE
    SDL_Texture* get_texture() const {return texture_;}

    // FREE METHOD
    void free();

};

// CLASS ARROWAMMO
class ArrowAmmo: public AmmoObject
{
protected:
// TO DO
public:
    // CONSTRUCTOR AND DESTRUCTOR
    ArrowAmmo();
    ~ArrowAmmo();
};

// CLASS BLASERAMMO

class BlaserAmmo: public AmmoObject
{
protected:
// TO DO
public:
    // CONSTRUCTOR AND DESTRUCTOR
    BlaserAmmo();
    ~BlaserAmmo();
};

// CLASS BORON AMMO
class BoronAmmo: public AmmoObject
{
protected:
// TO DO
public:
    // CONSTRUCTOR AND DESTRUCTOR
    BoronAmmo();
    ~BoronAmmo();
};

// CLASS NEURON AMMO
class NeuronAmmo: public AmmoObject
{
protected:
// TO DO
public:
    // CONSTRUCTOR AND DESTRUCTOR
    NeuronAmmo();
    ~NeuronAmmo();
};
#endif