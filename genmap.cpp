#include "header.h"
#include "globals.h"

int generate_maps () {
    for (int i=0;i<MAP_MAXX;i++){
        for (int j=0;j<MAP_MAXY;j++) {
            game.levels[0].tiles[i][j] = TILES[TILE_FLOOR];
        }
    }
    
    // let's try simple room generation!
    int rom_size = rand()%6+13; 
    int rx = rand()%6;
    int ry = rand()%6;
    
    for (int i=rx;i<=rx+rom_size;i++) {
        game.levels[0].tiles[i][ry] = TILES[TILE_WALL_HORIZONTAL];
        game.levels[0].tiles[i][ry+rom_size] = TILES[TILE_WALL_HORIZONTAL];
    }
    for (int i=ry+1;i<=ry+rom_size-1;i++) {
        game.levels[0].tiles[rx][i] = TILES[TILE_WALL_VERTICAL];
        game.levels[0].tiles[rx+rom_size][i] = TILES[TILE_WALL_VERTICAL];
        // door
        if  (i == ((ry+ry+rom_size)/2)) game.levels[0].tiles[rx+rom_size][i] = TILES[TILE_DOOR_LOCKED];
    }

    game.levels[0].tiles[MAP_MAXX-1][20] = TILES[TILE_EXIT];
    game.levels[0].tiles[MAP_MAXX-1][20].exit.destination_level = 1;
    game.levels[0].tiles[MAP_MAXX-1][20].exit.x = 0;
    game.levels[0].tiles[MAP_MAXX-1][20].exit.y = 21;
    game.levels[0].tiles[MAP_MAXX-1][21] = TILES[TILE_EXIT];
    game.levels[0].tiles[MAP_MAXX-1][21].exit.destination_level = 1;
    game.levels[0].tiles[MAP_MAXX-1][21].exit.x = 0;
    game.levels[0].tiles[MAP_MAXX-1][21].exit.y = 21;
    game.levels[0].tiles[MAP_MAXX-1][22] = TILES[TILE_EXIT];
    game.levels[0].tiles[MAP_MAXX-1][22].exit.destination_level = 1;
    game.levels[0].tiles[MAP_MAXX-1][22].exit.x = 0;
    game.levels[0].tiles[MAP_MAXX-1][22].exit.y = 21;
    
    for (int i=0;i<MAP_MAXX;i++){
        for (int j=0;j<MAP_MAXY;j++) {
            game.levels[1].tiles[i][j] = TILES[TILE_FLOOR];
        }
    }
    
    game.levels[1].tiles[0][20] = TILES[TILE_EXIT];
    game.levels[1].tiles[0][20].exit.destination_level = 0;
    game.levels[1].tiles[0][20].exit.x = MAP_MAXX-1;
    game.levels[1].tiles[0][20].exit.y = 21;
    game.levels[1].tiles[0][21] = TILES[TILE_EXIT];
    game.levels[1].tiles[0][21].exit.destination_level = 0;
    game.levels[1].tiles[0][21].exit.x = MAP_MAXX-1;
    game.levels[1].tiles[0][21].exit.y = 21;
    game.levels[1].tiles[0][22] = TILES[TILE_EXIT];
    game.levels[1].tiles[0][22].exit.destination_level = 0;
    game.levels[1].tiles[0][22].exit.x = MAP_MAXX-1;
    game.levels[1].tiles[0][22].exit.y = 21;

    return 0;
}

int generate_critters(int level_id) {
    // this is a placeholder
    //game.critters[game.critter_index] = TEMPLATES[CRITTER_HUMAN];
    //game.critters[game.critter_index].x = rand()%MAP_MAXX;
    //game.critters[game.critter_index].y = rand()%MAP_MAXY;
    //game.critters[game.critter_index].level_id = level_id;
    //game.critter_index++;
    
    return 0;
}
