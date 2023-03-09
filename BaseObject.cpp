#include "BaseObject.h"
// Implement Constructor and Destructor
BaseObject::BaseObject()
{
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}
BaseObject::~BaseObject() {}

// Implement Static IMG
void BaseObject::load_static_img(SDL_Renderer *renderer, const char *file)
{
    SDL_Surface *load_surface = IMG_Load(file);
    if (load_surface == NULL)
    {
        std::cout << "Cannot Load IMG"
                  << "\n";
    }
    else
    {
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 0, 0xFF, 0xFF));
        p_object_ = SDL_CreateTextureFromSurface(renderer, load_surface);
        if (p_object_ == NULL)
        {
            std::cout << "Cannot Create Texture"
                      << "\n";
        }
        else
        {
            rect_.w = load_surface->w;
            rect_.h = load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }
}
// Implement Set and Get method with the Rectangle
void BaseObject::set_rect_cordinate(const int &x, const int &y)
{
    rect_.x = x;
    rect_.y = y;
}
void BaseObject::set_rect_cordinate_and_width_height(const int &x, const int &y, const int &width, const int &height)
{
    rect_.x = x;
    rect_.y = y;
    rect_.w = width;
    rect_.h = height;
}
void BaseObject::set_width_height(const int &width, const int &height)
{
    rect_.w = width;
    rect_.h = height;
}
SDL_Rect BaseObject::get_rect() const
{
    return rect_;
}
void BaseObject::free()
{
    if (p_object_ != NULL)
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}
// Render IMG
void BaseObject::render_static_image(SDL_Renderer *renderer)
{
    SDL_Rect RenderQuad = rect_;
    SDL_RenderCopy(renderer, p_object_, nullptr, &rect_);
}
// Render IMG with scale ratio
void BaseObject::render_static_image_with_scale(SDL_Renderer *renderer, const double &scale)
{
    SDL_Rect RenderQuad;
    RenderQuad.x = rect_.x;
    RenderQuad.y = rect_.y;
    RenderQuad.w = static_cast<int>(rect_.w * scale);
    RenderQuad.h = static_cast<int>(rect_.h * scale);
    SDL_RenderCopy(renderer, p_object_, nullptr, &RenderQuad);
}