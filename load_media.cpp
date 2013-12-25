#include "header.h"
#include "globals.h"

SDL_Surface* load_bitmap(const char * path) {
    SDL_Surface * temp;
    temp = IMG_Load(path);
    if (!temp) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return NULL;
    } else {
        return temp;
    }
}

Mix_Chunk* load_sound(const char * path) {
    Mix_Chunk * temp;
    temp = Mix_LoadWAV(path);
    if (!temp) {
        printf("Unable to load wave file: %s\n", Mix_GetError());
        return NULL;
    } else {
        return temp;
    }
}

bool load_media() {
    // prevent undefined shit with media
    // WARNING: Assumes MAX_BITMAPS == MAX_SOUNDS
    for (int i=0;i<MAX_BITMAPS;i++) {
        BITMAPS[i] = NULL;
        SOUNDS[i] = NULL;
    }

    // load fonts
    FONTS[0] = TTF_OpenFont("data//font//georgia.ttf", 16);
    FONTS[1] = TTF_OpenFont("data//font//cour.ttf", 16);
    FONTS[2] = TTF_OpenFont("data//font//Reactor-Sans.ttf", 12);
    FONTS[3] = TTF_OpenFont("data//font//player1upblack.ttf", 12);

    DEFAULT_FONT = FONTS[1];

    // load images
    //BITMAPS[IMG_INTRO] = load_bitmap("data//img//titlescreen.png");

    //load sounds
    //SOUNDS[SND_MAIN_MENU] = load_sound("data//snd//menu.ogg");



    return true;
}

bool clean_up() {
    // WARNING: Assumes all these are the same
    for (int i=0;i<MAX_BITMAPS;i++) {
        if (FONTS[i] != NULL) {
            SDL_FreeSurface(BITMAPS[i]);
            Mix_FreeChunk(SOUNDS[i]);
            TTF_CloseFont(FONTS[i]);
        }
    }
    SDL_FreeSurface(MAIN_SCREEN); // this is important and needs to stay

    return true;
}




