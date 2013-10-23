#include "header.h"
#include "globals.h"

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
    char temp[40]; temp[0] = '\0';
    if (game.critters[critter_id].flags[0] & CRITTER_FLAG_ZOMBIE)
        snprintf(temp,40,"Zombie ");
    // danger, will robinson! how many chars does this have?
    snprintf(output,80,"%s%s",temp,game.critters[critter_id].name);
    return 0;
}
