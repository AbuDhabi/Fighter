#include "header.h"
#include "globals.h"

int MAXX = 768;
int MAXY = 628;
SDL_Surface* BITMAPS[MAX_BITMAPS]; //255 is more than I'll need
Mix_Chunk* SOUNDS[MAX_SOUNDS];
TTF_Font* FONTS[MAX_FONTS]; // HAHAHA
TTF_Font* DEFAULT_FONT;
SDL_Surface* MAIN_SCREEN;
bool END_PROGRAM = false;
Tile TILES[MAX_TILES];
SDL_Color COLORS[MAX_COLORS];

//game state
Game game;

int main ( int argc, char** argv ) {
    srand((unsigned)time(0)); // IT'S RANDOM TIME
    //putenv("SDL_VIDEO_CENTERED=1");
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )    {
        printf( "Unable to initialize SDL: %s\n", SDL_GetError() );
        return 1;
    }
    if (TTF_Init() < 0) {
        fprintf(stderr, "Unable to initialize TTF: %s\n", TTF_GetError());
        exit(1);
    }
    SDL_EnableUNICODE( SDL_ENABLE );  
    atexit(SDL_Quit);
    atexit(TTF_Quit);
    if ( ( SDL_EnableKeyRepeat( 100, SDL_DEFAULT_REPEAT_INTERVAL *2 ) ) ) {
        fprintf( stderr, "Setting keyboard repeat failed: %s\n", SDL_GetError());
        return 1;
    }

    // create a new window
    MAIN_SCREEN = SDL_SetVideoMode(MAXX, MAXY, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !MAIN_SCREEN )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }
    SDL_WM_SetCaption("Fighter","Fighter");

    bool media_load = load_media();
    if (!media_load) {
        printf("Could not load media properly.");
        return 1;
    }
    
    new_game_setup();
    


    // program main loop
    int state = STATE_INITIAL;
    while (!END_PROGRAM) {
        clear_screen();
        if (state == STATE_INITIAL) { state = intro(); }
        if (state == STATE_TITLE) { state = title_screen(); }
        if (state == STATE_CHARGEN) { state = chargen(); }
        if (state == STATE_AFTER_CHARGEN) { state = after_chargen(); }
        if (state == STATE_GENERATE_WORLD) { 
                generate_maps(); 
                state = STATE_MAPMODE;
        }
        if (state == STATE_MAPMODE) { 
                reveal_los(); // a bit of a placeholder solution
                state = mapmode(); 
        }
        if (state == STATE_INVENTORY) { state = show_inventory(); }
        if (state == STATE_MESSAGE_LOG) { state = message_log(); }
        if (state == STATE_HELP_MAPMODE) { state = print_help_mapmode(); }
        if (state == STATE_GAME_OVER) { state = game_over(); }
        if (state == STATE_EXIT) { END_PROGRAM = true; }
    } // end main loop
    
    SDL_EnableUNICODE( SDL_DISABLE ); 
    clean_up();
    printf("Exited cleanly.\n");
    return 0;
}
