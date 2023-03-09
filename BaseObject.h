#ifndef BASEOBJECT_H
#define BASEOBJECT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <iostream>
class BaseObject
{
protected:
SDL_Texture *p_object_;
SDL_Rect rect_;
public:
// CONSTRUCTOR AND DESTRUCTOR
BaseObject();
~BaseObject();
// get texture
SDL_Texture* get_texture() const{return p_object_;}



// Set and Get method with the Rectangle // 
void set_rect_cordinate(const int &x, const int &y);
void set_rect_cordinate_and_width_height(const int &x, const int &y, const int& width, const int &height);
void set_width_height(const int &width, const int &height);
int get_width() const;
SDL_Rect get_rect() const;
 
// Load Static IMG
void load_static_img(SDL_Renderer *renderer, const char *file);
// Render Static Image
void render_static_image(SDL_Renderer *renderer);
void render_static_image_with_scale(SDL_Renderer *renderer,const double &scale);
// Free Function
void free();
};
#endif
