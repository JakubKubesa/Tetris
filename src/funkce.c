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


//overeni pro pohyb dolu a do stran pro objekt
void jeMoznoSObjektem(int pole[][10], int delka, bool* posunDolu1, bool* posunDoprava, bool* posunDoleva){
    *posunDolu1 = true;
    *posunDoprava = true;
    *posunDoleva = true;

    for(int j=delka; j>=0; j--){
        for(int i=0; i<10; i++){
            if(pole[j][i] == 2){
                if(j < 19){ 
                    if(pole[j+1][i] != 1 && *posunDolu1 == true){                           //je mozny pomaly posun?
                        *posunDolu1 = true;
                    }else{
                        *posunDolu1 = false;
                    }
                }else{
                    *posunDolu1 = false;
                }

                if(i > 8){
                    *posunDoprava = false;
                }else{
                    if(pole[j][i+1] != 1 && *posunDoprava == true){
                        *posunDoprava = true;
                    }else{
                        *posunDoprava = false;
                    }
                }

                if(i < 1){
                    *posunDoleva = false;
                }else{
                    if(pole[j][i-1] != 1 && *posunDoleva == true){
                        *posunDoleva = true;
                    }else{
                        *posunDoleva = false;   
                    }
                }
            }
        }
    }
}


//posun dolu o jedno, dolu o dve a do stran
void posun(int pole[][10], int delka, int posun, bool* muze1){
    for(int j=delka; j>=0; j--){
        for(int i=0; i<10; i++){
            if(pole[j][i] == 2 && posun == 1){
                if(*muze1 == true){             
                    pole[j][i] = 0;
                    pole[j+1][i] = 2;
                }else{
                    pole[j][i] = 1;
                }
            }
            if(pole[j][i] == 2 && posun == 3){
                pole[j][i] = 0;
                pole[j][i-1] = 2;
            }
        }
    }

    for(int j=delka; j>=0; j--){
        for(int i=9; i>=0; i--){
            if(pole[j][i] == 2 && posun == 4){
                pole[j][i] = 0;
                pole[j][i+1] = 2;
            }
        }
    }
}



