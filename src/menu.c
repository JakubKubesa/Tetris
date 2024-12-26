#include "tetris.h"
#include <string.h>
#include <time.h>




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