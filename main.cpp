#include<iostream>
#include<SDL.h>
#include<SDL_image.h>

using namespace std;

int main(int argc, char *args[]){

    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Texture *tex;
    SDL_CreateWindowAndRenderer(1280, 640, 0, &window, &render);
	SDL_SetWindowTitle(window, "EGG CHICKEN GAME");
	SDL_Surface* surf = IMG_Load("bg600.png");
	tex = SDL_CreateTextureFromSurface(render, surf);
	SDL_RenderCopy(render, tex, NULL, NULL);
	while(true){
        SDL_RenderPresent(render);
    }
	SDL_Delay(5000);
	SDL_Quit();
	return 0;
}
