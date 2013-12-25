#include "header.h"
#include "globals.h"

int generate_critter_templates() {
    // the first critter is the default human
    for (int i=CRITTER_HUMAN+1;i<MAX_CRITTER_TEMPLATES;i++) { 
        game.CRITTER_TEMPLATES[i] = game.CRITTER_TEMPLATES[CRITTER_HUMAN]; // this is the base
        snprintf(game.CRITTER_TEMPLATES[i].name,80,"CR%d",i); // assign generic name
        int roll = rand()%CRITTER_FLAG0_LASTFLAG +1; // random assortment of flags
        roll = roll & (rand()%CRITTER_FLAG0_LASTFLAG +1); // less flags == good
        // take a look at flags and eliminate conflicting ones
        if (roll & CRITTER_FLAG0_ANGRY && roll & CRITTER_FLAG0_MELLOW) {
            roll = roll & ~(CRITTER_FLAG0_ANGRY | CRITTER_FLAG0_MELLOW);
        }
        if (roll & CRITTER_FLAG0_ELDER && roll & CRITTER_FLAG0_YOUNG) {
            roll = roll & ~(CRITTER_FLAG0_ELDER | CRITTER_FLAG0_YOUNG);
        }
        if (roll & CRITTER_FLAG0_FAST && roll & CRITTER_FLAG0_SLOW) {
            roll = roll & ~(CRITTER_FLAG0_FAST | CRITTER_FLAG0_SLOW);
        }
        if (roll & CRITTER_FLAG0_INTELLIGENT && roll & CRITTER_FLAG0_STUPID) {
            roll = roll & ~(CRITTER_FLAG0_INTELLIGENT | CRITTER_FLAG0_STUPID);
        }
        if (roll & CRITTER_FLAG0_SKELETAL && roll & CRITTER_FLAG0_ZOMBIE) {
            roll = roll & ~(CRITTER_FLAG0_SKELETAL | CRITTER_FLAG0_ZOMBIE);
        }
        if (roll & CRITTER_FLAG0_SMALL && roll & CRITTER_FLAG0_BIG) {
            roll = roll & ~(CRITTER_FLAG0_SMALL | CRITTER_FLAG0_BIG);
        }
        if (roll & CRITTER_FLAG0_WEAK && roll & CRITTER_FLAG0_STRONG) {
            roll = roll & ~(CRITTER_FLAG0_WEAK | CRITTER_FLAG0_STRONG);
        }
        
        // assign flags to critter
        game.CRITTER_TEMPLATES[i].flags[0] = roll;
        // modify the critter according to its flags
        if (roll & CRITTER_FLAG0_ELDER) { 
                game.CRITTER_TEMPLATES[i].arm += 2; 
                game.CRITTER_TEMPLATES[i].atk += 2; 
                game.CRITTER_TEMPLATES[i].dmg += 2; 
                game.CRITTER_TEMPLATES[i].def += 2; 
                char temp[80];
                snprintf(temp,80,"%s",game.CRITTER_TEMPLATES[i].name);
                snprintf(game.CRITTER_TEMPLATES[i].name,80,"Elder %s",temp);
        }
        if (roll & CRITTER_FLAG0_YOUNG) { 
                game.CRITTER_TEMPLATES[i].arm -= 2; 
                game.CRITTER_TEMPLATES[i].atk -= 2; 
                game.CRITTER_TEMPLATES[i].dmg -= 2; 
                game.CRITTER_TEMPLATES[i].def -= 2; 
                char temp[80];
                snprintf(temp,80,"%s",game.CRITTER_TEMPLATES[i].name);
                snprintf(game.CRITTER_TEMPLATES[i].name,80,"Young %s",temp);
        }
        if (roll & CRITTER_FLAG0_ANGRY) { 
                game.CRITTER_TEMPLATES[i].atk += 5; 
                char temp[80];
                snprintf(temp,80,"%s",game.CRITTER_TEMPLATES[i].name);
                snprintf(game.CRITTER_TEMPLATES[i].name,80,"Angry %s",temp);
        }
        if (roll & CRITTER_FLAG0_BIG) { 
                game.CRITTER_TEMPLATES[i].dmg += 5; 
                char temp[80];
                snprintf(temp,80,"%s",game.CRITTER_TEMPLATES[i].name);
                snprintf(game.CRITTER_TEMPLATES[i].name,80,"Big %s",temp);
        }
        if (roll & CRITTER_FLAG0_FAST) { 
                game.CRITTER_TEMPLATES[i].atk += 5; 
                game.CRITTER_TEMPLATES[i].def += 5; 
                char temp[80];
                snprintf(temp,80,"%s",game.CRITTER_TEMPLATES[i].name);
                snprintf(game.CRITTER_TEMPLATES[i].name,80,"Fast %s",temp);
        }
        if (roll & CRITTER_FLAG0_INTELLIGENT) { 
                // no effect now!
                //snprintf(game.CRITTER_TEMPLATES[i].name,80,"Intelligent %s",game.CRITTER_TEMPLATES[i].name);
        }
        if (roll & CRITTER_FLAG0_MELLOW) { 
                // no effect
                //snprintf(game.CRITTER_TEMPLATES[i].name,80,"Mellow %s",game.CRITTER_TEMPLATES[i].name);
        }
        if (roll & CRITTER_FLAG0_SKELETAL) { 
                game.CRITTER_TEMPLATES[i].arm += 5; 
                char temp[80];
                snprintf(temp,80,"%s",game.CRITTER_TEMPLATES[i].name);
                snprintf(game.CRITTER_TEMPLATES[i].name,80,"Skeletal %s",temp);
        }
        if (roll & CRITTER_FLAG0_SLOW) { 
                game.CRITTER_TEMPLATES[i].atk -= 5; 
                game.CRITTER_TEMPLATES[i].def -= 5; 
                char temp[80];
                snprintf(temp,80,"%s",game.CRITTER_TEMPLATES[i].name);
                snprintf(game.CRITTER_TEMPLATES[i].name,80,"Slow %s",temp);
        }
        if (roll & CRITTER_FLAG0_SMALL) { 
                game.CRITTER_TEMPLATES[i].dmg -= 5; 
                char temp[80];
                snprintf(temp,80,"%s",game.CRITTER_TEMPLATES[i].name);
                snprintf(game.CRITTER_TEMPLATES[i].name,80,"Small %s",temp);
        }
        if (roll & CRITTER_FLAG0_STRONG) { 
                game.CRITTER_TEMPLATES[i].atk += 5; 
                game.CRITTER_TEMPLATES[i].dmg += 5; 
                char temp[80];
                snprintf(temp,80,"%s",game.CRITTER_TEMPLATES[i].name);
                snprintf(game.CRITTER_TEMPLATES[i].name,80,"Strong %s",temp);
        }
        if (roll & CRITTER_FLAG0_STUPID) { 
                // no effect
                //snprintf(game.CRITTER_TEMPLATES[i].name,80,"Stupid %s",game.CRITTER_TEMPLATES[i].name);
        }
        if (roll & CRITTER_FLAG0_WEAK) { 
                game.CRITTER_TEMPLATES[i].atk -= 5; 
                game.CRITTER_TEMPLATES[i].dmg -= 5; 
                char temp[80];
                snprintf(temp,80,"%s",game.CRITTER_TEMPLATES[i].name);
                snprintf(game.CRITTER_TEMPLATES[i].name,80,"Weak %s",temp);
        }
        if (roll & CRITTER_FLAG0_ZOMBIE) { 
                game.CRITTER_TEMPLATES[i].maxhp += 10; 
                game.CRITTER_TEMPLATES[i].hp += 10; 
                char temp[80];
                snprintf(temp,80,"%s",game.CRITTER_TEMPLATES[i].name);
                snprintf(game.CRITTER_TEMPLATES[i].name,80,"Zombie %s",temp);
        }
        // don't accidentally create negative stat monsters
        if (game.CRITTER_TEMPLATES[i].arm <= 0) game.CRITTER_TEMPLATES[i].arm = 1;
        if (game.CRITTER_TEMPLATES[i].def <= 0) game.CRITTER_TEMPLATES[i].def = 1;
        if (game.CRITTER_TEMPLATES[i].atk <= 0) game.CRITTER_TEMPLATES[i].atk = 1;
        if (game.CRITTER_TEMPLATES[i].dmg <= 0) game.CRITTER_TEMPLATES[i].dmg = 1;
        if (game.CRITTER_TEMPLATES[i].hit_dice <= 0) game.CRITTER_TEMPLATES[i].hit_dice = 1;
        if (game.CRITTER_TEMPLATES[i].maxhp <= 0) game.CRITTER_TEMPLATES[i].maxhp = 1;
        if (game.CRITTER_TEMPLATES[i].hp <= 0) game.CRITTER_TEMPLATES[i].hp = 1;
        if (game.CRITTER_TEMPLATES[i].maxsp <= 0) game.CRITTER_TEMPLATES[i].maxsp = 1;
        if (game.CRITTER_TEMPLATES[i].sp <= 0) game.CRITTER_TEMPLATES[i].sp = 1;
        
        // random letter, this is a placeholder
        int rolling = 65+rand()%26;
        if (rand()%2) rolling += 32;
        game.CRITTER_TEMPLATES[i].visual = (char)rolling;
        // random colour!
        rolling = rand()%5;
        game.CRITTER_TEMPLATES[i].color = COLORS[rolling];
        if (rolling == COLOR_BLACK) game.CRITTER_TEMPLATES[i].color = COLORS[COLOR_WHITE];
        
    }
    return 0;
}

