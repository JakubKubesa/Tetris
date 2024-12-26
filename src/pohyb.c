#include "tetris.h"
#include <string.h>
#include <time.h>



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
