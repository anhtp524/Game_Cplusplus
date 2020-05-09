
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstdlib>
#include <time.h>
#include <string>


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
play_again:
    if (TTF_Init() < 0)
    {
		SDL_Log("%s", TTF_GetError());
    	return 0;
    }
    TTF_Font* font1 = NULL;
    font1 = TTF_OpenFont("VeraMoBd.ttf", 15);
    TTF_Font* font2 = NULL;
    font2 = TTF_OpenFont("VeraMoBd.ttf", 30);


    SDL_Texture *tex = NULL;
    SDL_Texture *Ga = NULL;

    SDL_Color color = {0,0,0,255};
    SDL_Rect trung,ga[5],gio,trungvo,tim[5],score_rect,score,score_bgr, score_number, score_ag;

    ga[0].x = 50;
    ga[0].y = 50;
    ga[0].w = 50;
    ga[0].h = 100;

    trung.x = 65;
    trung.y = 150;
    trung.w = 23;
    trung.h = 28;

    gio.x=600;
    gio.y=500;
    gio.w=56;
    gio.h=46;

    trungvo.w = 61;
    trungvo.h = 17;

    tim[0].x = 0;
    tim[0].y = 0;
    tim[0].w = 45;
    tim[0].h = 46;

    score_rect.x = 1200-30;
    score_rect.y = 0;
    score_rect.w = 30;
    score_rect.h = 40;

    score.x = 1200-30-80;
    score.y = 0;
    score.w = 80;
    score.h = 40;

    score_bgr.x = 480;
    score_bgr.y = 400;
    score_bgr.w = 150;
    score_bgr.h = 30;

    score_number.x = score_bgr.x + score_bgr.w;
    score_number.y = 400;
    score_number.w = 30;
    score_number.h = 30;

    score_ag.x = 1200 - 300;
    score_ag.y = 600 - 30;
    score_ag.w = 300;
    score_ag.h = 30;

    for(int i=1;i<5;i++){
        ga[i].x=ga[i-1].x + 250;
        ga[i].y = 50;
        ga[i].w = 50;
        ga[i].h = 100;

        tim[i].x = tim[i-1].x+45;
        tim[i].y = 0;
        tim[i].w = 45;
        tim[i].h = 46;
    }

    int n ;
    SDL_Event event;
    int TrungVo = 5;
    int diem = 0;
    int loai_trung = 2;
    int chon_trung = 1;
    int step = 7;

