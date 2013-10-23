#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#define COLOR_WHITE 0
#define COLOR_BLACK 1
#define COLOR_RED 2
#define COLOR_GREEN 3
#define COLOR_BLUE 4
#define COLOR_YELLOW 5
#define COLOR_DEFAULT_FG 0
#define COLOR_DEFAULT_BG 1
#define COLOR_HELPTEXT 3

#define NAME_MAX_CRITTER 16
#define NAME_MAX_ITEM 16

#define MAX_ITEMS 255*255

typedef struct Item {
    char name[80];
    int atk;
    int def;
    int dmg;
    int arm;
    // for free-lying items, unused when wielded/inventoried
    int x;
    int y;
    int level_id;
    char visual;
} Item;

#define SEX_MALE 0
#define SEX_FEMALE 1
#define SEX_NEUTER 2

#define MAX_CRITTERS 255*255

#define CRITTER_HUMAN 0

#define INVENTORY_SIZE 20
#define ITEM_SLOTS 4
#define ITEM_NONE_EQUIPPED -1

#define CRITTER_FLAGS 1
#define CRITTER_FLAG_ZOMBIE 1

typedef struct Critter {
    char name[16];
    int sex;
    int x, y; // coords on level
    int level_id; // which level is it on
    char visual;
    SDL_Color color;
    // game stats
    int hit_dice;
    int hp; int maxhp;
    int sp; int maxsp;
    int atk;
    int def;
    int dmg;
    int arm;
    int xp; // 100 xp for every level?
    int flags[CRITTER_FLAGS]; // special flags, like zombie
    // end game stats
    Item inventory[INVENTORY_SIZE];
    // item slots
    int slots[ITEM_SLOTS];
} Critter;

typedef struct Exit {
    int destination_level;
    int x;
    int y;
} Exit;

#define TILE_FLOOR 0
#define TILE_WALL_VERTICAL 1
#define TILE_WALL_HORIZONTAL 2
#define TILE_DOOR_OPEN 3
#define TILE_DOOR_LOCKED 4
#define TILE_EXIT 5

#define EXIT_TO_NOWHERE -1

typedef struct Tile {
    int tile_id;
    char visual; // what it looks like
    SDL_Color fg; // foreground color
    SDL_Color bg; // background color
    bool blocks; // whether it blocks movement
    Exit exit; // where it moves you
    char name[80]; 
} Tile;

typedef struct Level { // don't want conflicts with 'map'
    Tile tiles[MAP_MAXX][MAP_MAXY];
} Level;

#define PLAYER_CRITTER 0
#define player game.critters[0]
// don't name anything in the code "player", srsly
#define MAX_STATUS_MESSAGES 30
#define MAX_STATUS_MESSAGE_LENGTH 255

typedef struct Game {
    unsigned long int turns;
    Level levels[255]; // for the moment
    Critter critters[MAX_CRITTERS]; // might be sufficient
    int critter_index; 
    Item items[MAX_ITEMS];
    int item_index;
    char status_msgs[MAX_STATUS_MESSAGES][MAX_STATUS_MESSAGE_LENGTH];
} Game;

#endif // STRUCTS_H_INCLUDED
