#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

extern int MAXX;
extern int MAXY;
extern SDL_Surface* BITMAPS[MAX_BITMAPS];
extern Mix_Chunk* SOUNDS[MAX_SOUNDS];
extern TTF_Font* FONTS[MAX_FONTS];
extern TTF_Font* DEFAULT_FONT;
extern SDL_Surface* MAIN_SCREEN;
extern bool END_PROGRAM;
extern Game game;
extern Tile TILES[MAX_TILES];
extern SDL_Color COLORS[MAX_COLORS];


#endif // GLOBALS_H_INCLUDED
