#include "header.h"
#include "globals.h"

int message_log() {
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
                    return STATE_MAPMODE;
                    break;
                }
            } // end switch
        } // end of message processing
        
        clear_screen();
        
        put_text(4,2,"Messages (newest first):");
        
        for (int i=0;i<MAX_STATUS_MESSAGES;i++) {
            put_text(5,4+i,game.status_msgs[i]);
        }
        
        put_text(4,37,"Press any key to go back to map mode.",COLORS[COLOR_HELPTEXT],COLORS[COLOR_DEFAULT_BG]);

        SDL_Flip(MAIN_SCREEN);
        SDL_Delay(10); // manipulate at will
  
    }
    
    return STATE_MAPMODE;
}
