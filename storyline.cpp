#include "header.h"
#include "globals.h"

int print_text_cutscene(const char* text) {
    clear_screen();
    for (int i=0;i<64;i++) {
        if (i%2) put_text(i,1,"*");
        else put_text(i,0,"*");
        if (i%2) put_text(i,38,"*");
        else put_text(i,37,"*");
    }
    put_text(63,0,"*");
    put_text(62,1,"*");
    for (int i=0;i<39;i++) {
        if (i%2) put_text(0,i,"*");
        else put_text(1,i,"*");
        if (i%2) put_text(63,i,"*");
        else put_text(62,i,"*");
    }
    put_text(0,38,"*");
    put_text(1,37,"*");
    
    // improved beta version
    const int limit = 70;
    char temp[limit];
    temp[limit-1] = '\0';
    int n = 0, y = 3;
    int last_space_n = -1, last_space_i = -1;
    for (unsigned int i=0;i<strlen(text);i++) {
        if (text[i] == ' ') {
                last_space_n = n;
                last_space_i = i;
        }
        if ((n == limit-1)) {
            temp[last_space_n] = '\0';
            put_text(3,y,temp);
            n = 0;
            y++;
            i = last_space_i+1;
        }
        temp[n] = text[i];
        n++;
        if (i == strlen(text)-1) {
            temp[n] = '\0';
            put_text(3,y,temp);
        }
    }
    
    return 0;
}

int after_chargen() {
    char temp[3200];
    char sex[8];
    if (player.sex == SEX_FEMALE) snprintf(sex,8,"woman"); else snprintf(sex,8,"man");
    snprintf(temp,3200,"The King has been kidnapped by anarchists. Are you %s enough to rescue the King? Prove yourself - or die trying.",sex);
    snprintf(temp,3200,"%s                     In the meantime, just slay these zombies.",temp);
    print_text_cutscene(temp);
    //print_text_cutscene("Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.");
    /*                                                        // stop here
    put_text(3,3,"The King has been kidnapped by anarchists. Are you        ");
    if (player.sex == SEX_FEMALE) put_text(54,3,"woman"); else put_text(54,3,"man");
    put_text(3,4,"enough to rescue the King? Prove yourself - or die trying.");
    */
    
    SDL_Flip(MAIN_SCREEN);
    SDL_Delay(2000);

    return STATE_GENERATE_WORLD;
}
