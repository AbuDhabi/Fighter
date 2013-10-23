#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

extern int MAXX;
extern int MAXY;
extern SDL_Surface* BITMAPS[255];
extern Mix_Chunk* SOUNDS[255];
extern TTF_Font* FONTS[255];
extern TTF_Font* DEFAULT_FONT;
extern SDL_Surface* MAIN_SCREEN;
extern bool END_PROGRAM;
extern Game game;
extern Tile TILES[255];
extern SDL_Color COLORS[255];
extern Critter TEMPLATES[255];
extern Item ITEM_TEMPLATES[255];


#endif // GLOBALS_H_INCLUDED
