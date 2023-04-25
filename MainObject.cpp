#include "MainObject.h"
#include "Chicken.h"
#include <memory>
Uint32 MAIN_OBJECT_startTicks = 0;
Uint32 MAIN_OBJECT_spriteIndex = 0;
const Uint32 MAIN_OBJECT_spritetime = 100;

// IMPLEMENT CONSTRUTOR AND DESTRUCTOR
MainObject::MainObject()
{
    texture_ = NULL;
    is_win = false;
    spinning_angle = 0;
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    shoot_sound = Mix_LoadWAV("res/sound/arrow_firing.wav");
    eat_wing_sound = Mix_LoadWAV("res/sound/GET_FOOD.wav");
    witdth_of_sprite = 0;
    hit_sound = Mix_LoadWAV("res/sound/player_hit.wav");
    getting_present_sound = Mix_LoadWAV("res/sound/get_weapon.wav");
    health = 10;
    ammo_level = 0;
    height_of_sprite = 0;
    rect_.x = SCREEN_WIDTH / 2;
    rect_.y = SCREEN_HEIGHT - 100;
    rect_.w = 0;
    rect_.h = 0;
    slow_move_timer = SDL_GetTicks();
}
MainObject::~MainObject()
{
}

// IMPLEMENT SETTING CLIPS RECT
void MainObject::set_clips()
{
    if (witdth_of_sprite >= 0 && height_of_sprite >= 0)
    {
        for (int i = 0; i < MAIN_OBJECT_NUMS_FRAME; i++)
        {
            frame_clip[i].x = i * witdth_of_sprite;
            frame_clip[i].y = 0;
            frame_clip[i].w = witdth_of_sprite;
            frame_clip[i].h = height_of_sprite;
        }
        rect_.w = witdth_of_sprite;
        rect_.h = height_of_sprite;
    }
}

// IMPLEMENT LOAD ANIMATION SPRITE
void MainObject::load_animation_sprite(SDL_Renderer *renderer, const char *file)
{
    SDL_Surface *loadSurface = IMG_Load(file);
    if (loadSurface != NULL)
    {
        texture_ = SDL_CreateTextureFromSurface(renderer, loadSurface);
        witdth_of_sprite = loadSurface->w / MAIN_OBJECT_NUMS_FRAME;
        height_of_sprite = loadSurface->h;
        SDL_FreeSurface(loadSurface);
    }
}

void MainObject::render_animation(SDL_Renderer *renderer, const double &scale)
{
    if (health <= 0)
        return;
    if(slow_move == true)
    {
        slowly_move_from_bottom();
        return;
    }
    Uint32 currentTicks = SDL_GetTicks();
    if (currentTicks - MAIN_OBJECT_startTicks > MAIN_OBJECT_spritetime)
    {
        MAIN_OBJECT_spriteIndex = (MAIN_OBJECT_spriteIndex + 1) % 4;
        MAIN_OBJECT_startTicks = currentTicks;
    }
    rect_.w = static_cast<int>(witdth_of_sprite * scale);
    rect_.h = static_cast<int>(height_of_sprite * scale);

    SDL_Rect destRect = {rect_.x, rect_.y, static_cast<int>(witdth_of_sprite * scale), static_cast<int>(height_of_sprite * scale)};

    SDL_RenderCopy(renderer, texture_, &frame_clip[MAIN_OBJECT_spriteIndex], &destRect);
}

// IMPLEMENT SET AND GET METHOD IN RECTANGLE
void MainObject::set_rect_cordinate(const int &x, const int &y)
{
    rect_.x = x;
    rect_.y = y;
}
void MainObject::set_rect_cordinate_width_and_height(const int &x, const int &y, const int &width, const int &height)
{
    rect_.x = x;
    rect_.y = y;
    rect_.w = width;
    rect_.h = height;
}
void MainObject::set_rect_width_and_height(const int &width, const int &height)
{
    rect_.w = width;
    rect_.h = height;
}
SDL_Rect MainObject::get_rect() const
{
    return rect_;
}
SDL_Rect MainObject::get_rect_width_height_with_scale(const double &scale) const
{
    SDL_Rect rect = {rect_.x, rect_.y, static_cast<int>(rect_.w * scale), static_cast<int>(rect_.h * scale)};
    return rect;
}

