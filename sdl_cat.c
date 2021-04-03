#include "sdl_cat.h"
#include "globals.h"

SDL_Window *initMainWindow()
{
    SDL_Window *window;
    window = SDL_CreateWindow("snake game",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);

    return window;
}

void quit(SDL_Window *main_window)
{
    SDL_DestroyWindow(main_window);
    SDL_Quit();
}
