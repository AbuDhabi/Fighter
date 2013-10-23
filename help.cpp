#include "header.h"
#include "globals.h"

int print_help_mapmode() {
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
        
        put_text(4,3,"This is the help file for Fighter's map mode.",COLORS[COLOR_HELPTEXT],COLORS[COLOR_DEFAULT_BG]);
        
        put_text(4,5,"Keys:",COLORS[COLOR_HELPTEXT],COLORS[COLOR_DEFAULT_BG]);
        put_text(5,6,"Arrow Keys, Numpad Directions - Move, or select target",COLORS[COLOR_HELPTEXT],COLORS[COLOR_DEFAULT_BG]);
        put_text(5,7,"a - Apply, use in obvious manner",COLORS[COLOR_HELPTEXT],COLORS[COLOR_DEFAULT_BG]);
        put_text(5,8,"g - Get, pick up item you're standing on",COLORS[COLOR_HELPTEXT],COLORS[COLOR_DEFAULT_BG]);
        put_text(5,9,". - Stand still for a tick",COLORS[COLOR_HELPTEXT],COLORS[COLOR_DEFAULT_BG]);
        put_text(5,10,"F1 - Reach this help file",COLORS[COLOR_HELPTEXT],COLORS[COLOR_DEFAULT_BG]);
        put_text(5,11,"` - Display message log",COLORS[COLOR_HELPTEXT],COLORS[COLOR_DEFAULT_BG]);
        put_text(5,12,"i - Inventory",COLORS[COLOR_HELPTEXT],COLORS[COLOR_DEFAULT_BG]);
        put_text(5,13,"Esc - Exit game",COLORS[COLOR_HELPTEXT],COLORS[COLOR_DEFAULT_BG]);
        put_text(5,14,"Shift - Use exit from level, go to another one",COLORS[COLOR_HELPTEXT],COLORS[COLOR_DEFAULT_BG]);
        
        put_text(4,37,"Press any key to go back to map mode.",COLORS[COLOR_HELPTEXT],COLORS[COLOR_DEFAULT_BG]);

        SDL_Flip(MAIN_SCREEN);
        SDL_Delay(10); // manipulate at will
  
    }
    
    return STATE_MAPMODE;
}
