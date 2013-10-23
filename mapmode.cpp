#include "header.h"
#include "globals.h"


int print_level(int level_id) {
    for (int i=0;i<MAP_MAXX;i++){
        for (int j=0;j<MAP_MAXY;j++) {
            //char temp[80];
            //snprintf(temp,80,"%c",game.levels[level_id].tiles[i][j].visual);
            //put_text(i,j,temp);
            print_tile(i,j,game.levels[level_id].tiles[i][j]);
        }
    }

    return 0;
}

int print_critters(int level_id) {
    // placeholder
    char temp[80];
    snprintf(temp,80,"%c",player.visual);
    put_text(player.x,player.y,temp,COLORS[COLOR_DEFAULT_BG],COLORS[COLOR_DEFAULT_FG]);
    
    for (int i=1;i<game.critter_index;i++) {
        if (game.critters[i].level_id == level_id) {
            snprintf(temp,80,"%c",game.critters[i].visual);
            put_text(game.critters[i].x,game.critters[i].y,temp);
        }
    }
    return 0;
}

int print_items(int level_id) {
    char temp[8];
    for (int i=0;i<MAX_ITEMS;i++){
        if (game.items[i].level_id == level_id) {
            snprintf(temp,8,"%c",game.items[i].visual);
            put_text(game.items[i].x,game.items[i].y,temp);
        }
    }

    return 0;
}

int print_stats() {
    char temp[80];
    snprintf(temp,80,"%s | HP:%d/%d SP:%d/%d | HD:%d XP:%d | ATK:%d DEF:%d DMG:%d ARM:%d",
             player.name,player.hp,player.maxhp,player.sp,player.maxsp,player.hit_dice,player.xp,
             get_atk(PLAYER_CRITTER),get_def(PLAYER_CRITTER), get_dmg(PLAYER_CRITTER), get_arm(PLAYER_CRITTER));
    put_text(1,MAP_MAXY,temp);
    return 0;
}

int print_messages() {
    char temp[MAX_STATUS_MESSAGE_LENGTH];
    snprintf(temp,MAX_STATUS_MESSAGE_LENGTH,"%s",game.status_msgs[0]);
    put_text(1,MAP_MAXY+1,temp);
    snprintf(temp,MAX_STATUS_MESSAGE_LENGTH,"%s",game.status_msgs[1]);
    put_text(1,MAP_MAXY+2,temp);
    return 0;
}

bool correct_player_coord_input() {
    bool corrected;
    if (player.x < 0) { player.x = 0; corrected = false; }
    if (player.x >= MAP_MAXX) { player.x = MAP_MAXX-1; corrected = false; }
    if (player.y < 0) { player.y = 0; corrected = false; }
    if (player.y >= MAP_MAXY) { player.y = MAP_MAXY-1; corrected = false; }
    return corrected; // if no corrections, true, else false
}

//bool is_locked_door(int x, int y, int map_id) {
//    if (game.levels[map_id].tiles[x][y].tile_id == TILE_DOOR_LOCKED) return true;
//    return false;
//}

bool is_it_this_tile(int x, int y, int map_id, int tile_id) {
    if (game.levels[map_id].tiles[x][y].tile_id == tile_id) return true;
    return false;
}

bool should_attack(int x, int y, int map_id) {
    for (int i=0;i<game.critter_index;i++) {
        // will attack any critter that's there
        // this is obviously not good, unless everything is hostile
        if (game.critters[i].x == x && game.critters[i].y == y && game.critters[i].level_id == map_id) return true;
    }
    return false;
}

int find_critter(int x, int y, int map_id) {
    for (int i=0;i<game.critter_index;i++) {
        if (game.critters[i].x == x && game.critters[i].y == y && game.critters[i].level_id == map_id) {
            return i;
        }
    }
    // if not found, -1
    return -1;
}

