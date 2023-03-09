#include "CommonVariable.h"
#include "BaseObject.h"
#include "Present.h"
#include "MainObject.h"
#include "BackGround.h"
#include "ThemePlayer.h"
#include "Asteroid.h"
#include "Boss.h"
#include "Chicken.h"
const double MAIN_OBJECT_SCALE = 0.35;
const double CHICKEN_OBJECT_SCALE = 1.55;
const int number_of_asteroid = 10;
const int chicken_number = 10;
const int boss_number = 2;
bool InitData();
bool all_level_1_chicken_dead(Chicken *chicken)
{
    for (int i = 0; i < chicken_number; i++)
    {
        if (chicken[i].get_alive() == true)
        {
            return false;
        }
    }
    return true;
}
bool all_level_2_asteroid_dead(Asteroid *asteroid)
{
    for (int i = 0; i < number_of_asteroid; i++)
    {
        if (asteroid[i].get_health() > 0)
        {
            return false;
        }
    }
    return true;
}
bool all_boss_dead(Boss *boss)
{
    for (int i = 0; i < boss_number; i++)
    {
        if (boss[i].get_health() > 0)
        {
            return false;
        }
    }
    return true;
}
Asteroid *asteroid = new Asteroid[number_of_asteroid];
BackGround *back_ground = new BackGround();
MainObject *player = new MainObject();
Chicken *chicken = new Chicken[chicken_number];
ThemePlayer *theme_player = new ThemePlayer();
Boss *boss = new Boss[boss_number];

// Boss *boss = new Boss();

int main(int argc, char *argv[])
{

    srand(time(NULL));
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        // Handle error
        std::cerr << "Failed to initialize audio: " << Mix_GetError() << std::endl;
        // exit or return
    }

    back_ground->loading_background(renderer, "res/image/background(2).jpg");
    back_ground->set_speed(1);

    player->load_animation_sprite(renderer, "res/image/ship.png");
    player->set_clips();
    player->set_rect_cordinate(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    for (int i = 0; i < chicken_number; i++)
    {
        chicken[i].generate_present();
        chicken[i].load_animation_sprite(renderer, "res/image/chicken123.png");
        chicken[i].set_clips();
        chicken[i].set_rect_cordinate(100 + i * 100, 100);
        chicken[i].set_rect_width_and_height(75, 68);
        chicken[i].set_alive(true);
        chicken[i].set_speed(3);
        if (chicken[i].get_texture() == NULL)
        {
            std::cout << "Chicken texture is not null" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < number_of_asteroid; i++)
    {
        asteroid[i].set_width_height(75, 68);
        asteroid[i].set_is_on_screen(true);
        asteroid[i].set_speed(2);
    }
    theme_player->set_volume(12);

    // Asteroid *asteroid = new Asteroid();
    for (int i = 0; i < boss_number; i++)
    {
        boss[i].load_animation_sprite(renderer, "res/image/boss.png");
        boss[i].set_clips();
        boss[i].set_rect_cordinate(300 + i * 100, 300);
    }
    // if(boss -> get_texture() == NULL)
    // {
    //     std::cout << "Boss texture is null" << std::endl;
    //     exit(EXIT_FAILURE);
    // }
    int level = 1;
    Mix_AllocateChannels(100);
    bool isRunning = true;
    bool isPause = false;
    while (isRunning)
    {
        Uint32 current_time = SDL_GetTicks();
        if (player->get_health() <= 0)
        {
            isRunning = false;
        }
        Mix_ResumeMusic();
        back_ground->render_background_scroll(renderer);
        back_ground->update_background_scroll();
        back_ground->set_speed(2);

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = false;
                }
                // if (event.key.keysym.sym == SDLK_SPACE)
                // {
                //     isPause = true;
                //     while(isPause == true)
                //     {
                //         SDL_Delay(50);
                //         SDL_PollEvent(&event);
                //         if(event.key.keysym.sym == SDLK_a)
                //         {
                //                     isPause = false;
                //         }
                //         break;
                //     }
                // }
            }
            // handling movement
            player->handling_movement(event);
            player->handling_shooting(event);
        }

        if (level == 1)
        {
            for (int i = 0; i < chicken_number; i++)
            {
                chicken[i].render_animation(renderer, 1.55);
                chicken[i].handle_shooting_eggs(player);
                chicken[i].moving_back_and_forth();
                chicken[i].update_the_eggs();
                chicken[i].render_the_eggs();
                chicken[i].generate_present();
            }
            // player->process_if_hit_by_asteroid(asteroid);
            for (int i = 0; i < chicken_number; i++)
            {
                player->process_if_hit_by_chicken(&chicken[i]);
                player->processing_if_got_present(chicken[i].get_present());
                player->process_shooting_if_hit_chicken(&chicken[i]);
                player->process_if_hit_by_eggs(&chicken[i]);
                player->process_if_eat_wing_rect(&chicken[i]);
            }
            if (all_level_1_chicken_dead(chicken) == true)
            {
                level = 2;
            }
            if(player->get_health() <= 0)
            {
                isRunning = false;
            }
        }
        else if (level == 2)
        {
            for (int i = 0; i < number_of_asteroid; i++)
            {
                asteroid[i].render_with_angle();
                asteroid[i].moving_diagonal();
                asteroid[i].spinning();
                player->process_if_hit_by_asteroid(&asteroid[i]);
            }
            if (all_level_2_asteroid_dead(asteroid) == true)
            {
                level = 3;
            }
        }
        else if (level == 3)
        {
            for(int i = 0; i < boss_number; i++)
            {
            boss[i].render_animation(renderer, 1);
            boss[i].move_randomly_up_down_left_right();
            boss[i].firing_eggs(player);
            boss[i].update_the_eggs();
            boss[i].render_the_eggs();
            player->processing_if_hit_by_boss(&boss[i]);
            player->processing_if_hit_by_boss_egg(&boss[i]);
            }
            if(all_boss_dead(boss) == true)
            {
                isRunning = false;
            }
        }
        player->render_shooting();
        player->render_animation(renderer, MAIN_OBJECT_SCALE);

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }

    // FREEING METHOD AND QUITTING
    player->free();
    chicken->free();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}

bool InitData()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        // Handle error
        std::cerr << "Failed to initialize audio: " << Mix_GetError() << std::endl;
        // exit or return
    }

    window = SDL_CreateWindow("Chicken Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cerr << "Error creating SDL renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        std::cerr << "Error initializing SDL_image: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}
