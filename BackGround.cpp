#include "BackGround.h"

// implement constructor and destructor
BackGround::~BackGround()
{
    if (image_ != NULL)
    {
        SDL_DestroyTexture(image_);
        image_ = NULL;
    }
}
BackGround::BackGround()
{
    y_ = 0;
    speed_ = 1.0;
    image_ = NULL;
}
void BackGround::loading_background(SDL_Renderer *renderer, const char *file_path)
{
    image_ = IMG_LoadTexture(renderer, file_path);
    if (image_ == NULL)
    {
        std::cerr << "Cannot load image"
                  << "\n";
        exit(EXIT_FAILURE);
    }
}

// implement render_background_scroll and update_background_scroll
void BackGround::render_background_scroll(SDL_Renderer *renderer_)
{
    SDL_Rect renderquad = {0, y_, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer_, image_, NULL, &renderquad);
    renderquad = {0, y_ - SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer_, image_, NULL, &renderquad);
}
void BackGround::update_background_scroll()
{
    y_ += speed_;
    if (y_ >= SCREEN_HEIGHT)
    {
        y_ = 0;
    }
}