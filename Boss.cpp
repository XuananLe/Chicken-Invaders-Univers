#include "Boss.h"
#include "CommonVariable.h"
const double BOSS_SCALE = 0.5;
Uint32 BOSS_startTicks = 0;
Uint32 BOSS_spriteIndex = 0;
const Uint32 BOSS_NUMBER_OF_EGGS = 9;
const Uint32 BOSS_spritetime = 100;
const Uint32 MOVE_INTERVAL_MS = 1000; // Move every 1 seconds   
const double ATTACK_DISTANCE_SQUARED = 10000.0; // 100 pixels squared
double lerp(double a, double b, double t)
{
    return (1.0 - t) * a + t * b;
}
// IPLEMANTATION OF BOSS CONSTRUCTOR AND DESTRUCTOR
Boss::Boss()
{
    health_ = 100;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 200;
    rect_.h = 117;
    speed_ = 5;
    v_x = 0;
    v_y = 0;
    last_move_ticks_ = SDL_GetTicks();
    last_fire_ticks_ = SDL_GetTicks();
    x_direction_ = 1;
    last_time_move = SDL_GetTicks();
    texture_ = IMG_LoadTexture(renderer, "res/image/boss.png");
    last_egg_time = SDL_GetTicks();
    width_of_sprite = 0;
    height_of_sprite = 0;
    last_egg_firing_time = SDL_GetTicks();
    is_on_screen = true;
    shooting_egg_sound_ = Mix_LoadWAV("res/sound/Laying_eggs.wav");
    boss_shit = Mix_LoadWAV("res/sound/Ci1bosshit.wav");
    dir_x = 0;
    dir_y = 0;
    prev_collision_dir_ = "x";

}
Boss::~Boss()
{

}

void Boss::set_clips()
{
    if (width_of_sprite >= 0 || height_of_sprite >= 0)
    {
        for (int i = 0; i < BOSS_NUMS_FRAME; i++)
        {
            frame_clip[i].x = i * 200;
            frame_clip[i].y = 0;
            frame_clip[i].w = 200;
            frame_clip[i].h = 117;
        }
        rect_.w = 200;
        rect_.h = 117;
    }
}

void Boss::load_animation_sprite(SDL_Renderer *renderer, const char *file)
{

    texture_ = IMG_LoadTexture(renderer, file);

    // Set the texture blend mode to enable alpha blending
    SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND);
    // set the color mod to magenta (RGB: 255, 0, 255)
    // Set the alpha (transparency) value of the texture
    SDL_SetTextureAlphaMod(texture_, 200);

    if (texture_ == NULL)
    {
        std::cout << "Failed to load the texture" << std::endl;
    }
    else
    {

        rect_.w = 200;
        rect_.h = 117;
    }
}

void Boss::render_animation(SDL_Renderer *renderer, const double &scale)
{
    if (!is_on_screen)
    {
        return;
    }
    if (Boss::health_ <= 0)
    {
        rect_.x = -99999;
        rect_.y = -99999;
        rect_.w = 0;
        rect_.h = 0;
        return;
    }
    // early return technique
    if (health_ > 0)
    {
        std::cout << "Rect of the boss" << rect_.x << " " << rect_.y << std::endl;
        Uint32 currentTicks = SDL_GetTicks();
        if (currentTicks - BOSS_startTicks > BOSS_spritetime)
        {
            BOSS_spriteIndex = (BOSS_spriteIndex + 1) % BOSS_NUMS_FRAME;
            BOSS_startTicks = currentTicks;
        }
        // set up the rendering destination rectangle
        SDL_Rect destRect = {rect_.x, rect_.y, static_cast<int>(200 * scale), static_cast<int>(117 * scale)};

        // calculate the angle of rotation based on the current time
        double angle = static_cast<double>(currentTicks % 360);

        SDL_Point center = {destRect.w / 2, destRect.h / 2};
        // render the sprite with rotation
        SDL_RenderCopy(renderer, texture_, &frame_clip[BOSS_spriteIndex], &destRect);
    }
}

void Boss::firing_eggs()
{
    Uint32 current_time = SDL_GetTicks();
    if (current_time - last_egg_firing_time <= 1000)
    {
        return;
    }
    double egg_speed = 5;
    // 5 is the number of eggs
    double angle_step = 2 * M_PI / 5;
    for (int i = 0; i < 5; i++)
    {
        double angle = i * angle_step + (double)rand() / RAND_MAX * angle_step;
        double unit_x = cos(angle);
        double unit_y = sin(angle);
        double bullet_vx = egg_speed * unit_x;
        double bullet_vy = egg_speed * unit_y;
        Egg *egg = new Egg();
        egg->set_rect_cordinate(rect_.x + rect_.w / 2, rect_.y + rect_.h / 2);
        egg->set_rect_width_and_height(32, 41);
        egg->set_v_x(bullet_vx);
        egg->set_v_y(bullet_vy);
        egg_list.push_back(egg);
    }
    last_egg_firing_time = current_time;
}

void Boss::moving_toward_player(MainObject* main_object)
{
    Uint32 current_time = SDL_GetTicks();
    if(main_object->get_slow_move() == true) return;
    if (current_time - last_time_move <= 30)
    {
        return;
    }
    double distance_x = main_object->get_rect().x - rect_.x;
    double distance_y = main_object->get_rect().y - rect_.y;
    double distance = sqrt(distance_x * distance_x + distance_y * distance_y);
    double unit_x = distance_x / distance;
    double unit_y = distance_y / distance;
    Boss::speed_ = 10;
    v_x = Boss::speed_ * unit_x;
    v_y = Boss::speed_ * unit_y;
    rect_.x += v_x;
    rect_.y += v_y;
    last_time_move = current_time;
}


void Boss::render_health_bar()
{
    if (Boss::health_ <= 0)
    {
        return;
    }
    health_bar_rect.x = rect_.x;
    health_bar_rect.y = rect_.y - 10;
    SDL_Rect bg_rect = {health_bar_rect.x, health_bar_rect.y, health_bar_width, health_bar_height};
    SDL_Rect fg_rect = {health_bar_rect.x, health_bar_rect.y, health_bar_width, health_bar_height};
    fg_rect.w = health_bar_width * Boss::health_ / 100;
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(renderer, &bg_rect);
    SDL_SetRenderDrawColor(renderer, fgColor.r, fgColor.g, fgColor.b, fgColor.a);
    SDL_RenderFillRect(renderer, &fg_rect);
}

