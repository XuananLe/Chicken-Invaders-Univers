#include "Boss.h"
#include "CommonVariable.h"
const double BOSS_SCALE = 0.5;
Uint32 BOSS_startTicks = 0;
Uint32 BOSS_spriteIndex = 0;
const Uint32 BOSS_NUMBER_OF_EGGS = 9;
const Uint32 BOSS_spritetime = 100;
// IPLEMANTATION OF BOSS CONSTRUCTOR AND DESTRUCTOR
Boss::~Boss()
{
}
Boss::Boss()
{
    health_ = 3;
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
    // move_timer_ = SDL_AddTimer(1000,move_timer_callback, this);
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
    if (health_ <= 0)
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
void Boss::move_randomly_up_down_left_right()
{
    int speed = speed_;
    int current_time = SDL_GetTicks();
    if (current_time - last_time_move <= 1000)
    {
        // Move right
        if (x_direction_ == 1)
        {
            rect_.x += speed;
            if (rect_.x + rect_.w >= SCREEN_WIDTH)
            {
                x_direction_ = -1;
            }
        }
        // Move down
        else if (x_direction_ == -1)
        {
            rect_.y += speed;
            if (rect_.y + rect_.h >= SCREEN_HEIGHT)
            {
                x_direction_ = -2;
            }
        }
        // Move left
        else if (x_direction_ == -2)
        {
            rect_.x -= speed;
            if (rect_.x <= 0)
            {
                x_direction_ = -3;
            }
        }
        // Move up
        else if (x_direction_ == -3)
        {
            rect_.y -= speed;
            if (rect_.y <= 0)
            {
                x_direction_ = 1;
            }
        }
    }
    else
    {
        // last_time_move = current_time;
        x_direction_ = 1;
    }
}

void Boss::firing_eggs(MainObject *main_object)
{
    int current_time = SDL_GetTicks();
    if (health_ <= 0)
    {
        return;
    }
    if (current_time - last_egg_firing_time <= 2000)
    {
        return;
    }
    Mix_AllocateChannels(100);
    Mix_PlayChannel(-1, boss_shit, 0);
    last_egg_firing_time = current_time;
    double dx = main_object->get_rect().x - rect_.x;
    double dy = main_object->get_rect().y - rect_.y;
    double distance = sqrt(dx * dx + dy * dy);
    double unit_x = dx / distance;
    double unit_y = dy / distance;
    double speed = 10;
    double egg_vx = speed * unit_x;
    double egg_vy = speed * unit_y;
    Egg *egg = new Egg();
    Mix_AllocateChannels(100);
    egg->set_rect_cordinate(rect_.x + rect_.w / 2, rect_.y + rect_.h / 2);
    egg->set_rect_width_and_height(32, 41);
    egg->set_v_x(egg_vx);
    egg->set_v_y(egg_vy);
    Mix_PlayChannel(-1, shooting_egg_sound_, 0);
    egg_list.push_back(egg);
}
void Boss::firing_eggs()
{
    Uint32 current_time = SDL_GetTicks();
    if (current_time - last_egg_firing_time <= 2000)
    {
        return;
    }
    double egg_speed = 10;
    double angle_step = 2 * M_PI / 10;
    for (int i = 0; i < 10; i++)
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

void Boss::moving_toward_player(MainObject *main_object)
{
    Uint32 current_time = SDL_GetTicks();
    if(current_time - last_time_move <= 100)
    {
        return;
    }
    last_time_move = current_time;
    double dx = main_object->get_rect().x - Boss::rect_.x;
    double dy = main_object->get_rect().y - Boss::rect_.y;
    double distance = sqrt(dx * dx + dy * dy);
    double unit_x = dx / distance;
    double unit_y = dy / distance;
    double speed = 10;
    v_x = unit_x * speed;
    v_y = unit_y * speed;
    rect_.x += v_x;
    rect_.y += v_y;
}
void Boss::moving_like_zigzag()
{
    // double x_speed = 2;
    // double y_speed = 2;
    // double x_direction = 1;
    // double y_direction = 1;
    // double x = rect_.x + x_speed * x_direction;
    // double y = rect_.y + y_speed * y_direction;
    // if(x <= 0 || x + rect_.w >= SCREEN_WIDTH)
    // {
    //     x_direction = -x_direction;
    // }
    // if(y <= 0 || y + rect_.h >= SCREEN_HEIGHT)
    // {
    //     y_direction = -y_direction;
    // }
    // rect_.x = x;
    // rect_.y = y;
    // std::cout << rect_.x << " " << rect_.y << std::endl;
}