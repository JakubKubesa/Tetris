#ifndef TETRIS_H
#define TETRIS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

void vykresliBunku(SDL_Renderer* renderer, int x, int y);
void vykresliCelouBunku(SDL_Renderer* renderer, int x, int y);

void vykresliMenu(SDL_Renderer* renderer,TTF_Font* font, int kurzor);
void vykresliMenuObtiznosti(SDL_Renderer* renderer,TTF_Font* font, int kurzor);
int vykresliZakladniPlochu(SDL_Renderer* renderer, int pole[][10], int delka, int randomObjekt, int nasledujiciObjekt, int pole2[][10], int delka2, int starePole[][10], int prvniCyklus);
void jeMoznoSObjektem(int pole[][10], int delka, bool* posunDolu1, bool* posunDoprava, bool* posunDoleva);
void posun(int pole[][10], int delka, int posun, bool* muze1);
void otocObjekt(int pole[][10], int delka, int r, int objekt, bool *zmenaR);

void sdl_draw_text(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Rect location, const char* text);

void vykresliCtverec(int pole[][10], int nasledujici);
void vykresliIcko(int pole[][10], int nasledujici);
void vykresliLko(int pole[][10], int nasledujici);
void vykresliTecko(int pole[][10], int nasledujici);
void vykresliJecko(int pole[][10], int nasledujici);
void vykresliSko(int pole[][10], int nasledujici);
void vykresliZetko(int pole[][10], int nasledujici);

#endif
