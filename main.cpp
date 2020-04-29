#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <time.h>

using namespace std;
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char *args[]){

    SDL_Window *window = NULL;
    SDL_Renderer *render = NULL;

    SDL_CreateWindowAndRenderer(1200, 600, 0, &window, &render);
	SDL_SetWindowTitle(window, "Egg Chicken");

    SDL_Texture *tex = NULL;
    SDL_Texture *Ga = NULL;
    SDL_Rect trung,ga[5],gio;

    ga[0].x = 50;
    ga[0].y = 50;
    ga[0].w = 50;
    ga[0].h = 100;

    trung.x = 65;
    trung.y = 150;
    trung.w = 23;
    trung.h = 28;

    gio.x=0;
    gio.y=500;
    gio.w=56;
    gio.h=46;

    bool running = true;
    for(int i=1;i<5;i++){
        ga[i].x=ga[i-1].x + 250;
        ga[i].y = 50;
        ga[i].w = 50;
        ga[i].h = 100;
    }
    int n ;
    SDL_Event event;



while (running){
    if(trung.y==150){
        srand(time(0));
        n = rand()% 5;
        trung.x = ga[n].x+15;
    }

    SDL_Surface* surf = IMG_Load("bg600.png");
	tex = SDL_CreateTextureFromSurface(render, surf);
	SDL_RenderCopy(render, tex, NULL, NULL);

    SDL_Texture *Trung = NULL;
    SDL_Surface* anhtrung = IMG_Load("egg1.png");
    Trung = SDL_CreateTextureFromSurface(render, anhtrung);
    SDL_RenderCopy(render, Trung, NULL, &trung);

    SDL_Surface* anhga = IMG_Load("chicken.png");
    Ga = SDL_CreateTextureFromSurface(render, anhga);
    SDL_RenderCopy(render, Ga, NULL, &ga[0]);
    SDL_RenderCopy(render, Ga, NULL, &ga[1]);
    SDL_RenderCopy(render, Ga, NULL, &ga[2]);
    SDL_RenderCopy(render, Ga, NULL, &ga[3]);
    SDL_RenderCopy(render, Ga, NULL, &ga[4]);

    SDL_Surface* anhgio = IMG_Load("bowl.png");
    SDL_Texture* Gio = NULL;
	Gio = SDL_CreateTextureFromSurface(render, anhgio);
	SDL_RenderCopy(render, Gio, NULL, &gio);

    trung.y+=10;

    if(trung.y>=500) {
        trung.y = 150;
        //break;

    }
    if(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT: quitSDL(window, render);  break;
            //khi ấn phím
            default :{ if (event.type == SDL_KEYDOWN ){
                switch(event.key.keysym.sym)
                    {
                        case SDLK_LEFT: gio.x-=50;if(gio.x<0) gio.x=0; break;
                        case SDLK_RIGHT: gio.x+=50;if(gio.x>1200)gio.x=1150; break;

                        default: break;
                    }
            }
            }
        }
    }
        SDL_FreeSurface(anhga);
        SDL_FreeSurface(surf);
        SDL_FreeSurface(anhtrung);
        SDL_DestroyTexture(Ga);
        SDL_DestroyTexture(tex);
        SDL_RenderPresent(render);

    }

    SDL_Delay(2000);
	SDL_Quit();
	return 0;
}
