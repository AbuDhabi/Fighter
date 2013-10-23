#include "header.h"
#include "globals.h"

float distance_between_critters(int critter_a, int critter_b) {
    // this assumes same level
    // not sure if want
    return sqrt(pow(game.critters[critter_a].x - game.critters[critter_b].x,2) + pow(game.critters[critter_a].y - game.critters[critter_b].y,2));
}

int confused_move(int critter_id, int level_id) {
    int newx, newy;
    newx = game.critters[critter_id].x + rand()%3-1;
    newy = game.critters[critter_id].y + rand()%3-1;
    if (!check_solid(newx,newy,level_id)){
        game.critters[critter_id].x = newx;
        game.critters[critter_id].y = newy;
    }
    
    return 0;
}

int chase_move(int critter_id, int level_id) {
    int newx, newy;
    
    if (player.x > game.critters[critter_id].x) newx = (game.critters[critter_id].x) + 1;
    else if (player.x < game.critters[critter_id].x) newx = (game.critters[critter_id].x) - 1;
    else newx = game.critters[critter_id].x;
    if (player.y > game.critters[critter_id].y) newy = (game.critters[critter_id].y) + 1;
    else if (player.y < game.critters[critter_id].y) newy = (game.critters[critter_id].y) - 1;
    else newy = game.critters[critter_id].y;
    
    if (!check_solid(newx,newy,level_id)){
        game.critters[critter_id].x = newx;
        game.critters[critter_id].y = newy;
    }
    return 0;
}

int move_critters(int level_id) {
    for (int i=0;i<game.critter_index;i++) {
        if (i != PLAYER_CRITTER) {
            if (game.critters[i].level_id == level_id) {
                if (distance_between_critters(i,PLAYER_CRITTER) < 2) attack_critter(i,PLAYER_CRITTER);
                else if (distance_between_critters(i,PLAYER_CRITTER) < 10) chase_move(i,level_id);
                else confused_move(i,level_id);
            }
        }
    }
    
    return 0;
}

#define AFTERLIFE -1

int admit_to_afterlife() {
    for (int i=0;i<game.critter_index;i++) {
        if (game.critters[i].hp <= 0 && game.critters[i].level_id != AFTERLIFE) {
            game.critters[i].level_id = AFTERLIFE;
            char temp[80], lol[40];
            get_critter_name(lol,i);
            snprintf(temp,80,"The %s is admitted to the afterlife!",lol);
            add_status_msg(temp);
        }
    }
    return 0;
}

int give_level_ups() {
    for (int i=0;i<game.critter_index;i++) {
        if (game.critters[i].xp >= 100) {
                game.critters[i].xp = 0;
                game.critters[i].hit_dice++;
                // placeholder stat gainz
                game.critters[i].atk += 10;
                game.critters[i].def += 10;
                game.critters[i].arm += 10;
                game.critters[i].dmg += 10;
                game.critters[i].hp += 10;
                game.critters[i].maxhp += 10;
                game.critters[i].sp += 10;
                game.critters[i].maxsp += 10;
                char temp[80];
                snprintf(temp,80,"Welcome to level %d.",player.hit_dice);
                add_status_msg(temp);
        }
    }
    return 0;
}

int advance_turn() {
    // let's not have dead people do stuff (unless they're undead)
    admit_to_afterlife();
    // level up those still alive and at the threshold
    give_level_ups();
    
    move_critters(player.level_id);
    
    // placeholder, spawns infinite critters
    if (game.turns % 3 == 0) {
        if (game.critter_index < MAX_CRITTERS) {
                game.critters[game.critter_index] = TEMPLATES[CRITTER_HUMAN];
                game.critters[game.critter_index].x = rand()%MAP_MAXX;
                game.critters[game.critter_index].y = rand()%MAP_MAXY;
                game.critters[game.critter_index].level_id = 0;
                game.critters[game.critter_index].flags[0] = CRITTER_FLAG_ZOMBIE;
                game.critter_index++;
        }
    }
    
    game.turns++;
    if (player.hp < 1) return STATE_GAME_OVER;
    return STATE_GAME_CONTINUES;
}