int attack_critter(int attacker, int defender) {
    // determine hit chance
    float tohitcalc;
    int hitchance;
    tohitcalc = (float)get_atk(attacker) / (1 + (float)get_atk(attacker) + (float)get_def(defender));
    hitchance = tohitcalc * 100.0;
    // roll to hit!
    int roll;
    roll = rand()%100 + 1; // fencepost?
    // resolve
    char temp[80];
    char defname[80], atkname[80];
    get_critter_name(atkname,attacker);
    get_critter_name(defname,defender);
    if (roll <= hitchance) {
        // hit!
        float dmgcalc = (float)get_dmg(attacker) / (1 + (float)get_dmg(attacker) + (float)get_arm(defender));
        roll = rand()%100 +1;
        int damage = dmgcalc * get_dmg(attacker) * roll / 100;
        game.critters[defender].hp -= damage; // deals 10 damnage
        game.critters[attacker].xp += 10 * game.critters[defender].hit_dice / game.critters[attacker].hit_dice; // xp gain, placeholder
        // blood! also placeholdery due to that 0
        if (damage > 0) game.levels[0].tiles[game.critters[defender].x][game.critters[defender].y].bg = COLORS[COLOR_RED];
        
        snprintf(temp,80,"%s hits the %s for %d damage (%d%%)!",atkname,defname,damage,hitchance);
        add_status_msg(temp);
    } else {
        // miss!
        snprintf(temp,80,"%s misses the %s (%d%%)!",atkname,defname,hitchance);
        add_status_msg(temp);
    }
    

    return 0;
}

int get_dir_x(SDLKey key) {
    if (key == SDLK_KP1) return -1;
    if (key == SDLK_KP2 || key == SDLK_DOWN) return 0;
    if (key == SDLK_KP3) return 1;
    if (key == SDLK_KP4 || key == SDLK_LEFT) return -1;
    if (key == SDLK_KP5 || key == SDLK_PERIOD) return 0;
    if (key == SDLK_KP6 || key == SDLK_RIGHT) return 1;
    if (key == SDLK_KP7) return -1;
    if (key == SDLK_KP8 || key == SDLK_UP) return 0;
    if (key == SDLK_KP9) return 1;
    return 0;
}

int get_dir_y(SDLKey key) {
    if (key == SDLK_KP1) return 1;
    if (key == SDLK_KP2 || key == SDLK_DOWN) return 1;
    if (key == SDLK_KP3) return 1;
    if (key == SDLK_KP4 || key == SDLK_LEFT) return 0;
    if (key == SDLK_KP5 || key == SDLK_PERIOD) return 0;
    if (key == SDLK_KP6 || key == SDLK_RIGHT) return 0;
    if (key == SDLK_KP7) return -1;
    if (key == SDLK_KP8 || key == SDLK_UP) return -1;
    if (key == SDLK_KP9) return -1;
    return 0;
}

bool is_move_key(SDLKey key) {
    if (key == SDLK_KP1) return true;
    if (key == SDLK_KP2 || key == SDLK_DOWN) return true;
    if (key == SDLK_KP3) return true;
    if (key == SDLK_KP4 || key == SDLK_LEFT) return true;
    //if (key == SDLK_KP5 || key == SDLK_PERIOD) return true; // corner case?
    if (key == SDLK_KP6 || key == SDLK_RIGHT) return true;
    if (key == SDLK_KP7) return true;
    if (key == SDLK_KP8 || key == SDLK_UP) return true;
    if (key == SDLK_KP9) return true;
    return false;
}

#define ACTION_NORMAL 0
#define ACTION_USE 1
#define ACTION_FIRE 2

