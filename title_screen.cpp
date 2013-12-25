#include "header.h"
#include "globals.h"

int title_screen() {
    bool done = false;
    while (!done) {
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // check for messages
            switch (event.type) {
                // exit if the window is closed
            case SDL_QUIT:
                return -1;
                break;
                // check for keypresses
            case SDL_KEYDOWN:
                {
                    if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_1) {
                        return STATE_CHARGEN;
                    }
                    if (event.key.keysym.sym == SDLK_2) {
                        // not implemented yet
                    }
                    if (event.key.keysym.sym == SDLK_3) {
                        return STATE_EXIT;
                    }
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        return STATE_EXIT;
                    }
                    break;
                }
            } // end switch
        } // end of message processing
        
        clear_screen();
        
        put_text(28,10,"Fighter");
        put_text(28,11,"  v1.0 ");
        put_text(25,20,"1 - NEW GAME");
        put_text(25,21,"2 - LOAD GAME");
        put_text(25,22,"3 - EXIT");
        
        SDL_Flip(MAIN_SCREEN);
        SDL_Delay(10); // manipulate at will
  
    }
    return STATE_TITLE;
}
