#include "ThemePlayer.h"
ThemePlayer::ThemePlayer()
{
    // Initialize SDL and SDL_mixer
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("Mix_OpenAudio failed: %s\n", Mix_GetError());
        exit(1);
    }
    // Load the theme file
    menu_theme = "res/sound/MENU_THEME.mp3";
    level_1_theme = "res/sound/level_1_theme.mp3";
    level_2_theme = "res/sound/MENU_THEME.mp3";
    boss_level_theme = "res/sound/MENU_THEME.mp3";
}
ThemePlayer::~ThemePlayer()
{
    // Close SDL and SDL_mixer
    Mix_CloseAudio();
    SDL_Quit();
}
// IMPLEMENTATION OF stop_theme()
void ThemePlayer::stop_theme()
{
    Mix_HaltMusic();
}
// IMPLEMENTATION OF play_theme()
void ThemePlayer::play_theme(const char *theme)
{
    Mix_Music *music;
    music = Mix_LoadMUS(theme);
    if (music == NULL)
    {
        printf("Mix_LoadMUS failed: %s\n", Mix_GetError());
        exit(1);
    }
}

// IMPLEMENTATION OF set_volume()
void ThemePlayer::set_volume(const int &volume)
{
    Mix_VolumeMusic(volume);
}