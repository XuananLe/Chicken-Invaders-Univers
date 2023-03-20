#include "AmmoObject.h"
#include "CommonVariable.h"
const int ARROW_WIDTH = 21;
const int ARROW_HEIGHT = 59;

// IMPLEMENT CONSTRUCTOR AND DESTRUCTOR
AmmoObject::AmmoObject()
{
    type_ = AmmoType::ARROW;
    texture_ = IMG_LoadTexture(renderer, "res/image/arrow.png");
    can_move = true;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = ARROW_WIDTH;
    rect_.h = ARROW_HEIGHT;
    speed_ = 10;
    life_time_ = 0;
    startTicks_ = 0;
    damage_ = 1;
    alive_ = false;
    double direction = 0; // Set direction to point straight up
}
AmmoObject::~AmmoObject()
{
    if (texture_ != NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}

// IMPLEMENT RENDER METHOD
void AmmoObject::render(SDL_Renderer *renderer)
{
    if (can_move == true)
        SDL_RenderCopy(renderer, texture_, NULL, &rect_);
}

// IMPLEMENT UPDATE METHOD
void AmmoObject::update()
{
    if (alive_ == true && can_move == true)
    {
        rect_.y -= speed_ * cos(direction_ * M_PI / 180);
        rect_.x = rect_.x + speed_ * sin(direction_ * M_PI / 180);
    }
    if (rect_.x < 0 || rect_.x > SCREEN_WIDTH || rect_.y < 0 || rect_.y > SCREEN_HEIGHT || can_move == false)
    {
        alive_ = false;
    }
}

// IMPLEMENT FREE METHOD
void AmmoObject::free()
{
    if (texture_ != NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}

// IMPLEMENT LOAD_STATIC_AMMO_PICTURE METHOD
void AmmoObject::load_static_ammo_picture(SDL_Renderer *renderer, const char *file_path)
{
    SDL_Surface *surface = IMG_Load(file_path);
    if (surface == NULL)
    {
        std::cout << "Unable to load image " << file_path << " SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        texture_ = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND);
        if (texture_ == NULL)
        {
            std::cout << "Unable to create texture from " << file_path << " SDL Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            rect_.w = static_cast<int>(surface->w);
            rect_.h = static_cast<int>(surface->h);
        }
        SDL_FreeSurface(surface);
    }
}

// IMPLEMENT CONSTRUCTOR AND DESTRUCTOR OF ARROWAMMO
ArrowAmmo::ArrowAmmo()
{
    speed_ = 10;
    damage_ = 10;
    life_time_ = 1000;
    can_move = true;
    startTicks_ = SDL_GetTicks();
    texture_ = IMG_LoadTexture(renderer, "res/image/arrow.png");
    alive_ = true;
}
ArrowAmmo::~ArrowAmmo()
{
    if (texture_ != NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}
