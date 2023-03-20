#include "CommonVariable.h"
#include "BaseObject.h"
#include "Present.h"
#include "MainObject.h"
#include "BackGround.h"
#include "ThemePlayer.h"
#include "menu.h"
#include "Asteroid.h"
#include "Boss.h"
#include "Chicken.h"
const double MAIN_OBJECT_SCALE = 0.35;
const double CHICKEN_OBJECT_SCALE = 1.55;
const int number_of_asteroid = 20;
const int chicken_number = 15;
bool is_paused = false;
bool player_want_to_play_again = false;
bool game_is_truly_end = false;
int level = 0;
const int boss_number = 2;
Uint64 SCORE = SDL_GetTicks();
Mix_Music *background_music     = NULL;

// ======================= Enity Variable ======================= \\
bool InitData();

GameMenu *menu = new GameMenu();

Present *present = new Present();

Asteroid *asteroid = new Asteroid[number_of_asteroid];

BackGround *back_ground = new BackGround();

MainObject *player = new MainObject();

Chicken *chicken = new Chicken[chicken_number];

Chicken *chicken2 = new Chicken[chicken_number];

Boss *boss = new Boss[boss_number];

Uint32 last_time_present_fall_down = SDL_GetTicks();

// ======================= Init function =======================

int init_system()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        // Handle error
        std::cerr << "Failed to initialize audio: " << Mix_GetError() << std::endl;
        // exit or return
    }
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
    return 0;
}

