#include "Chicken.h"
#include "Present.h"
#include "CommonVariable.h"
Uint32 CHICKEN_startTicks = 0;
Uint32 CHICKEN_spriteIndex = 0;
const Uint32 CHICKEN_spritetime = 50;

// IMPLEMENTATION OF CONSTRUCTOR AND DESTRUCTOR
Chicken::Chicken()
{
    health_ = 2;
    speed_ = 10;
    radius_ = 500;
    angle_increment = 2;
    egg_shooting_prob_ = 0.5; // Mean that the chicken has 50% chance to shoot an egg
    scale = 1;

    angle_ = 90; // IF angle = 0, meaning that the chicken is moving horizontally
    width_of_sprite = 0;
    height_of_sprite = 0;
    direction_ = 0;
    damage_ = 0;
    type_ = 1;
    alive_ = true;

    has_wing = (rand() % 100 <= 70) ? true : false;
    has_present = (rand() % 100 <= 50) ? true : false;

    last_egg_time_ = SDL_GetTicks();
    broken_egg_time_ = SDL_GetTicks();
    last_wing_time_ = SDL_GetTicks();

    is_on_screen = true;

    v_x = 4;
    v_y = 4;
    dir_x = 1;
    dir_y = 1;

    int x_direction = 1; // flags to indicate the direction of the chicken left or right, 1 for right and -1 for left

    texture_ = IMG_LoadTexture(renderer, "res/image/chicken123.png");
    wing_texture_ = IMG_LoadTexture(renderer, "res/image/meat.png");
    wing_rect_.x = 0;
    wing_rect_.y = 0;
    wing_rect_.w = 59;
    wing_rect_.h = 84;

    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 75;
    rect_.h = 68;
    chicken_got_hit_sound = Mix_LoadWAV("res/sound/CHICKEN_GOT_HIT.wav");
    chicken_laying_eggs_sound = Mix_LoadWAV("res/sound/Laying_eggs.wav");
    eggs_get_destroyed_sound = Mix_LoadWAV("res/sound/Egg_Destroy.wav");
}
Chicken::~Chicken()
{
    if (texture_ != NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}

// IMPLEMENTATION OF SETTING CLIPS
void Chicken::set_clips()
{
    if (width_of_sprite >= 0 || height_of_sprite >= 0)
    {
        for (int i = 0; i < CHICKEN_NUMS_FRAME; i++)
        {
            frame_clip[i].x = i * width_of_sprite / CHICKEN_NUMS_FRAME;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_of_sprite / CHICKEN_NUMS_FRAME;
            frame_clip[i].h = height_of_sprite;
        }
        rect_.w = 75;
        rect_.h = 68;
    }
}

// IMPLEMENTATION OF LOADING ANIMATION SPRITE
void Chicken::load_animation_sprite(SDL_Renderer *renderer, const char *file)
{
    texture_ = IMG_LoadTexture(renderer, file);

    // Set the texture blend mode to enable alpha blending
    SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND);

    // Set the alpha (transparency) value of the texture
    SDL_SetTextureAlphaMod(texture_, 255);

    if (texture_ == NULL)
    {
        std::cout << "Failed to load the texture" << std::endl;
    }
    else
    {
        SDL_QueryTexture(texture_, NULL, NULL, &width_of_sprite, &height_of_sprite);
        rect_.w = 75;
        rect_.h = 68;
    }
}

// IMPLEMENTATION OF SET AND GET METHOD FOR RECT
void Chicken::set_rect_cordinate(const int &x, const int &y)
{
    rect_.x = x;
    rect_.y = y;
}
void Chicken::set_rect_cordinate_width_and_height(const int &x, const int &y, const int &width, const int &height)
{
    rect_.x = x;
    rect_.y = y;
    rect_.w = 75;
    rect_.h = 68;
}
void Chicken::set_rect_width_and_height(const int &width, const int &height)
{
    rect_.w = width;
    rect_.h = height;
}
SDL_Rect Chicken::get_rect() const
{
    return rect_;
}
SDL_Rect Chicken::get_rect_width_height_with_scale(const double &scale) const
{
    SDL_Rect temp;
    temp.x = rect_.x;
    temp.y = rect_.y;
    temp.w = 75 * scale;
    temp.h = 68 * scale;
    return temp;
}

// IMPLEMENTATION OF RENDERING THE ANIMATION
void Chicken::render_animation(SDL_Renderer *renderer, const double &scale)
{
    // early return technique
    if (health_ > 0)
    {
        Uint32 currentTicks = SDL_GetTicks();
        if (currentTicks - CHICKEN_startTicks > CHICKEN_spritetime)
        {
            CHICKEN_spriteIndex = (CHICKEN_spriteIndex + 1) % CHICKEN_NUMS_FRAME;
            CHICKEN_startTicks = currentTicks;
        }
        rect_.w = static_cast<int>(75 * scale);
        rect_.h = static_cast<int>(68 * scale);
        SDL_Rect destRect = {rect_.x, rect_.y, static_cast<int>(75 * scale), static_cast<int>(68 * scale)};
        wing_rect_.x = rect_.x;
        wing_rect_.y = rect_.y;
        last_wing_time_ = SDL_GetTicks();
        // Render the current sprite
        SDL_RenderCopy(renderer, texture_, &frame_clip[CHICKEN_spriteIndex], &destRect);
    }
    else if (health_ <= 0)
    {
        if (has_wing == false)
            return;
        Uint32 currentTicks = SDL_GetTicks();
        if (currentTicks - last_wing_time_ > 6000)
        {
            has_wing = false;
            wing_rect_.y = -9999;
            wing_rect_.x = -9999;
            speed_ = 0;
            return;
        }
        if (wing_rect_.y + 84 <= SCREEN_HEIGHT)
        {
            wing_rect_.y += wing_fall_speed_;
        }
        if (is_on_screen == true)
            SDL_RenderCopy(renderer, wing_texture_, NULL, &wing_rect_);
        else
        {
            wing_rect_.y = -9999;
            wing_rect_.x = -9999;
            speed_ = 0;
            wing_rect_.w = 0;
            wing_rect_.h = 0;
        }
    }
}


