#include "header.h"
#include "globals.h"

int game_over() {
    print_text_cutscene("You have died.");
    
    SDL_Flip(MAIN_SCREEN);
    SDL_Delay(2000);

    return STATE_EXIT; // might want to change this to STATE_TITLE
}
