#include "tetris.h"
#include <string.h>
#include <time.h>


void vykresliBunku(SDL_Renderer* renderer, int x, int y) {
    SDL_Rect rect = {x + 1, y + 1, 38, 38};
    SDL_RenderFillRect(renderer, &rect);
}

void vykresliCelouBunku(SDL_Renderer* renderer, int x, int y) {
    SDL_Rect rect = {x,y,40,40};
    SDL_RenderFillRect(renderer, &rect);
}

void vykresliMalouBunku(SDL_Renderer* renderer, int x, int y) {
    SDL_Rect rect = {x,y,5,5};
    SDL_RenderFillRect(renderer, &rect);
}


// pocitani score + vymazani vyplneneho radku + vykresleni zakladni herni plochy + vykresleni nasledujiciho objektu
int vykresliZakladniPlochu(SDL_Renderer* renderer, int pole[][10], int delka, int randomObjekt, int nasledujiciObjekt, int pole2[][10], int delka2, int starePole[][10], int prvniCyklus){
    int seznamVyplnenych[delka], score=0;

    for(int i=0; i<delka; i++){     //najde vyplnene radky
        seznamVyplnenych[i] = 1;
        for(int j=0; j<10; j++){
            if(pole[i][j] != 1){
                seznamVyplnenych[i] = 0;
            }
        }
    }

    for(int i=0; i<delka; i++){     //vymaze vyplnene radky
        if(seznamVyplnenych[i] == 1){
            score++;
            for(int j=i; j>=0; j--){
                for(int k=0; k<10; k++){
                    if(j > 0){
                        pole[j][k] = pole[j-1][k];               
                    }else{
                        pole[j][k] = 0;
                    }
                }
            }
        }
    }

    for(int i=0; i<delka; i++){     //vykresleni herniho pole
        for(int j=0; j<10; j++){
            if((pole[i][j] != starePole[i][j]) || prvniCyklus == 1){
                if(pole[i][j] == 2){   
                    switch(randomObjekt){
                        case 0: 
                            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); //zelena
                            break;
                        case 1:
                            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); //modra
                            break;
                        case 2:
                            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //cervena
                            break;
                        case 3: 
                            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                            break;
                        case 4:
                            SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
                            break;
                        case 5:
                            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                            break;
                        case 6:
                            SDL_SetRenderDrawColor(renderer, 255, 128, 0, 255);
                            break;
                    }                                 //pohybujici se objekt
                    vykresliBunku(renderer, j*40, i*40);
                }else if(pole[i][j] == 1){        //umisteny objekt
                    SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255);
                    vykresliBunku(renderer, j*40, i*40);
                }else{                                                  //herni plocha
                    SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
                    vykresliBunku(renderer, j*40, i*40);
                }
            }
            
        }
    }


    for(int i=0; i<delka2; i++){    //vykresleni pole s nasledujicim objektem
        for(int j=2; j<7; j++){
            if(pole2[i][j] == 2){
                switch(nasledujiciObjekt){
                    case 0: 
                        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                        break;
                    case 1:
                        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                        break;
                    case 2:
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                        break;
                    case 3: 
                        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                        break;
                    case 4:
                        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
                        break;
                    case 5:
                        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                        break;
                    case 6:
                        SDL_SetRenderDrawColor(renderer, 255, 128, 0, 255);
                        break;
                }                                 //pohybujici se objekt
                vykresliBunku(renderer, j*40+320, i*40+80);
            }else{
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                vykresliBunku(renderer, j*40+320, i*40+80);
            }
        }
    }

    for(int i=16; i<19;i++){
        for(int j=10; j<15; j++){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            vykresliCelouBunku(renderer, j*40, i*40);
        }
    }

    return score;
}




void sdl_draw_text(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Rect location, const char* text)
{
    // Vykreslení textu se zadaným fontem a barvou do obrázku (surface)
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    // Převod surface na hardwarovou texturu
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Vykreslení obrázku
    SDL_RenderCopy(renderer, texture, NULL, &location);

    // Uvolnění textury a surface
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}



//objekty
void vykresliCtverec(int pole[][10], int nasledujici){
    srand(time(NULL));
    int i;
    if(nasledujici == 1){
        i=0;
    }else{
        i = rand()%9-4;
    }

    pole[0][i+4] = 2;
    pole[1][i+4] = 2;
    pole[0][i+5] = 2;
    pole[1][i+5] = 2;
}

void vykresliIcko(int pole[][10], int nasledujici){
    srand(time(NULL));
    int i;
    if(nasledujici == 1){
        i=0;
    }else{
        i = rand()%7-3;
    }

    pole[0][i+3] = 2;
    pole[0][i+4] = 2;
    pole[0][i+5] = 2;
    pole[0][i+6] = 2;
}

void vykresliLko(int pole[][10], int nasledujici){
    srand(time(NULL));
    int i;
    if(nasledujici == 1){
        i=0;
    }else{
        i = rand()%9-4;
    }

    pole[0][i+4] = 2;
    pole[1][i+4] = 2;
    pole[2][i+4] = 2;
    pole[2][i+5] = 2;
}

void vykresliTecko(int pole[][10], int nasledujici){
    srand(time(NULL));
    int i;
    if(nasledujici == 1){
        i=0;
    }else{
        i = rand()%8-3;
    }

    pole[0][i+3] = 2;
    pole[0][i+4] = 2;
    pole[0][i+5] = 2;
    pole[1][i+4] = 2;
}

void vykresliJecko(int pole[][10], int nasledujici){
    srand(time(NULL));
    int i;
    if(nasledujici == 1){
        i=0;
    }else{
        i = rand()%9-4;
    }

    pole[0][i+5] = 2;
    pole[1][i+5] = 2;
    pole[2][i+5] = 2;
    pole[2][i+4] = 2;
}

void vykresliSko(int pole[][10], int nasledujici){
    srand(time(NULL));
    int i;
    if(nasledujici == 1){
        i=0;
    }else{
        i = rand()%8-3;
    }

    pole[0][i+5] = 2;
    pole[0][i+4] = 2;
    pole[1][i+4] = 2;
    pole[1][i+3] = 2;
}

void vykresliZetko(int pole[][10], int nasledujici){
    srand(time(NULL));
    int i;
    if(nasledujici == 1){
        i=0;
    }else{
        i = rand()%8-3;
    }

    pole[0][i+3] = 2;
    pole[0][i+4] = 2;
    pole[1][i+4] = 2;
    pole[1][i+5] = 2;
}