// IMPLEMENT HANDLING MOVEMENT
void MainObject::handling_movement(SDL_Event &event)
{
    if (health <= 0 || slow_move == true)
        return;
    if(rect_.y >= 901) slow_move = false;
    if (event.type == SDL_MOUSEMOTION)
    {

        int cursor_x = event.motion.x;
        int cursor_y = event.motion.y;

        int ship_end_x = rect_.x + rect_.w / 2;
        int ship_end_y = rect_.y + rect_.h / 2;

        int new_x = cursor_x - rect_.w / 2;
        int new_y = cursor_y - rect_.h / 2;

        // Check if the ship is within the left and right edges of the screen
        if (new_x < 0)
        {
            new_x = 0;
        }
        else if (new_x + rect_.w > SCREEN_WIDTH)
        {
            new_x = SCREEN_WIDTH - rect_.w;
        }

        // Check if the ship is within the top and bottom edges of the screen
        if (new_y < 0)
        {
            new_y = 0;
        }
        else if (new_y + rect_.h / 2 > SCREEN_HEIGHT)
        {
            new_y = SCREEN_HEIGHT - rect_.h;
        }

        rect_.x = new_x;
        rect_.y = new_y - rect_.h / 2;
    }
    else
        return;
}

// IMPLEMENT HANDLING SHOOTING
void MainObject::handling_shooting(SDL_Event &event)
{
    if (health <= 0 || slow_move == true)
        return;


    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            Mix_AllocateChannels(100);
            AmmoObject *ammo = new AmmoObject();
            std::string path = "res/image/";
            std::string ammo_type_123 = "";
            // Set ammo type
            if (ammo_type == 2)
            {
                ammo_type_123 = "BORON";
                ammo->set_speed(10);
                switch (MainObject::ammo_level)
                {
                case 0:
                    ammo->set_damage(2);
                    break;
                case 1:
                    ammo->set_damage(3);
                    break;
                case 2:
                    ammo->set_damage(4);
                    break;
                case 3:
                    ammo->set_damage(5);
                    break;
                default:
                    ammo->set_damage(0);
                    break;
                }
            }
            else if (ammo_type == 1)
            {
                ammo_type_123 = "NEUTRON";
                ammo->set_speed(20);
                switch (MainObject::ammo_level)
                {
                case 0:
                    ammo->set_damage(1);
                    break;
                case 1:
                    ammo->set_damage(2);
                    break;
                case 2:
                    ammo->set_damage(3);
                    break;
                case 3:
                    ammo->set_damage(4);
                    break;
                default:
                    ammo->set_damage(0);
                    break;
                }
            }
            else
            {
                std::cout << "MainObject.cpp INVALID AMMO TYPE" << std::endl;
                exit(EXIT_FAILURE);
            }
            std::string path_ammo = path + ammo_type_123 + std::to_string(ammo_level) + ".png";

            ammo->load_static_ammo_picture(renderer, path_ammo.c_str());
            if (ammo->get_texture() == NULL)
            {
                std::cout << "ERROR: at file MainObject.cpp " << SDL_GetError() << std::endl;
                std::cout << IMG_GetError() << std::endl;
                exit(0);
            }

            ammo->set_alive(true);
            ammo->set_can_move(true);
            ammo->set_rect_cordinate(rect_.x + rect_.w / 2 - 10, rect_.y);
            ammo_list.push_back(ammo);

            Mix_VolumeChunk(shoot_sound, 12);
            if (Mix_PlayChannel(-1, shoot_sound, 0) == -1)
            {
                printf("Unable to play WAV file: %s\n", Mix_GetError());
                exit(0);
            }
        }
        else if (event.button.button == SDL_BUTTON_RIGHT)
        {
            // TO DO
        }
        else
            return;
    }
    else
        return;
}
// IMPLEMENT RENDERING SHOOTING AMMO
void MainObject::render_shooting()
{
    if (health <= 0)
        return;
    if(slow_move == true) return;

    // Remove any bullets that have gone off-screen or hit a target.
    for (auto it = ammo_list.begin(); it != ammo_list.end();)
    {
        if ((*it)->is_alive() == true)
        {
            (*it)->update();
            ++it;
        }
        else
        {
            delete *it;
            it = ammo_list.erase(it);
        }
    }

    // Render all bullets.
    for (auto it = ammo_list.begin(); it != ammo_list.end(); ++it)
    {
        (*it)->render(renderer);
    }
}