// HANDLE SHOOTING EGGS AT A RANDOM TIME
void Chicken::handle_shooting_eggs_toward_player(MainObject *main_object)
{
    if(main_object->get_slow_move() == true) return;
    if (health_ <= 0 || !is_on_screen)
    {
        return;
    }
    Uint32 current_time = SDL_GetTicks();
    if (current_time - last_egg_time_ < 5 * 1000)
    { // Only lay egg every 5 seconds
        return;
    }

    int rand_num = rand() % 100 + 1;
    last_egg_time_ = current_time;
    if (rand_num <= 40)
    { 
        // 95% chance of laying egg
        double dx = main_object->get_rect().x - rect_.x;
        double dy = main_object->get_rect().y - rect_.y;
        double distance = sqrt(dx * dx + dy * dy);
        double unit_x = dx / distance;
        double unit_y = dy / distance;
        double egg_speed = 9;
        double egg_vx = egg_speed * unit_x;
        double egg_vy = egg_speed * unit_y;
        Egg *egg = new Egg();
        egg->set_rect_cordinate(rect_.x + rect_.w / 2, rect_.y + rect_.h / 2);
        egg->set_rect_width_and_height(32, 41);
        egg->set_v_x(egg_vx);
        egg->set_v_y(egg_vy);
        eggs_list.push_back(egg);
        Mix_PlayChannel(-1, chicken_laying_eggs_sound, 0);
    }
}

// IMPLEMENTATION OF UPDATING THE EGGS
void Chicken::update_the_eggs()
{
    for (int i = 0; i < eggs_list.size(); i++)
    {
        eggs_list[i]->move_horizontally();
    }
}

void Chicken::shooting_eggs_toward_player()
{
    for (int i = 0; i < eggs_list.size(); i++)
    {
        eggs_list[i]->move_diagonally();
    }
}

// IMPLEMENTATION OF RENDERING THE EGGS
void Chicken::render_the_eggs()
{
    for (int i = 0; i < eggs_list.size(); i++)
    {
        eggs_list[i]->render();
    }
}

// IMPLEMENTATION OF PLAYING HIT SOUND
void Chicken::play_hit_sound()
{
    Mix_AllocateChannels(100);
    Mix_PlayChannelTimed(-1, chicken_got_hit_sound, 0, 400);
}

// PRESENT
void Chicken::generate_present()
{
    if (present == NULL)
    {
        return;
    }
    if (has_present == 0)
    {
        present = NULL;
        return;
    }
    if (health_ != 0 && has_present == 1)
    {
        present->set_kind_of_present(rand() % 5);
        if (present->get_kind_of_present() == 2)
        {
            present->set_kind_of_present(3);
        }
        present->set_rect_cordinate(rect_.x + rect_.w / 2, rect_.y + rect_.h / 2);
        return;
    }
    if (has_present == true && health_ <= 0)
    {
        present->update();
        present->render();
    }
}

void Chicken::moving_diagnoally()
{    
    rect_.x += v_x * dir_x;
    rect_.y += v_y * dir_y;
    if (rect_.x < 0)
    {
        dir_x = 1;
    }
    else if (rect_.x + rect_.w > SCREEN_WIDTH)
    {
        dir_x = -1;
    }
    if (rect_.y < 0)
    {
        dir_y = 1;
    }
    else if (rect_.y + rect_.h > SCREEN_HEIGHT)
    {
        dir_y = -1;
    }
}

// IMPLEMENTATION OF FREE METHOD
void Chicken::free()
{
    if (texture_ != NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}

void Chicken::moving_parabola()
{
    if (health_ <= 0 || !is_on_screen)
    {
        return;
    }
    // Define the parabola parameters
    double a = -0.005;              // Controls the steepness of the parabola
    double h = SCREEN_WIDTH / 2.0;  // The x-coordinate of the vertex
    double k = SCREEN_HEIGHT / 2.0; // The y-coordinate of the vertex
    // Update x position
    rect_.x += x_direction_ * speed_;
    // Update y position using the parabolic equation: y = a * (x - h)^2 + k
    rect_.y = a * pow(rect_.x - h, 2) + k;
    // Reverse direction when reaching the screen edges
    if (rect_.x <= 0 || rect_.x + rect_.w >= SCREEN_WIDTH)
    {
        x_direction_ *= -1;
    }
}