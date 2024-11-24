#include "tetris.h"
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[])
{
    // Inicializace SDL
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    TTF_Font* font = TTF_OpenFont("/mnt/c/Users/jakub/Documents/skola/upr/tetris/Arial.ttf", 50);

    // Vytvoření okna
    SDL_Window* window = SDL_CreateWindow(
        "SDL experiments",  // Titulek okna
        100,                // Souřadnice x
        100,                // Souřadnice y
        600,                // Šířka
        800,                // Výška
        SDL_WINDOW_SHOWN    // Okno se má po vytvoření rovnou zobrazit
    );

    // Vytvoření kreslítka
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC
    );

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");


    SDL_Rect location;
        location.x = 420;    // Horizontální pozice
        location.y = 650;    // Vertikální pozice
        location.w = 100;   // Šířka
        location.h = 25;    // Výška

    SDL_Rect location2;
        location2.x = 120;    // Horizontální pozice
        location2.y = 50;    // Vertikální pozice
        location2.w = 200;   // Šířka
        location2.h = 50;    // Výška
    
    SDL_Rect location3;
        location3.x = 420;    // Horizontální pozice
        location3.y = 690;    // Vertikální pozice
        location3.w = 150;   // Šířka
        location3.h = 25;    // Výška


    SDL_Color white = {255, 255, 255, 255};
    SDL_Event event;

    int running = 1, running2 = 1, running3 = 1;
    int novyObjekt = 0, cyklusObjektu=0, randomObjekt=0, nasledujiciObjekt=0, score=0, r=0, MaxScore = 0, obtiznost = 1, nasledujici=0;
    int zaznamObsazenychPoli[20][10] = {0}, polePredZmenou[20][10] = {0}, poleProNasledujici[3][10] = {0};
    double cyklus = 0, rychlost=0, prvniCyklus=1, zmenaRychlosti=0, kurzor=0, kurzor2=0; 

    char text[50], konec[50],MScore[50];
    bool posunDolu1=true, posunDoprava=true, posunDoleva=true, prava=false, leva=false, otoceni= false, zmenaR=false, gameOver = false, zapsano=false;

    Uint64 last = SDL_GetPerformanceCounter();

    FILE *f = fopen("maxScore.txt", "r");
    FILE *f2 = fopen("maxScore2.txt", "r");
    FILE *f3 = fopen("maxScore3.txt", "r");

    srand(time(NULL));


    while (running == 1){
        while(running2 == 1){   //menu
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

            while (SDL_PollEvent(&event)){
                if (event.type == SDL_QUIT){
                    running2 = 0;
                    running = 0;
                }else if (event.type == SDL_KEYDOWN){   
                    switch (event.key.keysym.sym){
                        case SDLK_UP:
                            if(kurzor != 0){
                                kurzor--;
                            }
                            break;
                        case SDLK_DOWN:
                            if(kurzor != 2){
                                kurzor++;
                            }
                            break;
                        case SDLK_RETURN:
                            if(kurzor == 0){
                                running2 = 0;
                            }else if(kurzor == 1){
                                running3 = 1;
                                while(running3 == 1){   //menu obtiznosti
                                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

                                    while (SDL_PollEvent(&event)){
                                        if (event.type == SDL_QUIT){
                                            running3 = 0;
                                            running2 = 0;
                                            running = 0;
                                        }else if (event.type == SDL_KEYDOWN){   
                                            switch (event.key.keysym.sym){
                                                case SDLK_UP:
                                                    if(kurzor2 != 0){
                                                        kurzor2--;
                                                    }
                                                    break;
                                                case SDLK_DOWN:
                                                    if(kurzor2 != 2){
                                                        kurzor2++;
                                                    }
                                                    break;
                                                case SDLK_RETURN:
                                                    if(kurzor2 == 0){
                                                        obtiznost = 0;
                                                        running3 = 0;
                                                    }else if(kurzor2 == 1){
                                                        obtiznost = 1;
                                                        running3 = 0;
                                                    }else if(kurzor2 == 2){
                                                        obtiznost = 2;
                                                        running3 = 0;
                                                    }
                                                    break;
                                                }
                                        }
                                    }
                                    SDL_RenderClear(renderer);
            
                                    vykresliMenuObtiznosti(renderer, font, kurzor2);

                                    SDL_RenderPresent(renderer);
                                }
                            }else if(kurzor == 2){
                                running = 0;
                                running2 = 0;
                            }
                            break;
                    }
                }
            }
            SDL_RenderClear(renderer);
            
            vykresliMenu(renderer, font, kurzor);

            SDL_RenderPresent(renderer);
        }

        //konec menu zacatek hry
        Uint64 now = SDL_GetPerformanceCounter();
        double deltaTime = (double)((now - last) / (double)SDL_GetPerformanceFrequency());
        last = now;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        //ovladani klaves ve hre
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT){
                running = 0;
            }else if (event.type == SDL_KEYDOWN){   
                switch (event.key.keysym.sym){
                    case SDLK_LEFT:
                        leva = true; break;
                    case SDLK_RIGHT:
                        prava = true; break;
                    case SDLK_DOWN:
                        rychlost = 0.05; break;
                    case SDLK_r:
                        otoceni = true; break;
                }
            }
        }

        jeMoznoSObjektem(zaznamObsazenychPoli, 19, &posunDolu1, &posunDoprava, &posunDoleva);      //overeni pro posuny       

        if(otoceni == true){    //rotace
            r++;
            otocObjekt(zaznamObsazenychPoli, 20, r, randomObjekt, &zmenaR);
            if(zmenaR != true){
                r--;
            }
            otoceni=false;
        }


        if(leva == true){   //pohyb doleva
            if(posunDoleva == true){
                posun(zaznamObsazenychPoli, 19, 3, &posunDolu1);
            }
            leva = false;
        }
        if(prava == true){ //pohyb doprava
            if(posunDoprava == true){
                posun(zaznamObsazenychPoli, 19, 4, &posunDolu1);
            }
            prava = false;
        }

        if(prvniCyklus == 1){
            SDL_RenderClear(renderer); // Vykresli pozadí
            switch(obtiznost){
                case 0: fscanf(f,"%d", &MaxScore);break;
                case 1: fscanf(f2,"%d", &MaxScore);break;
                case 2: fscanf(f3,"%d", &MaxScore);break;
            }
        }


        sprintf(text, "Score: %d", score);
        sprintf(MScore, "Max score: %d", MaxScore);

        if(novyObjekt == 0 && gameOver == false){
            if(cyklus == 0){
                randomObjekt = rand() % 7;
            }else{
                randomObjekt = nasledujiciObjekt;
            }

            for(int i=0; i<3; i++){ //vyresetovani pole pro nasledujici objekt
                for(int j=0; j<10; j++){
                    poleProNasledujici[i][j] = 0;
                }
            }
            nasledujiciObjekt = rand() % 7;

            r=0;
            nasledujici = 1;
            switch(nasledujiciObjekt){  //naplneni pole pro nasledujici objekt objektem
                case 0: vykresliCtverec(poleProNasledujici, nasledujici); break;
                case 1: vykresliIcko(poleProNasledujici, nasledujici); break;
                case 2: vykresliLko(poleProNasledujici, nasledujici); break;
                case 3: vykresliTecko(poleProNasledujici, nasledujici); break;
                case 4: vykresliJecko(poleProNasledujici, nasledujici); break;
                case 5: vykresliSko(poleProNasledujici, nasledujici); break;
                case 6: vykresliZetko(poleProNasledujici, nasledujici); break;
            }
            nasledujici = 0;
            
            switch(randomObjekt){   //naplneni herniho pole objektem
                case 0: vykresliCtverec(zaznamObsazenychPoli, nasledujici); break;
                case 1: vykresliIcko(zaznamObsazenychPoli, nasledujici); break;
                case 2: vykresliLko(zaznamObsazenychPoli, nasledujici); break;
                case 3: vykresliTecko(zaznamObsazenychPoli, nasledujici); break;
                case 4: vykresliJecko(zaznamObsazenychPoli, nasledujici); break;
                case 5: vykresliSko(zaznamObsazenychPoli, nasledujici); break;
                case 6: vykresliZetko(zaznamObsazenychPoli, nasledujici); break;
            }
            
            zmenaRychlosti++;
            novyObjekt++;
            cyklusObjektu = 0;
        }


        jeMoznoSObjektem(zaznamObsazenychPoli, 19, &posunDolu1, &posunDoprava, &posunDoleva);      //overeni pro posuny

        score += vykresliZakladniPlochu(renderer, zaznamObsazenychPoli, 20, randomObjekt, nasledujiciObjekt, poleProNasledujici, 3, polePredZmenou, prvniCyklus);    // vykreslení hrací plochy + nasledujiciho bloku a vrácení score
        prvniCyklus++;
        sdl_draw_text(renderer, font, white, location, text);   //vypsani score
        sdl_draw_text(renderer, font, white, location3, MScore);   //vypsani max score
        memcpy(polePredZmenou, zaznamObsazenychPoli, sizeof(zaznamObsazenychPoli)); //zkopirovani aktualniho pole... setri vykon, vykresluje jen bloky ktere se zmenily

        //ukonceni hry
        if((posunDolu1 == false && cyklusObjektu == 0) || gameOver == true){ 
            sprintf(konec, "Game over");
            sdl_draw_text(renderer, font, white, location2, konec);
            gameOver = true;
            if(zapsano == false && MaxScore < score){
                switch(obtiznost){
                    case 0: 
                        f = fopen("maxScore.txt", "w");
                        fprintf(f,"%d", score);break;
                    case 1: 
                        f2 = fopen("maxScore2.txt", "w");
                        fprintf(f2,"%d", score);break;
                    case 2: 
                        f3 = fopen("maxScore3.txt", "w");
                        fprintf(f3,"%d", score);break;
                }
                
                
                zapsano = true;
            }
        }

        //zvyseni rychlosti, posun dolu, nastaveni pro vytvoreni noveho objektu
        if(cyklus >= rychlost){
            switch(obtiznost){
                case 0:
                    rychlost = 1 - (zmenaRychlosti*0.004);
                    if(rychlost < 0.1){
                        rychlost = 0.1;
                    }
                    break;
                case 1: 
                    rychlost = 0.8 - (zmenaRychlosti*0.007);
                    if(rychlost < 0.1){
                        rychlost = 0.1;
                    }
                    break;
                case 2:
                    rychlost = 0.5 - (zmenaRychlosti*0.008);
                    if(rychlost < 0.1){
                        rychlost = 0.1;
                    }
                    break;
            }
            
            posun(zaznamObsazenychPoli, 19, 1, &posunDolu1);
            if(posunDolu1 == false){
                novyObjekt=0;
            }
            cyklus=0;
        }

        SDL_RenderPresent(renderer);

        cyklus+=deltaTime;
        cyklusObjektu++;
    }

    // Uvolnění prostředků
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    fclose(f);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

//pocet radku ... 338+751+28=1123
// zjednodusit posledni funkci?