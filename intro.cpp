#include "header.h"
#include "globals.h"

int intro() {
    for (int i=0;i<MAP_MAXX;i++) {
        if (i%2) put_text(i,1,"*");
        else put_text(i,0,"*");
        if (i%2) put_text(i,MAP_MAXY+2,"*");
        else put_text(i,MAP_MAXY+1,"*");
    }
    put_text(MAP_MAXX-1,0,"*");
    put_text(MAP_MAXX-2,1,"*");
    for (int i=0;i<MAP_MAXY+3;i++) {
        if (i%2) put_text(0,i,"*");
        else put_text(1,i,"*");
        if (i%2) put_text(MAP_MAXX-1,i,"*");
        else put_text(MAP_MAXX-2,i,"*");
    }
    put_text(0,MAP_MAXX+2,"*");
    put_text(1,MAP_MAXX+1,"*");
    // big-ass ascii
    put_text(7,15,"FFFFFFF  II   GGGGG    HH   HH  TTTTTTTT  EEEEEEE  RRRRRR ");
    put_text(7,16,"FF           GG   GG   HH   HH     TT     EE       RR   RR");
    put_text(7,17,"FFFFF    II  GG        HHHHHHH     TT     EEEEE    RR   RR");
    put_text(7,18,"FF       II  GG  GGGG  HH   HH     TT     EE       RRRRRR ");
    put_text(7,19,"FF       II  GG   GG   HH   HH     TT     EE       RR   RR");
    put_text(7,20,"FF       II   GGGGGG   HH   HH     TT     EEEEEEE  RR   RR");
    SDL_Flip(MAIN_SCREEN);
    SDL_Delay(1000);
    
    return STATE_TITLE;
}