// IMPLEMENT Processing the shooting
void MainObject::process_shooting_if_hit_chicken(Chicken *chicken)
{
    if (health <= 0 || chicken->get_health() <= 0)
        return;
    for (int i = 0; i < ammo_list.size(); i++)
    {
        if (check_collision_2_rect(ammo_list[i]->get_rect(), chicken->get_rect()))
        {
            chicken->play_hit_sound();
            chicken->set_health(chicken->get_health() - ammo_list[i]->get_damage());
            if (chicken->get_health() <= 0)
            {
                chicken->set_rect_cordinate_width_and_height(-9999, -9999, 0, 0);
                chicken->set_speed(0);
                chicken->set_alive(false);
            }
            ammo_list[i]->set_alive(false);
            ammo_list[i]->set_speed(0);
            ammo_list[i]->set_can_move(false);
            return;
        }
    }
}
// IMPLEMENT if eat wing
void MainObject::process_if_eat_wing_rect(Chicken *chicken)
{
    if (health <= 0)
        return;
    if ((chicken->get_health() <= 0) && (check_collision_2_rect(chicken->get_wing_rect(), rect_)) == true && (chicken->get_on_screen() == true) && chicken->get_has_wing() == true)
    {
        MainObject::number_of_wings += 1;
        Mix_AllocateChannels(100);
        Mix_PlayChannelTimed(-1, eat_wing_sound, 0, 1000);
        chicken->set_on_screen(false);
    }
}
// IMPLEMENTATION OF IF HIT BY CHICKEN
void MainObject::process_if_hit_by_chicken(Chicken *chicken)
{
    if (health <= 0)
        return;
    if ((chicken->get_health() >= 1) && (check_collision_2_rect(chicken->get_rect(), rect_) == true) && (chicken->get_on_screen() == true))
    {
        if(slow_move == true) return;
        Explosion *explosion = new Explosion();
        explosion->set_is_on_screen(true);
        explosion->load_animation_sprite(renderer, "res/image/explosion.png");
        explosion->set_clips();
        explosion->set_coordinates(MainObject::rect_.x, MainObject::rect_.y);
        explosion_list.push_back(explosion);
        Mix_AllocateChannels(100);
        Mix_PlayChannelTimed(-1, hit_sound, 0, 1000);
        Mix_VolumeChunk(hit_sound, 64);
        chicken->set_health(-1);
        chicken->set_on_screen(false);
        chicken->set_alive(false);
        MainObject::health = MainObject::health - 1;
        set_slow_move();
        return;
    }
}

void MainObject::process_if_hit_by_eggs(Chicken *chicken)
{
    if (health <= 0)
        return;
    for (int i = 0; i < chicken->get_eggs_list().size(); i++)
    {
        if (check_collision_2_rect(chicken->get_eggs_list()[i]->get_rect(), rect_) == true && chicken->get_eggs_list()[i]->get_is_broken() == false)
        {
            if (chicken->get_eggs_list()[i]->get_alive() == false)
                return;

            Explosion *explosion = new Explosion();
            explosion->set_is_on_screen(true);
            explosion->load_animation_sprite(renderer, "res/image/explosion.png");
            explosion->set_clips();
            explosion->set_coordinates(MainObject::rect_.x, MainObject::rect_.y);
            explosion_list.push_back(explosion);
            // early return technique
            Mix_AllocateChannels(100);
            Mix_PlayChannelTimed(-1, hit_sound, 0, 1000);
            Mix_VolumeChunk(hit_sound, 80);
            health = health - 1;
            chicken->get_eggs_list()[i]->set_alive(false);
            
            set_slow_move();

            return;
        }
    }
}


void MainObject::processing_if_hit_by_boss_egg(Boss *boss)
{
    if (health <= 0)
        return;
    for (int i = 0; i < boss->get_egg_list().size(); i++)
    {
        if (check_collision_2_rect(boss->get_egg_list()[i]->get_rect(), rect_) == true)
        {
            if (boss->get_egg_list()[i]->get_alive() == false)
                return;
            // early return technique

            Explosion *explosion = new Explosion();
            explosion->set_is_on_screen(true);
            explosion->load_animation_sprite(renderer, "res/image/explosion.png");
            explosion->set_clips();
            explosion->set_coordinates(MainObject::rect_.x, MainObject::rect_.y);
            explosion_list.push_back(explosion);

            Mix_AllocateChannels(100);
            Mix_VolumeChunk(hit_sound, 80);
            Mix_PlayChannelTimed(-1, hit_sound, 0, 1000);
            MainObject::health = MainObject::health - 1;
            boss->get_egg_list()[i]->set_alive(false);
            set_slow_move();
            return;
        }
    }
}

void MainObject::processing_if_hit_by_boss(Boss *boss)
{
    if (health <= 0 || boss->get_health() <= 0)
        return;

    if (check_collision_2_rect(boss->get_rect(), rect_) == true && slow_move == false)
    {
        Explosion *explosion = new Explosion();

        explosion->set_is_on_screen(true);
        explosion->load_animation_sprite(renderer, "res/image/explosion.png");
        explosion->set_clips();
        explosion->set_coordinates(MainObject::rect_.x - 15, MainObject::rect_.y - 15);
        explosion_list.push_back(explosion);

        Mix_AllocateChannels(100);
        Mix_PlayChannelTimed(-1, hit_sound, 0, 1000);

        health = health - 1;

        set_slow_move();
        
        return;
    }

    for (int i = 0; i < ammo_list.size(); i++)
    {
        if (check_collision_2_rect(ammo_list[i]->get_rect(), boss->get_rect()) and ammo_list[i]->get_can_move() == true)
        {
            Mix_AllocateChannels(100);
            boss->set_health(boss->get_health() - ammo_list[i]->get_damage());
            ammo_list[i]->set_alive(false);
            ammo_list[i]->set_can_move(false);
            Mix_PlayChannelTimed(-1, hit_sound, 0, 1000);
            return;
        }
    }
}