int mapmode () {
    int action = ACTION_NORMAL;
    bool turn_over = false;
    int turn_result;
    bool done = false;
    SDLKey keypress;
    int newx, newy;
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
                    keypress = event.key.keysym.sym;
                    if (keypress == SDLK_RETURN) { 
                         
                    }
                    if (keypress == SDLK_ESCAPE) {  
                         return STATE_EXIT;
                    }
                    if (keypress == SDLK_PERIOD) {
                        turn_over = true;
                    }
                    if (keypress == SDLK_a) {
                        // this command lets you use something
                        // by using direction keys, select something on the map
                        // otherwise might use something from inventory (NIY)
                        action = ACTION_USE;
                    }
                    if (keypress == SDLK_i) {
                        // opens up inventory
                        //action = ACTION_INVENTORY;
                        return STATE_INVENTORY;
                    }
                    if (keypress == SDLK_BACKQUOTE) {
                        // opens message log
                        return STATE_MESSAGE_LOG;
                    }
                    if (keypress == SDLK_F1) {
                        // help file for mapmode
                        return STATE_HELP_MAPMODE;
                    }
                    if (keypress == SDLK_f) {
                        // shoots! this will need a direction
                        action = ACTION_FIRE;
                    }
                    if (keypress == SDLK_g) {
                        // get item from ground
                        int item_here = -1;
                        for (int i=0;i<MAX_ITEMS;i++) 
                            if (game.items[i].level_id == player.level_id && game.items[i].x == player.x && game.items[i].y == player.y)
                                item_here = i;
                        if (item_here != -1)
                            for (int i=0;i<INVENTORY_SIZE;i++) {
                                if (strcmp(player.inventory[i].name,"Nothing") == 0) {
                                        char temp[80];
                                        snprintf(temp,80,"You pick up the %s.",game.items[item_here].name);
                                        add_status_msg(temp);
                                        player.inventory[i] = game.items[item_here];
                                        game.items[item_here].level_id = -1;
                                        break;
                                }
                            }
                    }
                    if (keypress == SDLK_LSHIFT || keypress == SDLK_RSHIFT) {
                        // move to another area provided you are standing on an exit
                        if (game.levels[player.level_id].tiles[player.x][player.y].exit.destination_level != EXIT_TO_NOWHERE) {
                            int oldx, oldy, destx, desty;
                            oldx = player.x;
                            oldy = player.y;
                            destx = game.levels[player.level_id].tiles[player.x][player.y].exit.x;
                            desty = game.levels[player.level_id].tiles[player.x][player.y].exit.y;
                            player.x = destx;
                            player.y = desty;
                            player.level_id = game.levels[player.level_id].tiles[oldx][oldy].exit.destination_level;
                            turn_over = true;
                        }
                        
                    }
                    if (is_move_key(keypress)) {
                        newx = player.x + get_dir_x(keypress);
                        newy = player.y + get_dir_y(keypress);
                        if (action == ACTION_NORMAL) {
                            if (!check_solid(newx,newy,player.level_id)) {
                                player.x = newx;
                                player.y = newy;
                                turn_over = true;
                            } else if (should_attack(newx,newy,player.level_id)) {
                                attack_critter(PLAYER_CRITTER,find_critter(newx,newy,player.level_id));
                                turn_over = true;
                            }
                        } else if (action == ACTION_USE) {
                            if (is_it_this_tile(newx,newy,player.level_id,TILE_DOOR_LOCKED)) {
                                char temp[80];
                                snprintf(temp,80,"You open the %s.",game.levels[player.level_id].tiles[newx][newy].name);
                                add_status_msg(temp);
                                game.levels[player.level_id].tiles[newx][newy] = TILES[TILE_DOOR_OPEN];
                                action = ACTION_NORMAL;
                                turn_over = true;
                            } else if (is_it_this_tile(newx,newy,player.level_id,TILE_DOOR_OPEN)) {
                                char temp[80];
                                snprintf(temp,80,"You close the %s.",game.levels[player.level_id].tiles[newx][newy].name);
                                add_status_msg(temp);
                                game.levels[player.level_id].tiles[newx][newy] = TILES[TILE_DOOR_LOCKED];
                                action = ACTION_NORMAL;
                                turn_over = true;
                            } else {
                                action = ACTION_NORMAL; // you tried to do something weird
                            }
                        } else if (action == ACTION_FIRE) {
                            if (true) {
                                // detect if there's something on the line of fire
                                int firex, firey;
                                int critter_shot = -1;
                                for (int i=1;i<MAP_MAXX+MAP_MAXY;i++) { // why does max not work?
                                    firex = player.x + i*get_dir_x(keypress);
                                    firey = player.y + i*get_dir_y(keypress);
                                    if (firex >= MAP_MAXX || firex < 0) break;
                                    if (firey >= MAP_MAXY || firey < 0) break;
                                    if (should_attack(firex,firey,player.level_id)) {
                                        attack_critter(PLAYER_CRITTER,find_critter(firex,firey,player.level_id));
                                        critter_shot = 1; // this is a placeholder value
                                        break;
                                    }
                                }
                                if (critter_shot == -1) {
                                    // nothing in LOF
                                    char temp[80];
                                    snprintf(temp,80,"Your shot finds no target.");
                                    add_status_msg(temp);
                                }
                                turn_over = true;
                                action = ACTION_NORMAL;
                            } else {
                                action = ACTION_NORMAL; // you tried to do something weird
                            }
                        }
                    }
                    //correct_player_coord_input(); // this returns a bool
                    break;
                }
            } // end switch
        } // end of message processing
        
        clear_screen();
        
        if (turn_over) {
                turn_result = advance_turn();
                if (turn_result == STATE_GAME_OVER) return STATE_GAME_OVER;
                else if (turn_result == STATE_GAME_CONTINUES) { turn_over = false; }
        }
        print_level(player.level_id);
        print_items(player.level_id);
        print_critters(player.level_id);
        print_stats();
        print_messages();
        
        
        SDL_Flip(MAIN_SCREEN);
        SDL_Delay(10); // manipulate at will
  
    }

    return STATE_TITLE;
}
