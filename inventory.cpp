#include "header.h"
#include "globals.h"

int equip_item(int critter_id, int inventory_id, int slot_id) {
    game.critters[critter_id].slots[slot_id] = inventory_id;
    return 0;
}

int remove_item(int critter_id, int slot_id) {
    game.critters[critter_id].slots[slot_id] = ITEM_NONE_EQUIPPED;
    return 0;
}

#define INVENTORY_VIEW 0
#define INVENTORY_USE 1
#define INVENTORY_EQUIP 2
#define INVENTORY_SELECT_EQUIP 3
#define INVENTORY_DROP 4

int show_inventory() {
    int mode = INVENTORY_VIEW;
    int selected_slot = 0;
    int selected_list = 0;
    bool done = false;
    char temp[80];
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
                    if (event.key.keysym.sym == SDLK_e) {
                        // equip
                        mode = INVENTORY_EQUIP;
                        
                    }
                    if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_UP ||
                        event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT) {
                        if (mode == INVENTORY_EQUIP) {
                            if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_RIGHT) {
                                selected_slot++;
                                if (selected_slot >= ITEM_SLOTS) selected_slot = 0;
                            }
                            if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_UP) {
                                selected_slot--;
                                if (selected_slot < 0) selected_slot = ITEM_SLOTS-1;
                            }   
                        }
                        if (mode == INVENTORY_SELECT_EQUIP || mode == INVENTORY_DROP) {
                            if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_RIGHT) {
                                selected_list++;
                                if (selected_list >= INVENTORY_SIZE) selected_list = 0;
                            }
                            if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_UP) {
                                selected_list--;
                                if (selected_list < 0) selected_list = INVENTORY_SIZE-1;
                            }   
                        }
                    }
                    if (event.key.keysym.sym == SDLK_a) {
                        // apply/use
                        mode = INVENTORY_USE;
                    }
                    if (event.key.keysym.sym == SDLK_d) {
                        // drop 
                        mode = INVENTORY_DROP;
                    }
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        if (mode == INVENTORY_EQUIP) mode = INVENTORY_SELECT_EQUIP;
                        else if (mode == INVENTORY_SELECT_EQUIP) {
                            bool conflict = false;
                            for (int i=0;i<ITEM_SLOTS;i++) 
                                if (selected_list == player.slots[i]) conflict = true;
                            if (!conflict && strcmp(player.inventory[selected_list].name,"Nothing") != 0) player.slots[selected_slot] = selected_list;
                        }
                        else if (mode == INVENTORY_DROP) {
                            if (strcmp(player.inventory[selected_list].name,"Nothing") !=0) {
                                char temp[80];
                                snprintf(temp,80,"You drop the %s.",player.inventory[selected_list].name);
                                add_status_msg(temp);
                                game.items[game.item_index] = player.inventory[selected_list];
                                game.items[game.item_index].x = player.x;
                                game.items[game.item_index].y = player.y;
                                game.items[game.item_index].level_id = player.level_id;
                                game.item_index++;
                                player.inventory[selected_list] = game.ITEM_TEMPLATES[0]; // Nothing
                                for (int i=0;i<ITEM_SLOTS;i++) {
                                    if (player.slots[i] == selected_list) player.slots[i] = ITEM_NONE_EQUIPPED;
                                }
                                
                            }
                        }
                    }
                    if (event.key.keysym.sym == SDLK_BACKSPACE) {
                        if (mode == INVENTORY_EQUIP || mode == INVENTORY_SELECT_EQUIP) player.slots[selected_slot] = ITEM_NONE_EQUIPPED;
                    }
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        if (mode == INVENTORY_VIEW) return STATE_MAPMODE;
                        else if (mode == INVENTORY_SELECT_EQUIP) mode = INVENTORY_EQUIP;
                        else mode = INVENTORY_VIEW;
                    }
                    break;
                }
            } // end switch
        } // end of message processing
        
        clear_screen();
        
        put_text(4,3,"Equipped:");
        
        for (int i=0;i<ITEM_SLOTS;i++) {
            if (player.slots[i] != ITEM_NONE_EQUIPPED) {
                snprintf(temp,80,"%s",player.inventory[player.slots[i]].name);
            } else {
                snprintf(temp,80,"Nothing");
            }
            if (mode == INVENTORY_EQUIP && selected_slot == i) {
                put_text(5+i*12,5,temp,COLORS[COLOR_DEFAULT_BG],COLORS[COLOR_DEFAULT_FG]);
            } else {
                put_text(5+i*12,5,temp);
            }
        }
        
        put_text(4,8,"Carried:");
        
        int equipped;
        SDL_Color fg, bg;
        for (int i=0;i<INVENTORY_SIZE;i++) {
            if (i == selected_list && ( mode == INVENTORY_SELECT_EQUIP || mode == INVENTORY_DROP)) {
                fg = COLORS[COLOR_DEFAULT_BG];
                bg = COLORS[COLOR_DEFAULT_FG];
            } else {
                fg = COLORS[COLOR_DEFAULT_FG];
                bg = COLORS[COLOR_DEFAULT_BG];
            }
            equipped = -1;
            for (int j=0;j<ITEM_SLOTS;j++) {
                if (player.slots[j] == i) {
                    equipped = j;
                }
            }
            if (equipped != ITEM_NONE_EQUIPPED) {
                snprintf(temp,80,"%d - %s (slot %d)",i+1,player.inventory[i].name,equipped+1);
                put_text(5,10+i,temp,fg,bg);
            } else {
                snprintf(temp,80,"%d - %s",i+1,player.inventory[i].name);
                put_text(5,10+i,temp,fg,bg);
            }
        }
        
        // space on right reserved for item stats
        if (mode == INVENTORY_SELECT_EQUIP || mode == INVENTORY_USE || mode == INVENTORY_DROP) {
            if (strcmp(player.inventory[selected_list].name,"Nothing") != 0) {
                snprintf(temp,80,"ATK: %d",player.inventory[selected_list].atk);
                put_text(30,10,temp);
                snprintf(temp,80,"DEF: %d",player.inventory[selected_list].def);
                put_text(30,11,temp);
                snprintf(temp,80,"DMG: %d",player.inventory[selected_list].dmg);
                put_text(30,12,temp);
                snprintf(temp,80,"ARM: %d",player.inventory[selected_list].arm);
                put_text(30,13,temp);
            }
        } else if (mode == INVENTORY_EQUIP) {
            if (player.slots[selected_slot] != ITEM_NONE_EQUIPPED) {
                snprintf(temp,80,"ATK: %d",player.inventory[player.slots[selected_slot]].atk);
                put_text(30,10,temp);
                snprintf(temp,80,"DEF: %d",player.inventory[player.slots[selected_slot]].def);
                put_text(30,11,temp);
                snprintf(temp,80,"DMG: %d",player.inventory[player.slots[selected_slot]].dmg);
                put_text(30,12,temp);
                snprintf(temp,80,"ARM: %d",player.inventory[player.slots[selected_slot]].arm);
                put_text(30,13,temp);
            }
        }
        
        put_text(4,31,"E to equip mode, arrow keys select, Enter implements.", COLORS[COLOR_HELPTEXT],COLORS[COLOR_DEFAULT_BG]);
        put_text(4,32,"Backspace in equip mode unequips.", COLORS[COLOR_HELPTEXT],COLORS[COLOR_DEFAULT_BG]);
        put_text(4,33,"A to use mode, arrow keys select, Enter implements.", COLORS[COLOR_HELPTEXT],COLORS[COLOR_DEFAULT_BG]);
        put_text(4,34,"D to drop mode, arrow keys select, Enter implements.", COLORS[COLOR_HELPTEXT],COLORS[COLOR_DEFAULT_BG]);
        put_text(4,35,"Escape goes back one step, or exits inventory in normal mode.", COLORS[COLOR_HELPTEXT],COLORS[COLOR_DEFAULT_BG]);
        
        SDL_Flip(MAIN_SCREEN);
        SDL_Delay(10); // manipulate at will
  
    }
    return STATE_MAPMODE;
}
