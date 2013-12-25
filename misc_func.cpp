#include "header.h"
#include "globals.h"

void colors_setup() {
    COLORS[COLOR_BLACK] = {0x00,0x00,0x00,0xFF};
    COLORS[COLOR_WHITE] = {0xFF,0xFF,0xFF,0xFF};
    COLORS[COLOR_BLUE] = {0x00,0x00,0xFF,0xFF};
    COLORS[COLOR_GREEN] = {0x00,0xFF,0x00,0xFF};
    COLORS[COLOR_RED] = {0xFF,0x00,0x00,0xFF};
    COLORS[COLOR_YELLOW] = {0xFF,0xFF,0x00,0xFF};
}

void clear_screen() {
    boxRGBA(MAIN_SCREEN,0,0,MAXX,MAXY,COLORS[COLOR_DEFAULT_BG].r,COLORS[COLOR_DEFAULT_BG].g,COLORS[COLOR_DEFAULT_BG].b,COLORS[COLOR_DEFAULT_BG].unused);
}

void tiles_setup() {
    Exit e;
    e.destination_level = EXIT_TO_NOWHERE;
    e.x = 1;
    e.y = 1;
    TILES[TILE_FLOOR].tile_id = TILE_FLOOR;
    snprintf(TILES[TILE_FLOOR].name,80,"Floor");
    TILES[TILE_FLOOR].blocks = false;
    TILES[TILE_FLOOR].visual = '.';
    TILES[TILE_FLOOR].fg = COLORS[COLOR_DEFAULT_FG];
    TILES[TILE_FLOOR].bg = COLORS[COLOR_DEFAULT_BG];
    TILES[TILE_FLOOR].exit = e;
    TILES[TILE_FLOOR].explored = false;
    TILES[TILE_FLOOR].transparent = true;
    TILES[TILE_WALL_HORIZONTAL].tile_id = TILE_WALL_HORIZONTAL;
    snprintf(TILES[TILE_WALL_HORIZONTAL].name,80,"Wall");
    TILES[TILE_WALL_HORIZONTAL].blocks = true;
    TILES[TILE_WALL_HORIZONTAL].visual = '-';
    TILES[TILE_WALL_HORIZONTAL].fg = COLORS[COLOR_DEFAULT_FG];
    TILES[TILE_WALL_HORIZONTAL].bg = COLORS[COLOR_DEFAULT_BG];
    TILES[TILE_WALL_HORIZONTAL].exit = e;
    TILES[TILE_WALL_HORIZONTAL].explored = false;
    TILES[TILE_WALL_HORIZONTAL].transparent = false;
    TILES[TILE_WALL_VERTICAL].tile_id = TILE_WALL_VERTICAL;
    snprintf(TILES[TILE_WALL_VERTICAL].name,80,"Wall");
    TILES[TILE_WALL_VERTICAL].blocks = true;
    TILES[TILE_WALL_VERTICAL].visual = '|';
    TILES[TILE_WALL_VERTICAL].fg = COLORS[COLOR_DEFAULT_FG];
    TILES[TILE_WALL_VERTICAL].bg = COLORS[COLOR_DEFAULT_BG];
    TILES[TILE_WALL_VERTICAL].exit = e;
    TILES[TILE_WALL_VERTICAL].explored = false;
    TILES[TILE_WALL_VERTICAL].transparent = false;
    TILES[TILE_DOOR_OPEN].tile_id = TILE_DOOR_OPEN;
    snprintf(TILES[TILE_DOOR_OPEN].name,80,"Door");
    TILES[TILE_DOOR_OPEN].blocks = false;
    TILES[TILE_DOOR_OPEN].visual = '+';
    TILES[TILE_DOOR_OPEN].fg = COLORS[COLOR_YELLOW];
    TILES[TILE_DOOR_OPEN].bg = COLORS[COLOR_DEFAULT_BG];
    TILES[TILE_DOOR_OPEN].exit = e;
    TILES[TILE_DOOR_OPEN].explored = false;
    TILES[TILE_DOOR_OPEN].transparent = true;
    TILES[TILE_DOOR_LOCKED].tile_id = TILE_DOOR_LOCKED;
    snprintf(TILES[TILE_DOOR_LOCKED].name,80,"Door");
    TILES[TILE_DOOR_LOCKED].blocks = true;
    TILES[TILE_DOOR_LOCKED].visual = '+';
    TILES[TILE_DOOR_LOCKED].fg = COLORS[COLOR_DEFAULT_BG];
    TILES[TILE_DOOR_LOCKED].bg = COLORS[COLOR_YELLOW];
    TILES[TILE_DOOR_LOCKED].exit = e;
    TILES[TILE_DOOR_LOCKED].explored = false;
    TILES[TILE_DOOR_LOCKED].transparent = false;
    TILES[TILE_EXIT].tile_id = TILE_EXIT;
    snprintf(TILES[TILE_EXIT].name,80,"Exit");
    TILES[TILE_EXIT].blocks = false;
    TILES[TILE_EXIT].visual = '>';
    TILES[TILE_EXIT].fg = COLORS[COLOR_DEFAULT_FG];
    TILES[TILE_EXIT].bg = COLORS[COLOR_DEFAULT_BG];
    TILES[TILE_EXIT].exit = e;
    TILES[TILE_EXIT].explored = false;
    TILES[TILE_EXIT].transparent = true;
    TILES[TILE_ENTRANCE].tile_id = TILE_ENTRANCE;
    snprintf(TILES[TILE_ENTRANCE].name,80,"Entrance");
    TILES[TILE_ENTRANCE].blocks = false;
    TILES[TILE_ENTRANCE].visual = '<';
    TILES[TILE_ENTRANCE].fg = COLORS[COLOR_DEFAULT_FG];
    TILES[TILE_ENTRANCE].bg = COLORS[COLOR_DEFAULT_BG];
    TILES[TILE_ENTRANCE].exit = e;
    TILES[TILE_ENTRANCE].explored = false;
    TILES[TILE_ENTRANCE].transparent = true;
    TILES[TILE_WALL_SIMPLE].tile_id = TILE_WALL_SIMPLE;
    snprintf(TILES[TILE_WALL_SIMPLE].name,80,"Wall");
    TILES[TILE_WALL_SIMPLE].blocks = true;
    TILES[TILE_WALL_SIMPLE].visual = ' ';
    TILES[TILE_WALL_SIMPLE].fg = COLORS[COLOR_DEFAULT_FG];
    TILES[TILE_WALL_SIMPLE].bg = COLORS[COLOR_DEFAULT_FG];
    TILES[TILE_WALL_SIMPLE].exit = e;
    TILES[TILE_WALL_SIMPLE].explored = false;
    TILES[TILE_WALL_SIMPLE].transparent = false;
}