void init_player(MainObject *player)
{
    player->load_animation_sprite(renderer, "res/image/ship.png");
    player->set_clips();
    player->set_rect_cordinate(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void init_back_ground(BackGround *back_ground)
{
    back_ground->loading_background(renderer, "res/image/background(2).jpg");
    back_ground->set_speed(1);
}

void init_asteroid(Asteroid *asteroid)
{
    for (int i = 0; i < number_of_asteroid; i++)
    {
        asteroid[i].set_width_height(75, 68);
        asteroid[i].set_is_on_screen(true);
        asteroid[i].set_speed(2);
    }
}

void init_random_present(Present *present)
{
    present->set_is_on_screen(true);
    present->set_rect_cordinate(rand() % SCREEN_WIDTH, 0);
    present->set_kind_of_present(0);
}

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

bool all_level_1_2_chicken_dead(Chicken *chicken2)
{
    for (int i = 0; i < chicken_number; i++)
    {
        if (chicken2[i].get_alive() == true)
            return false;
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

void init_chicken_level_1(Chicken *chicken)
{
    for (int i = 0; i < chicken_number / 3; i++)
    {
        chicken[i].generate_present();
        chicken[i].load_animation_sprite(renderer, "res/image/chicken123.png");
        chicken[i].set_clips();
        chicken[i].set_rect_cordinate(100 + i * 100, -100);
        chicken[i].set_rect_width_and_height(75, 68);
        chicken[i].set_alive(true);
        chicken[i].set_speed(3);
        if (chicken[i].get_texture() == NULL)
        {
            std::cout << "Chicken texture is not null" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    for (int i = chicken_number / 3; i < 2 * (chicken_number / 3); i++)
    {
        chicken[i].generate_present();
        chicken[i].load_animation_sprite(renderer, "res/image/chicken123.png");
        chicken[i].set_clips();
        chicken[i].set_rect_cordinate(100 + (i - (chicken_number / 3)) * 100, 0);
        chicken[i].set_rect_width_and_height(75, 68);
        chicken[i].set_alive(true);
        chicken[i].set_speed(3);
        if (chicken[i].get_texture() == NULL)
        {
            std::cout << "Chicken texture is not null" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 2 * chicken_number / 3; i < chicken_number; i++)
    {
        chicken[i].generate_present();
        chicken[i].load_animation_sprite(renderer, "res/image/chicken123.png");
        chicken[i].set_clips();
        chicken[i].set_rect_cordinate(100 + (i - (2 * chicken_number / 3)) * 100, 100);
        chicken[i].set_rect_width_and_height(75, 68);
        chicken[i].set_alive(true);
        chicken[i].set_speed(3);
        if (chicken[i].get_texture() == NULL)
        {
            std::cout << "Chicken texture is not null" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

void init_chicken_level_1_2(Chicken *chicken)
{
    for (int i = 0; i < chicken_number; i++)
    {
        chicken[i].generate_present();
        chicken[i].load_animation_sprite(renderer, "res/image/chicken123.png");
        chicken[i].set_clips();
        chicken[i].set_rect_cordinate(i * 100, chicken[i].get_rect().w);
        chicken[i].set_rect_width_and_height(75, 68);
        chicken[i].set_alive(true);
        chicken[i].set_speed(3);
        if (chicken[i].get_texture() == NULL)
        {
            std::cout << "Chicken texture is not null" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

void update_game_state()
{
    SDL_RenderPresent(renderer);
    if (is_paused == false)
        SDL_RenderClear(renderer);
}

void process_chicken_vs_player(Chicken *chicken, MainObject *player)
{
    if (is_paused == true)
        return;
    for (int i = 0; i < chicken_number; i++)
    {
        chicken[i].render_animation(renderer, 1.55);
        chicken[i].handle_shooting_eggs(player);
        chicken[i].moving_diagnoally();
        chicken[i].update_the_eggs();
        chicken[i].render_the_eggs();
        chicken[i].generate_present();
    }
    for (int i = 0; i < chicken_number; i++)
    {
        player->process_if_hit_by_chicken(&chicken[i]);
        player->processing_if_got_present(chicken[i].get_present());
        player->process_shooting_if_hit_chicken(&chicken[i]);
        player->process_if_hit_by_eggs(&chicken[i]);
        player->process_if_eat_wing_rect(&chicken[i]);
    }
}

void play_music_level(int level, Mix_Music *music)
{
    if (is_paused == true)
        return;
    if (level == 0)
    {
        music = Mix_LoadMUS("res/sound/MENU_THEME.mp3");
        if (music == NULL)
        {
            std::cout << "Music is not loaded" << std::endl;
            exit(EXIT_FAILURE);
        }
        Mix_PlayMusic(music, -1);
    }
    if (level == 1)
    {
        music = Mix_LoadMUS("res/sound/level_1_theme.mp3");
        if (music == NULL)
        {
            std::cout << "Music is not loaded" << std::endl;
            exit(EXIT_FAILURE);
        }
        Mix_PlayMusic(music, -1);
    }
    if (level == 2)
    {
        music = Mix_LoadMUS("res/sound/asteroid_level.mp3");
        if (music == NULL)
        {
            std::cout << "Music is not loaded" << std::endl;
            exit(EXIT_FAILURE);
        }
        Mix_PlayMusic(music, -1);
    }
    if (level == 3)
    {
        music = Mix_LoadMUS("res/sound/boss_theme.mp3");
        if (music == NULL)
        {
            std::cout << "Music is not loaded" << std::endl;
            exit(EXIT_FAILURE);
        }
        Mix_PlayMusic(music, -1);
    }
}

void common_process(MainObject *player, Present *present, SDL_Event &event)
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            exit(EXIT_SUCCESS);
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_SPACE)
            {
                is_paused = !is_paused;
            }
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                exit(EXIT_SUCCESS);
            }
        }
        if (is_paused == true)
            break;
        player->handling_movement(event);
        player->handling_shooting(event);
    }
    if (is_paused == true)
        return;

    Uint32 current_time = SDL_GetTicks();
    if ((current_time - last_time_present_fall_down) >= 10000 && present->get_is_on_screen() == false)
    {
        present->set_is_on_screen(true);
        present->set_rect_cordinate(rand() % SCREEN_WIDTH, 0);
        present->set_kind_of_present(0);
        last_time_present_fall_down = current_time;
    }

    back_ground->render_background_scroll(renderer);
    back_ground->update_background_scroll();
    back_ground->set_speed(2);

    present->render();
    present->update();

    player->processing_if_got_present(present);
    player->render_shooting();
    player->render_animation(renderer, MAIN_OBJECT_SCALE);
}

void init_boss(Boss *boss)
{
    if (is_paused == true) return;
    boss[0].load_animation_sprite(renderer, "res/image/boss.png");
    boss[0].set_clips();
    boss[0].set_rect_cordinate(100, 100);
    boss[1].load_animation_sprite(renderer, "res/image/boss.png");
    boss[1].set_clips();
    boss[1].set_rect_cordinate(SCREEN_WIDTH - 100, 100);
}


void init_menu(GameMenu *menu)
{
    if (menu->get_texture() == NULL)
    {
        exit(EXIT_FAILURE);
    }
}

void process_astroid_vs_player(Asteroid *asteroid, MainObject *player)
{
    if (is_paused == true)
        return;
    for (int i = 0; i < number_of_asteroid; i++)
    {
        asteroid[i].render_with_angle();
        asteroid[i].moving_diagonal();
        asteroid[i].spinning();
        player->process_if_hit_by_asteroid(&asteroid[i]);
    }
} //
void intro_before_level(int level)
{
    Uint32 current_time = SDL_GetTicks();
    Uint32 last_time = current_time;
    while (last_time - current_time <= 5000)
    {
        last_time = SDL_GetTicks();
        common_process(player, present, event);
        menu->render_before_level(level);
        if (menu != NULL)
        {
            if (is_paused == false)
            {
                menu->render_time();
            }
            menu->render_health_bar(player);
        }
        update_game_state();
    }
}

void process_boss_vs_player(Boss *boss, MainObject *player)
{
    if (is_paused == true)
        return;
    for (int i = 0; i < boss_number; i++)
    {
        boss[i].render_animation(renderer, 1);
        boss[i].moving_toward_player(player);
        boss[i].firing_eggs();
        boss[i].update_the_eggs();
        boss[i].render_the_eggs();
        player->processing_if_hit_by_boss(&boss[i]);
        player->processing_if_hit_by_boss_egg(&boss[i]);
    }
}

// ==================== MAIN ====================
int main(int argc, char *argv[])
{
    if (TTF_Init() < 0)
    {
        std::cerr << "Failed to initialize SDL2_ttf: " << TTF_GetError() << std::endl;
        return 1;
    }

    srand(time(NULL));
    init_menu(menu);
    init_back_ground(back_ground);
    init_chicken_level_1(chicken);
    init_chicken_level_1_2(chicken2);
    init_random_present(present);
    init_asteroid(asteroid);
    init_player(player);
    init_boss(boss);

    // =================<MENU>================
    Mix_AllocateChannels(100);
    play_music_level(level, background_music);

    while (menu->get_game_has_started() == false)
    {
        menu->render_menu();
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                exit(EXIT_FAILURE);
            }
            menu->process_input_menu(event);
        }
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }

    // ===============<LEVEL 1>================
    level = 1;
    play_music_level(level, background_music);
    intro_before_level(level);

    while (level == 1)
    {
        common_process(player, present, event);
        process_chicken_vs_player(chicken, player);
        if (all_level_1_chicken_dead(chicken) == true && all_level_1_2_chicken_dead(chicken2) == true)
        {
            level = 2;
        }
        else if (all_level_1_chicken_dead(chicken) == true)
        {
            process_chicken_vs_player(chicken2, player);
        }
        if (player->get_health() <= 0)
        {
            exit(EXIT_SUCCESS);
        }
        if (menu != NULL)
        {
            if (is_paused == false)
            {
                menu->render_time();
            }
            menu->render_health_bar(player);
        }
        update_game_state();
    }
    // ===============<LEVEL 2>================

    level++;
    // level = 2;
    intro_before_level(level);
    play_music_level(level, background_music);
    while (level == 2)
    {
        common_process(player, present, event);
        process_astroid_vs_player(asteroid, player);
        if (all_level_2_asteroid_dead(asteroid) == true)
        {
            level = 3;
        }
        if (player->get_health() <= 0)
        {
            exit(EXIT_SUCCESS);
        }
        if (is_paused == false)
        {
            menu->render_time();
        }
        menu->render_health_bar(player);
        update_game_state();
    }

    // ===============<LEVEL 3>================

    level++;
    // level = 3;
    level = 3;
    intro_before_level(level);
    play_music_level(level, background_music);
    boss[0].set_rect_cordinate(SCREEN_WIDTH / 2, 0);

    while (level == 3)
    {
        common_process(player, present, event);
        process_boss_vs_player(boss, player);
        if (all_boss_dead(boss) == true || player->get_health() <= 0)
        {
            std::cout << "player_is_dead";
            exit(EXIT_SUCCESS);
        }
        if (is_paused == false)
        {
            menu->render_time();
        }
        menu->render_health_bar(player);
        update_game_state();
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
/*

*/