//overeni rotace objektu a jeji rotace
void otocObjekt(int pole[][10], int delka, int r, int objekt, bool *zmenaR){ 
    int otoceno=0;
    *zmenaR=false;

    for(int i=0; i<delka;i++){
        if(otoceno == 1){
            break;
        }
        for(int j=0; j<10; j++){
            if(pole[i][j] == 2){
                switch(objekt){
                    case 0: break;
                    case 1: 
                        if(r % 2 == 1 && j<8){
                            if(i > 2 && pole[i-3][j+1] != 1 && pole[i-2][j+1] != 1 && pole[i-1][j+1] != 1){
                                pole[i-3][j+1] = 2; //nove indexy
                                pole[i-2][j+1] = 2;
                                pole[i-1][j+1] = 2;
                                pole[i][j] = 0;     //smazani starych
                                pole[i][j+2] = 0;
                                pole[i][j+3] = 0; 
                                *zmenaR=true;
                            }else if(i <= 2 && pole[0][j+1] != 1 && pole[1][j+1] != 1 && pole[2][j+2] != 1){
                                pole[0][j+1] = 2; //nove indexy
                                pole[1][j+1] = 2;
                                pole[2][j+1] = 2;
                                pole[3][j+1] = 2;
                                pole[i][j] = 0;     //smazani starych
                                pole[i][j+2] = 0;
                                pole[i][j+3] = 0; 
                                *zmenaR=true;
                            }
                        }else if(r % 2 == 0){
                            if(j > 0 && j < 8 && pole[i+3][j-1] != 1 && pole[i+3][j+1] !=1 && pole[i+3][j+2] != 1){
                                pole[i+3][j-1] = 2; //nove indexy
                                pole[i+3][j+1] = 2;
                                pole[i+3][j+2] = 2;
                                pole[i][j] = 0;     //smazani starych
                                pole[i+1][j] = 0;
                                pole[i+2][j] = 0;
                                *zmenaR=true;
                            }else if(j == 0 && pole[i+3][j] != 1 && pole[i+3][j+1] !=1 && pole[i+3][j+2] != 1 && pole[i+3][j+3] != 1){                                pole[i+3][j+1] = 2;
                                pole[i+3][j+2] = 2;
                                pole[i+3][j+3] = 2;
                                pole[i][j] = 0;     //smazani starych
                                pole[i+1][j] = 0;
                                pole[i+2][j] = 0;
                                *zmenaR=true;
                            }else if(j == 8 && pole[i+3][j-1] != 1 && pole[i+3][j+1] !=1 && pole[i+3][j-2] != 1 && pole[i+3][j] != 1){
                                pole[i+3][j-1] = 2; //nove indexy
                                pole[i+3][j+1] = 2;
                                pole[i+3][j-2] = 2;
                                pole[i+3][j] = 2;
                                pole[i][j] = 0;     //smazani starych
                                pole[i+1][j] = 0;
                                pole[i+2][j] = 0;
                                *zmenaR=true;
                            }else if(j == 9 && pole[i+3][j-1] != 1 && pole[i+3][j-3] !=1 && pole[i+3][j-2] != 1 && pole[i+3][j] != 1){
                                pole[i+3][j-1] = 2; //nove indexy
                                pole[i+3][j-3] = 2;
                                pole[i+3][j-2] = 2;
                                pole[i+3][j] = 2;
                                pole[i][j] = 0;     //smazani starych
                                pole[i+1][j] = 0;
                                pole[i+2][j] = 0;
                                *zmenaR=true;
                            }
                        }
                        otoceno=1;
                        break;
                    case 2: 
                        if(r % 4 == 0 && i > 0 && j > 1 && pole[i][j-1] !=1 && pole[i+2][j-1] !=1 && pole[i+2][j] != 1){
                            pole[i][j] = 0;
                            pole[i+1][j] = 0;
                            pole[i+1][j-2] = 0;
                            pole[i][j-1] = 2;
                            pole[i+2][j-1] = 2;
                            pole[i+2][j] = 2;
                            *zmenaR=true; 
                        }else if(r % 4 == 1 && i > 0 && j<9){
                            if(j>0 &&pole[i+1][j+1] != 1 && pole[i+1][j-1] != 1 && pole[i+2][j-1] != 1){
                                pole[i][j] = 0;
                                pole[i+2][j] = 0;
                                pole[i+2][j+1] = 0;
                                pole[i+1][j+1] = 2;
                                pole[i+1][j-1] = 2;
                                pole[i+2][j-1] = 2;
                                *zmenaR=true;
                            }else if(j==0 && pole[i+1][j+1] !=1 && pole[i+1][j+2] != 1){
                                pole[i][j] = 0;
                                pole[i+2][j+1] = 0;
                                pole[i+1][j+1] = 2;
                                pole[i+1][j+2] = 2;
                                *zmenaR=true;
                            }
                        }else if(r % 4 == 2 && i > 0 && j<9 && pole[i-1][j] != 1 && pole[i-1][j+1] != 1 && pole[i+1][j+1] != 1){
                            pole[i][j] = 0;
                            pole[i+1][j] = 0;
                            pole[i][j+2] = 0;
                            pole[i-1][j] = 2;
                            pole[i-1][j+1] = 2;
                            pole[i+1][j+1] = 2;
                            *zmenaR=true;
                        }else if(r % 4 == 3 && i > 0 && j >= 0){
                            if(j < 8 && pole[i+1][j] != 1 && pole[i+1][j+2] != 1 && pole[i][j+2] != 1){
                                pole[i][j] = 0;
                                pole[i][j+1] = 0;
                                pole[i+2][j+1] = 0;
                                pole[i+1][j] = 2;
                                pole[i+1][j+2] = 2;
                                pole[i][j+2] = 2;
                                *zmenaR=true;
                            }else if(j == 8 && pole[i+2][j-1] !=1 && pole[i+2][j] != 1){
                                pole[i][j] = 0;
                                pole[i][j+1] = 0;
                                pole[i+2][j] = 2;
                                pole[i+2][j-1] = 2;
                                *zmenaR=true;
                            }
                        }
                        otoceno=1;
                        break;
                    case 3:
                        if(r % 4 == 0 && i > 0 && j<9){
                            if(j>0 && pole[i+1][j-1] != 1){
                                pole[i][j] = 0;
                                pole[i+1][j-1] = 2;
                                *zmenaR=true;
                            }else if(j == 0 && pole[i+1][j+2] != 1 && pole[i+2][j+1] != 1){
                                pole[i][j] = 0;
                                pole[i+2][j] = 0;
                                pole[i+1][j+2] = 2;
                                pole[i+2][j+1] = 2;
                                *zmenaR=true;
                            }
                        }else if(r % 4 == 1 && i > 0 && j<8  && pole[i-1][j+1] != 1){
                            pole[i][j+2] = 0;
                            pole[i-1][j+1] = 2;
                            *zmenaR=true;
                        }else if(r % 4 == 2 && i > 0 && j>0){
                            if(j < 9 && pole[i+1][j+1] != 1){
                                pole[i+2][j] = 0;
                                pole[i+1][j+1] = 2;
                                *zmenaR=true;
                            }else if(j == 9 && pole[i+1][j-2] != 1 && pole[i][j-1] != 1){
                                pole[i][j] = 0;
                                pole[i+2][j] =0;
                                pole[i+1][j-2] = 2;
                                pole[i][j-1] = 2;
                                *zmenaR=true;
                            }
                        }else if(r % 4 == 3 && i > 0 && j<9 && j>0 && pole[i+2][j] != 1){
                            pole[i+2][j] = 2;
                            pole[i+1][j-1] = 0;
                            *zmenaR=true;
                        }
                        otoceno=1;
                        break;
                    case 4: 
                        if(r % 4 == 0 && i > 0 && j<8 && j>=0 && pole[i-1][j+1] != 1 && pole[i+1][j+1] != 1 && pole[i+1][j] != 1){
                            pole[i][j] = 0;
                            pole[i][j+2] = 0;
                            pole[i+1][j+2] = 0;
                            pole[i-1][j+1] = 2;
                            pole[i+1][j+1] = 2;
                            pole[i+1][j] = 2;
                            *zmenaR=true; 
                        }else if(r % 4 == 1 && i > 0 && j>0){
                            if(j<9 && pole[i+1][j+1] != 1 && pole[i+1][j-1] != 1 && pole[i][j-1] != 1){
                                pole[i][j] = 0;
                                pole[i+2][j] = 0;
                                pole[i+2][j-1] = 0;
                                pole[i+1][j+1] = 2;
                                pole[i+1][j-1] = 2;
                                pole[i][j-1] = 2;
                                *zmenaR=true;
                            }else if(j == 9 && pole[i+1][j-2] !=1 && pole[i+2][j-2] != 1){
                                pole[i][j] = 0;
                                pole[i+1][j] = 0;
                                pole[i+1][j-2] = 2;
                                pole[i+2][j-2] = 2;
                                *zmenaR=true;
                            }
                        }else if(r % 4 == 2 && i > 0 && j<8 && pole[i][j+1] !=1 && pole[i][j+2] != 1 && pole[i+2][j+1] != 1){
                            pole[i][j] = 0;
                            pole[i+1][j] = 0;
                            pole[i+1][j+2] = 0;
                            pole[i][j+1] = 2;
                            pole[i][j+2] = 2;
                            pole[i+2][j+1] = 2;
                            *zmenaR=true;
                        }else if(r % 4 == 3 && i > 2 && j<9){
                            if(j > 0 && pole[i+1][j-1] !=1 && pole[i+1][j+1] != 1 && pole[i+2][j+1] != 1){
                                pole[i][j] = 0;
                                pole[i][j+1] = 0;
                                pole[i+2][j] = 0;
                                pole[i+1][j-1] = 2;
                                pole[i+1][j+1] = 2;
                                pole[i+2][j+1] = 2;
                                *zmenaR=true;
                            }else if(j == 0 && pole[i+1][j] !=1 && pole[i+1][j+1] !=1 && pole[i+1][j+2] != 1 && pole[i+2][j+2] != 1){
                                pole[i][j] = 0;
                                pole[i][j+1] = 0;
                                pole[i+2][j] = 0;
                                pole[i+1][j] = 2;
                                pole[i+1][j+1] = 2;
                                pole[i+1][j+2] = 2;
                                pole[i+2][j+2] = 2;
                                *zmenaR=true;
                            }
                        }                                                                                                                           
                        otoceno=1;
                        break;
                    case 5:
                        if(r % 2 == 0 && i > 0 && j < 9){
                            if(j > 0 && pole[i+2][j-1] !=1 && pole[i+2][j] != 1){
                                pole[i][j] = 0;
                                pole[i+2][j+1] = 0;
                                pole[i+2][j-1] = 2;
                                pole[i+2][j] = 2;
                                *zmenaR=true;
                            }else if(j==0 && pole[i+1][j+1] != 1 && pole[i+1][j+2] != 1 && pole[i+2][j] != 1){
                                pole[i][j] = 0;
                                pole[i+1][j] = 0;
                                pole[i+1][j+1] = 2;
                                pole[i+1][j+2] = 2;
                                pole[i+2][j] = 2;
                                *zmenaR=true;
                            }
                        }else if(r % 2 == 1 && i > 0 && j < 9 && j> 0 && pole[i-1][j] != 1 && pole[i+1][j+1] != 1){
                            pole[i+1][j] = 0;
                            pole[i+1][j-1] = 0;
                            pole[i-1][j] = 2;
                            pole[i+1][j+1] = 2;
                            *zmenaR=true;
                        }
                        otoceno=1; 
                        break;
                    case 6: 
                        if(r % 2 == 0 && i > 0 && j > 0){
                            if(j<9 && pole[i+2][j+1] != 1 && pole[i+2][j] != 1){
                                pole[i][j] = 0;
                                pole[i+2][j-1] = 0;
                                pole[i+2][j+1] = 2;
                                pole[i+2][j] = 2;
                                *zmenaR=true;
                            }else if(pole[i+1][j-2] != 1 && pole[i+2][j] != 1){
                                pole[i][j] = 0;
                                pole[i+1][j] = 0;
                                pole[i+1][j-2] = 2;
                                pole[i+2][j] = 2;
                                *zmenaR=true;
                            }
                        }else if(r % 2 == 1 && i > 0 && j < 8 && j>=0 && pole[i+1][j] != 1 && pole[i-1][j+1] != 1){
                            pole[i+1][j+1] = 0;
                            pole[i+1][j+2] = 0;
                            pole[i+1][j] = 2;
                            pole[i-1][j+1] = 2;
                            *zmenaR=true;
                        }
                        otoceno=1; 
                        break;
                }
            }
            if(otoceno == 1){
                break;
            }
        }
    }
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



// vykresleni menu
void vykresliMenu(SDL_Renderer* renderer,TTF_Font* font, int kurzor){ 
    char text1[20], text2[20], text3[20];
    SDL_Color white = {255, 255, 255, 255};

    SDL_Rect location;
        location.x = 250;    // Horizontální pozice
        location.y = 175;    // Vertikální pozice
        location.w = 95;    //Šířka
        location.h = 45;     // Výška  

    SDL_Rect location2;
        location2.x = 235;    // Horizontální pozice
        location2.y = 335;    // Vertikální pozice
        location2.w = 140;    // Šířka
        location2.h = 45;     // Výška
    
    SDL_Rect location3;
        location3.x = 255;    // Horizontální pozice
        location3.y = 495;    // Vertikální pozice
        location3.w = 90;    // Šířka
        location3.h = 45;     // Výška

    sprintf(text1,"Play");
    sprintf(text2, "Settings");
    sprintf(text3, "Quit");

    kurzor++;
    

    for(int i=4; i<6;i++){
        for(int j=4; j<11; j++){
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            vykresliCelouBunku(renderer, j*40, i*40);
        }
    }

    for(int i=8; i<10;i++){
        for(int j=4; j<11; j++){
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            vykresliCelouBunku(renderer, j*40, i*40);
        }
    }

    for(int i=12; i<14;i++){
        for(int j=4; j<11; j++){
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            vykresliCelouBunku(renderer, j*40, i*40);
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(int j=32; j<88; j++){
        vykresliMalouBunku(renderer, j*5, 5 + 32*5*kurzor-10);
    }
    for(int j=32; j<88; j++){
        vykresliMalouBunku(renderer, j*5, 5 + 32*5*kurzor+75);
    }
    for(int i=0; i<18; i++){
        vykresliMalouBunku(renderer, 155, 5 + kurzor*160-10 + i*5);
    }
    for(int i=0; i<18; i++){
        vykresliMalouBunku(renderer, 440, 5 + kurzor*160-10 + i*5);
    }


    sdl_draw_text(renderer, font, white, location, text1);
    sdl_draw_text(renderer, font, white, location2, text2);
    sdl_draw_text(renderer, font, white, location3, text3);
}


// vykresleni menu
void vykresliMenuObtiznosti(SDL_Renderer* renderer,TTF_Font* font, int kurzor){ 
    char text1[20], text2[20], text3[20];
    SDL_Color white = {255, 255, 255, 255};

    SDL_Rect location;
        location.x = 250;    // Horizontální pozice
        location.y = 175;    // Vertikální pozice
        location.w = 95;    //Šířka
        location.h = 45;     // Výška  

    SDL_Rect location2;
        location2.x = 235;    // Horizontální pozice
        location2.y = 335;    // Vertikální pozice
        location2.w = 140;    // Šířka
        location2.h = 45;     // Výška
    
    SDL_Rect location3;
        location3.x = 255;    // Horizontální pozice
        location3.y = 495;    // Vertikální pozice
        location3.w = 90;    // Šířka
        location3.h = 45;     // Výška

    sprintf(text1,"Easy");
    sprintf(text2, "Medium");
    sprintf(text3, "Hard");

    kurzor++;
    

    for(int i=4; i<6;i++){
        for(int j=4; j<11; j++){
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            vykresliCelouBunku(renderer, j*40, i*40);
        }
    }

    for(int i=8; i<10;i++){
        for(int j=4; j<11; j++){
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            vykresliCelouBunku(renderer, j*40, i*40);
        }
    }

    for(int i=12; i<14;i++){
        for(int j=4; j<11; j++){
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            vykresliCelouBunku(renderer, j*40, i*40);
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(int j=32; j<88; j++){
        vykresliMalouBunku(renderer, j*5, 5 + 32*5*kurzor-10);
    }
    for(int j=32; j<88; j++){
        vykresliMalouBunku(renderer, j*5, 5 + 32*5*kurzor+75);
    }
    for(int i=0; i<18; i++){
        vykresliMalouBunku(renderer, 155, 5 + kurzor*160-10 + i*5);
    }
    for(int i=0; i<18; i++){
        vykresliMalouBunku(renderer, 440, 5 + kurzor*160-10 + i*5);
    }


    sdl_draw_text(renderer, font, white, location, text1);
    sdl_draw_text(renderer, font, white, location2, text2);
    sdl_draw_text(renderer, font, white, location3, text3);
}