#include "header.h"
#include "globals.h"

// prints in default colours
int put_text(int x, int y, const char *text) {
    //if (x < 0 || x > MAP_MAXX) return 1;
    //if (y < 0 || y > MAP_MAXY+1) return 1;
    if (strlen(text) == 0) return 0; // no text, nothing to draw
    SDL_Surface * text_surface;
    text_surface = TTF_RenderText_Solid(DEFAULT_FONT, text, COLORS[COLOR_DEFAULT_FG]);
    SDL_Rect text_rect;
    text_rect.x = x*12;
    text_rect.y = y*16;
    text_rect.w = text_surface->w;
    text_rect.h = text_surface->h;
    int r = COLORS[COLOR_DEFAULT_BG].r, g = COLORS[COLOR_DEFAULT_BG].g, b = COLORS[COLOR_DEFAULT_BG].b;
    //int unused = COLORS[COLOR_DEFAULT_BG].unused;
    boxRGBA(MAIN_SCREEN,text_rect.x,text_rect.y+4,text_rect.x+text_rect.w,text_rect.y+text_rect.h-4,r,g,b,255);
    SDL_BlitSurface(text_surface,0,MAIN_SCREEN,&text_rect);
    SDL_FreeSurface(text_surface);
    return 0;
}

// prints in chosen colours
int put_text(int x, int y, const char *text, SDL_Color fg, SDL_Color bg) {
    //if (fg == NULL) fg = COLORS[COLOR_DEFAULT_FG];
    //if (bg == NULL) bg = COLORS[COLOR_DEFAULT_BG];
    if (strlen(text) == 0) return 0; // no text, nothing to draw
    SDL_Surface * text_surface;
    text_surface = TTF_RenderText_Solid(DEFAULT_FONT, text, fg);
    SDL_Rect text_rect;
    text_rect.x = x*12;
    text_rect.y = y*16;
    text_rect.w = text_surface->w;
    text_rect.h = text_surface->h;
    int r = bg.r, g = bg.g, b = bg.b;
    //int unused = bg.unused;
    boxRGBA(MAIN_SCREEN,text_rect.x,text_rect.y+4,text_rect.x+text_rect.w,text_rect.y+text_rect.h-4,r,g,b,255);
    SDL_BlitSurface(text_surface,0,MAIN_SCREEN,&text_rect);
    SDL_FreeSurface(text_surface);
    return 0;
}

int print_tile(int x, int y, Tile tile) {
    char text[8];
    snprintf(text,8,"%c",tile.visual);
    if (x < 0 || x > MAP_MAXX) return 1;
    if (y < 0 || y > MAP_MAXY) return 1;
    SDL_Surface * text_surface;
    text_surface = TTF_RenderText_Solid(DEFAULT_FONT, text, tile.fg);
    SDL_Rect text_rect;
    text_rect.x = x*12;
    text_rect.y = y*16;
    text_rect.w = text_surface->w;
    text_rect.h = text_surface->h;
    boxRGBA(MAIN_SCREEN,text_rect.x,text_rect.y+4,text_rect.x+text_rect.w,text_rect.y+text_rect.h-4,tile.bg.r,tile.bg.g,tile.bg.b,255);
    SDL_BlitSurface(text_surface,0,MAIN_SCREEN,&text_rect);
    SDL_FreeSurface(text_surface);
    return 0;
}

int add_status_msg(const char * text) {
    for (int i=MAX_STATUS_MESSAGES-1;i>0;i--) {
        snprintf(game.status_msgs[i],MAX_STATUS_MESSAGE_LENGTH,"%s",game.status_msgs[i-1]);
    }
    snprintf(game.status_msgs[0],MAX_STATUS_MESSAGE_LENGTH,"%s",text);
    return 0;
}
/* this is unusable because I need colours checked for every tile
int print_tile_row(int y, int level) {
    char tilerow[MAP_MAXX+8];
    tilerow[MAP_MAXX] = '\0';
    for (int i=0;i<MAP_MAXX;i++){
        tilerow[i] = game.levels[level].tiles[i][y].visual;
    }
    SDL_Surface * text_surface;
    text_surface = TTF_RenderText_Solid(DEFAULT_FONT, tilerow, tile.fg);
    SDL_Rect text_rect;
    text_rect.x = x*12;
    text_rect.y = y*16;
    // unnecessary given that it's the bottom layer
    //text_rect.w = text_surface->w;
    //text_rect.h = text_surface->h;
    //boxRGBA(MAIN_SCREEN,text_rect.x,text_rect.y+4,text_rect.x+text_rect.w,text_rect.y+text_rect.h-4,0,0,0,255);
    SDL_BlitSurface(text_surface,0,MAIN_SCREEN,&text_rect);
    SDL_FreeSurface(text_surface);
    return 0;


}
*/
