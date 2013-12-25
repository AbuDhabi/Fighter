#include "header.h"
#include "globals.h"

int game_over() {
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
                    done = true;
                    break;
                }
            } // end switch
        } // end of message processing
        
        clear_screen();
        
        char temp[80];
        snprintf(temp,80,"You have died on level %d.",player.level_id);
        
        put_text(4,2,temp);
        
        for (int i=0;i<MAX_STATUS_MESSAGES;i++) {
            put_text(5,4+i,game.status_msgs[i]);
        }
        
        put_text(4,37,"Press any key to exit to title.",COLORS[COLOR_HELPTEXT],COLORS[COLOR_DEFAULT_BG]);

        SDL_Flip(MAIN_SCREEN);
        SDL_Delay(10); // manipulate at will
  
    }
    
    return STATE_TITLE;
    /*
    print_text_cutscene("You have died.");
    
    SDL_Flip(MAIN_SCREEN);
    SDL_Delay(2000);

    return STATE_EXIT; // might want to change this to STATE_TITLE
    */
}