// gets full critter stats, including modifiers
int get_atk(int critter_id) {
    int mod = 0;
    for (int i=0;i<ITEM_SLOTS;i++) {
        if (game.critters[critter_id].slots[i] != ITEM_NONE_EQUIPPED)
            mod += game.critters[critter_id].inventory[game.critters[critter_id].slots[i]].atk;
    }
    return game.critters[critter_id].atk + mod;
}

int get_def(int critter_id) {
    int mod = 0;
    for (int i=0;i<ITEM_SLOTS;i++) {
        if (game.critters[critter_id].slots[i] != ITEM_NONE_EQUIPPED)
            mod += game.critters[critter_id].inventory[game.critters[critter_id].slots[i]].def;
    }
    return game.critters[critter_id].def + mod;
}

int get_arm(int critter_id) {
    int mod = 0;
    for (int i=0;i<ITEM_SLOTS;i++) {
        if (game.critters[critter_id].slots[i] != ITEM_NONE_EQUIPPED)
            mod += game.critters[critter_id].inventory[game.critters[critter_id].slots[i]].arm;
    }
    return game.critters[critter_id].arm + mod;
}

int get_dmg(int critter_id) {
    int mod = 0;
    for (int i=0;i<ITEM_SLOTS;i++) {
        if (game.critters[critter_id].slots[i] != ITEM_NONE_EQUIPPED)
            mod += game.critters[critter_id].inventory[game.critters[critter_id].slots[i]].dmg;
    }
    return game.critters[critter_id].dmg + mod;
}

int get_critter_name(char * output, int critter_id) {
    // totally a placeholder in lieu of something more robust
    //char temp[40]; temp[0] = '\0';
    //if (game.critters[critter_id].flags[0] & CRITTER_FLAG0_ZOMBIE)
    //    snprintf(temp,40,"Zombie ");
    // danger, will robinson! how many chars does this have?
    snprintf(output,80,"%s",game.critters[critter_id].name);
    return 0;
}