while (TrungVo != 0 ){
    if(trung.y==150){
        srand(time(0));
        n = rand()% 5;
        trung.x = ga[n].x+15;
    }

    SDL_Surface* surf = IMG_Load("bg600.png");
	tex = SDL_CreateTextureFromSurface(render, surf);
	SDL_RenderCopy(render, tex, NULL, NULL);

    SDL_Texture *Trung = NULL;
    SDL_Surface* anhtrung;
    if(chon_trung == 1 ){
        anhtrung = IMG_Load("egg1.png");
        Trung = SDL_CreateTextureFromSurface(render, anhtrung);
        SDL_RenderCopy(render, Trung, NULL, &trung);
    }
    else{
        anhtrung = IMG_Load("egg2.png");
        Trung = SDL_CreateTextureFromSurface(render, anhtrung);
        SDL_RenderCopy(render, Trung, NULL, &trung);
    }


    SDL_Surface* anhga = IMG_Load("chicken.png");
    Ga = SDL_CreateTextureFromSurface(render, anhga);
    SDL_RenderCopy(render, Ga, NULL, &ga[0]);
    SDL_RenderCopy(render, Ga, NULL, &ga[1]);
    SDL_RenderCopy(render, Ga, NULL, &ga[2]);
    SDL_RenderCopy(render, Ga, NULL, &ga[3]);
    SDL_RenderCopy(render, Ga, NULL, &ga[4]);

    SDL_Texture *Tim = NULL;
    SDL_Surface* anhtim = IMG_Load("heart.png");
    Tim = SDL_CreateTextureFromSurface(render, anhtim);
    for(int i = 0; i<TrungVo;i++ ){
       SDL_RenderCopy(render, Tim, NULL, &tim[i]);
    }

    SDL_Surface* anhgio = IMG_Load("bowl.png");
    SDL_Texture* Gio = NULL;
	Gio = SDL_CreateTextureFromSurface(render, anhgio);
	SDL_RenderCopy(render, Gio, NULL, &gio);

    SDL_FreeSurface(anhga);
    SDL_FreeSurface(surf);
    SDL_FreeSurface(anhtrung);
    SDL_FreeSurface(anhgio);
    SDL_DestroyTexture(Ga);
    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(Gio);
    SDL_DestroyTexture(Trung);


    trung.y+=step;
    ;


    if(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT: quitSDL(window, render);  break;
            //khi di chuyển chuột
            default :{ if (event.type == SDL_MOUSEMOTION ){

                    gio.x = event.motion.x;
                    if(gio.x<0) gio.x = 0;
                    if(gio.x>1100) gio.x = 1150;
                    break;

            }
            }
        }
    }
    if(trung.y>=500) {
        if(trung.x>=gio.x-30&&trung.x<=gio.x+30) {
                if(chon_trung ==1) diem++;
                else diem+=2;
                step++;
        }
        else{
            SDL_Texture *Trungvo = NULL;
            SDL_Surface* anhtrungvo = IMG_Load("egg-popped.png");
            Trungvo = SDL_CreateTextureFromSurface(render, anhtrungvo);
            trungvo.x = trung.x - 10;
            trungvo.y = trung.y+20;
            SDL_RenderCopy(render, Trungvo, NULL, &trungvo);
            SDL_FreeSurface(anhtrungvo);
            SDL_DestroyTexture(Trungvo);

            TrungVo --;
        }
            trung.y = 150;
            srand(time(0));
            chon_trung = rand()%loai_trung + 1;

    }

    string Score = to_string(diem);
    SDL_Surface* surfScore = TTF_RenderText_Solid(font1, Score.c_str()  , color);
    tex = SDL_CreateTextureFromSurface(render,surfScore);
    SDL_RenderCopy(render,tex,NULL,&score_rect);
    SDL_FreeSurface(surfScore);
    SDL_DestroyTexture(tex);

    string sc = "Score:";
    SDL_Surface* Diem = TTF_RenderText_Solid(font2, sc.c_str(), color);
    SDL_Texture* d = SDL_CreateTextureFromSurface(render,Diem);
    SDL_RenderCopy(render,d,NULL,&score);
    SDL_FreeSurface(Diem);
    SDL_DestroyTexture(d);

    SDL_RenderPresent(render);
    SDL_RenderClear(render);
    }
    SDL_Delay(500);
    SDL_Surface* surf = IMG_Load("gameover.jpg");
    tex = SDL_CreateTextureFromSurface(render, surf);
	SDL_RenderCopy(render, tex, NULL, NULL);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(tex);

    SDL_Color white = {255,250,250,255};
    SDL_Surface* Score1 = TTF_RenderText_Solid(font2, "Your Score:"  , white);
    SDL_Texture* text = SDL_CreateTextureFromSurface(render , Score1);
    SDL_RenderCopy(render,text,NULL,&score_bgr);
    SDL_FreeSurface(Score1);
    SDL_DestroyTexture(text);

    string s = to_string (diem);
    SDL_Surface* Score_number = TTF_RenderText_Solid(font2, s.c_str()   , white);
    SDL_Texture* text_number = SDL_CreateTextureFromSurface(render , Score_number);
    SDL_RenderCopy(render,text_number,NULL,&score_number);
    SDL_FreeSurface(Score_number);
    SDL_DestroyTexture(text_number);

    SDL_Surface* Score_playag = TTF_RenderText_Solid(font2, "Press SPACE to play again"  , white);
    SDL_Texture* text_ag = SDL_CreateTextureFromSurface(render , Score_playag);
    SDL_RenderCopy(render,text_ag,NULL,&score_ag);
    SDL_FreeSurface(Score_playag);
    SDL_DestroyTexture(text_ag);


    SDL_RenderPresent(render);
    SDL_RenderClear(render);

    SDL_Event e;
    bool x = false;
    while (!x)
    {
    while (SDL_PollEvent(&e) != 0)
    {
    if (e.type == SDL_QUIT)
    {

        x = true;

        quitSDL(window, render);
        break;
    }
    else if (e.type == SDL_KEYDOWN)
    {
    if (e.key.keysym.sym == SDLK_SPACE)
    {


     goto play_again;
    }

   }
  }
 }


    SDL_Delay(5000);
	quitSDL(window , render);
	return 0;
}
