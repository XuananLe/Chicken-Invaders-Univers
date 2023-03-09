#include "CommonVariable.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
class ThemePlayer
{
protected:
const char* menu_theme;
const char *level_1_theme;
const char *level_2_theme;
const char *boss_level_theme;
public:
// Constructor and Destructor
ThemePlayer();
~ThemePlayer();
// Stop the theme
void stop_theme();
// PLAYING THE THEME
void play_theme(const char* theme);
// SET VOLUME
void set_volume(const int &volume);
};