void items_setup() {
    // work out some kind of system here, probably don't want to leave it numbers
    game.ITEM_TEMPLATES[0].arm = 0;
    game.ITEM_TEMPLATES[0].atk = 0;
    game.ITEM_TEMPLATES[0].def = 0;
    game.ITEM_TEMPLATES[0].dmg = 0;
    game.ITEM_TEMPLATES[0].level_id = -1; // afterlife for items?
    game.ITEM_TEMPLATES[0].x = 0;
    game.ITEM_TEMPLATES[0].y = 0;
    game.ITEM_TEMPLATES[0].visual = ' ';
    snprintf(game.ITEM_TEMPLATES[0].name,NAME_MAX_ITEM,"Nothing");
    game.ITEM_TEMPLATES[1].arm = 101;
    game.ITEM_TEMPLATES[1].atk = 101;
    game.ITEM_TEMPLATES[1].def = 101;
    game.ITEM_TEMPLATES[1].dmg = 101;
    game.ITEM_TEMPLATES[1].level_id = -1; // afterlife for items?
    game.ITEM_TEMPLATES[1].x = 0;
    game.ITEM_TEMPLATES[1].y = 0;
    game.ITEM_TEMPLATES[1].visual = '*';
    snprintf(game.ITEM_TEMPLATES[1].name,NAME_MAX_ITEM,"Paperweight");
    
    game.item_index = 0;
    for (int i=0;i<MAX_ITEMS;i++) {
        game.items[i] = game.ITEM_TEMPLATES[0]; 
    }
    //game.items[game.item_index] = game.ITEM_TEMPLATES[1];
    //game.items[game.item_index].x = 12;
    //game.items[game.item_index].y = 12;
    //game.items[game.item_index].level_id = 0;
    //game.item_index++;
    

}

