#include <SDL2/SDL.h>

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(
        "2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    {
        bool running = true;
        while (running){
            SDL_Event event;
            while (SDL_PollEvent(&event)){
                if (event.type == SDL_QUIT){
                    running = false;
                }
                else if (event.type == SDL_KEYDOWN){
                    if (event.key.keysym.sym == SDLK_ESCAPE){
                        running = false;
                    }
                }
            }
            SDL_SetRenderDrawColor(renderer, 0xfa, 0xf8, 0xef, 0xff);
            SDL_RenderClear(renderer);
            
            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}