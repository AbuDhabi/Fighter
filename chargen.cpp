#include "header.h"
#include "globals.h"

int chargen() {
    snprintf(player.name,16,"Napoleon");
    player.sex = SEX_MALE;
    int index = 0;
    int progress = 0;
    char sex[8] = "Male";
    player.x = 10;
    player.y = 10;
    player.atk = 200;
    player.dmg = 200;
    player.slots[0] = 0; // should be a paperweight

    bool done = false;
    while (!done) {
        if (progress < 0) return 1; // back to title if you back out
        
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
                    if (event.key.keysym.sym == SDLK_RETURN) { // text input complete
                        progress++;
                    }
                    if (event.key.keysym.sym == SDLK_ESCAPE) { // go back to title
                        progress--;
                    }
                    if (progress == 0) {
                        if (event.key.keysym.sym == SDLK_BACKSPACE) { // delete last letter
                            index--;
                            if (index < 0) index = 0;
                            player.name[index] = '\0';
                        } else {
                            snprintf(player.name,16,"%s%c",player.name,(char)event.key.keysym.unicode);
                            index = strlen(player.name);
                        }
                    }
                    if (progress == 1) {
                        if ((char)event.key.keysym.unicode == 'm' || (char)event.key.keysym.unicode == 'M') {
                            player.sex = SEX_MALE;
                            snprintf(sex,8,"Male");
                        } else if ((char)event.key.keysym.unicode == 'f' || (char)event.key.keysym.unicode == 'F') {
                            player.sex = SEX_FEMALE;
                            snprintf(sex,8,"Female");
                        }                
                    }
                    if (progress == 3) {
                        player.color = COLORS[COLOR_DEFAULT_FG];
                        player.visual = '@';
                        player.x = 10;
                        player.y = 10;
                        return STATE_AFTER_CHARGEN; // done chargen
                    }
                    break;
                }
            } // end switch
        } // end of message processing
        
        clear_screen();
        
        put_text(5,5,"Please enter your name: ");
        put_text(30,5,player.name);
        if (progress >= 1) {
            // in your face, queers!
            put_text(5,7,"Please enter your sex (M/F): ");
            put_text(35,7,sex);
        }
        if (progress >= 2) {
            put_text(10,20,"Are you sure? Press Enter to continue,");
            put_text(10,21,"or Escape to go back.");
        }
        
        SDL_Flip(MAIN_SCREEN);
        SDL_Delay(100);
  
    }

    return STATE_TITLE;
}