void critters_setup() {
    // standard template for a level 1 human 
    game.CRITTER_TEMPLATES[CRITTER_HUMAN].color = COLORS[COLOR_DEFAULT_FG];
    snprintf(game.CRITTER_TEMPLATES[CRITTER_HUMAN].name,80,"Human");
    game.CRITTER_TEMPLATES[CRITTER_HUMAN].visual = '@';
    game.CRITTER_TEMPLATES[CRITTER_HUMAN].sex = SEX_MALE;
    game.CRITTER_TEMPLATES[CRITTER_HUMAN].x = 0;
    game.CRITTER_TEMPLATES[CRITTER_HUMAN].y = 0;
    game.CRITTER_TEMPLATES[CRITTER_HUMAN].hit_dice = 1;
    game.CRITTER_TEMPLATES[CRITTER_HUMAN].maxhp = game.CRITTER_TEMPLATES[CRITTER_HUMAN].hit_dice * 10;
    game.CRITTER_TEMPLATES[CRITTER_HUMAN].hp = game.CRITTER_TEMPLATES[CRITTER_HUMAN].maxhp;
    game.CRITTER_TEMPLATES[CRITTER_HUMAN].maxsp = game.CRITTER_TEMPLATES[CRITTER_HUMAN].hit_dice * 5;
    game.CRITTER_TEMPLATES[CRITTER_HUMAN].sp = game.CRITTER_TEMPLATES[CRITTER_HUMAN].maxsp;
    game.CRITTER_TEMPLATES[CRITTER_HUMAN].arm = 10;
    game.CRITTER_TEMPLATES[CRITTER_HUMAN].atk = 10;
    game.CRITTER_TEMPLATES[CRITTER_HUMAN].def = 10;
    game.CRITTER_TEMPLATES[CRITTER_HUMAN].dmg = 10;
    game.CRITTER_TEMPLATES[CRITTER_HUMAN].xp = 0;
    for (int i=0;i<CRITTER_FLAGS;i++) {
        game.CRITTER_TEMPLATES[CRITTER_HUMAN].flags[i] = 0;
    }
    // item setup
    game.CRITTER_TEMPLATES[CRITTER_HUMAN].inventory[0] = game.ITEM_TEMPLATES[1]; // paperweight
    for (int i=1;i<INVENTORY_SIZE;i++) {
        game.CRITTER_TEMPLATES[CRITTER_HUMAN].inventory[i] = game.ITEM_TEMPLATES[0]; // nothing
    }
    for (int i=0;i<ITEM_SLOTS;i++) {
        game.CRITTER_TEMPLATES[CRITTER_HUMAN].slots[i] = ITEM_NONE_EQUIPPED; // means no damn item there
    }
    
    // generate random critters!
    generate_critter_templates();
    
    // the player critter is there
    game.critter_index = 1;    
    // to avoid uninitialized
    for (int i=0;i<MAX_CRITTERS;i++) {
        game.critters[i] = game.CRITTER_TEMPLATES[CRITTER_HUMAN];
    }
}

bool is_a_critter_there(int x, int y, int map_id) {
    for (int i=0;i<game.critter_index;i++) {
        if (game.critters[i].x == x && game.critters[i].y == y && game.critters[i].level_id == map_id) return true;
    }
    return false;
}

bool check_solid(int x, int y, int map_id) {
    if (x < 0) return true; 
    if (x >= MAP_MAXX) return true;
    if (y < 0) return true;
    if (y >= MAP_MAXY) return true;
    // check creature collision
    if (is_a_critter_there(x,y,map_id)) return true;
    return game.levels[map_id].tiles[x][y].blocks; // true if solid, do not pass
}

int check_creature() {

    return 0; // should return a code concerning relationship with creature
}

void status_msg_setup() {
    for (int i=0;i<MAX_STATUS_MESSAGES;i++){
        game.status_msgs[i][0] = '\0';
    }
}

int new_game_setup() {
    player.level_id = 0; // starting
    colors_setup();
    tiles_setup();
    items_setup();
    critters_setup();
    //generate_critters(0); // moved to generate_maps()
    status_msg_setup();
    
    
    return 0;
}