void MainObject::process_if_hit_by_asteroid(Asteroid *asteroid)
{
    if (health <= 0)
        return;
    if (check_collision_2_rect(asteroid->get_rect(), rect_) == true && asteroid->get_is_on_screen() == true)
    {
        Mix_AllocateChannels(100);
        MainObject::health--;
        Mix_PlayChannelTimed(-1, hit_sound, 0, 1000);
        Explosion *explosion = new Explosion();
        explosion->set_is_on_screen(true);
        explosion->load_animation_sprite(renderer, "res/image/explosion.png");
        explosion->set_clips();
        explosion->set_coordinates(MainObject::rect_.x, MainObject::rect_.y);
        explosion_list.push_back(explosion);
        asteroid->set_health(-1);
        asteroid->set_is_on_screen(false);
        asteroid->set_rect_cordinate_and_width_height(-9999, -9999, 0, 0);
        set_slow_move();
        return;
    }
    for (int i = 0; i < ammo_list.size(); i++)
    {
        if (check_collision_2_rect(ammo_list[i]->get_rect(), asteroid->get_rect()) and ammo_list[i]->get_can_move() == true and asteroid->get_is_on_screen() == true)
        {
            asteroid->set_health(asteroid->get_health() - 1);
            if (asteroid->get_health() <= 0)
            {
                asteroid->set_rect_cordinate_and_width_height(-9999, -9999, 0, 0);
                asteroid->set_is_on_screen(false);
            }
            ammo_list[i]->set_can_move(false);
            ammo_list[i]->set_alive(false);
            return;
        }
    }
}
// IMPLEMENT PROCESSING IF GET A BONUS
void MainObject::processing_if_got_present(Present *present)
{
    if (health <= 0)
        return;
    if (present == NULL)
    {
        return;
    }
    if (check_collision_2_rect(present->get_rect(), rect_) == true && present->get_is_on_screen() == true)
    {
        Mix_AllocateChannels(100);
        Mix_PlayChannelTimed(-1, getting_present_sound, 0, 1000);
        present->set_is_on_screen(false);
        if (present->get_kind_of_present() == 0)
        {

            // 10 is the max health at this moment
            if (MainObject::health >= 10)
                return;
            MainObject::health += 1;
        }
        else if (present->get_kind_of_present() == 1 || present->get_kind_of_present() == 3)
        {

            if (present->get_kind_of_present() == 1)
            {
                MainObject::ammo_type = 1;
            }
            else
                MainObject::ammo_type = 2;

            if (MainObject::ammo_level < 3)
            {
                MainObject::ammo_level = MainObject::ammo_level + 1;
            }
            else
                return;
        }
        else
        {
            return;
        }
    }
}

void MainObject::slowly_move_from_bottom()
{
    if(slow_move == false) return;
    if(rect_.y <= 800) 
    {
        slow_move = false;
    }

    rect_.y -= 10; 
    Uint32 currentTicks = SDL_GetTicks();
    if (currentTicks - MAIN_OBJECT_startTicks > MAIN_OBJECT_spritetime)
    {
        MAIN_OBJECT_spriteIndex = (MAIN_OBJECT_spriteIndex + 1) % MAIN_OBJECT_NUMS_FRAME;
        MAIN_OBJECT_startTicks = currentTicks;
    }
    rect_.w = static_cast<int>(witdth_of_sprite * MAIN_OBJECT_SCALE);
    rect_.h = static_cast<int>(height_of_sprite * MAIN_OBJECT_SCALE);

    SDL_Rect destRect = {rect_.x, rect_.y, rect_.w, rect_.h};

    SDL_RenderCopy(renderer, texture_, &frame_clip[MAIN_OBJECT_spriteIndex], &destRect);
}

// IMPLEMENT FREE METHOD
void MainObject::free()
{
    if (texture_ != NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
        witdth_of_sprite = 0;
        height_of_sprite = 0;
        rect_.x = 0;
        rect_.y = 0;
        rect_.w = 0;
        rect_.h = 0;
        Mix_FreeChunk(shoot_sound);
    }
}
