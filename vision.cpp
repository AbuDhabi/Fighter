#include "header.h"
#include "globals.h"

// determines if a critter can view given coordinates
bool in_line_of_sight(int critter_id, int level_id, int x, int y) {
    int critter_x = game.critters[critter_id].x;
    int critter_y = game.critters[critter_id].y;
    int critter_level = game.critters[critter_id].level_id; // not its hit dice
    // obvious fail condition
    if (level_id != critter_level) return false;
    // bresenham setup
    int x0, x1, y0, y1;
    x0 = critter_x; x1 = x;
    y0 = critter_y; y1 = y;
    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
    int err = (dx>dy ? dx : -dy)/2, e2;
    // bresenham loop
    for(;;){
        // check if something blocks vision
        if (x0==x1 && y0==y1) return true; // can see, even if final tile is non-transparent
        if (!(game.levels[level_id].tiles[x0][y0].transparent)) break; // can't see
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }

    return false; // default
}

int distance_between_tiles(int x0, int x1, int y0, int y1) {
    // assumes same level
    return sqrt(pow(x0 - x1,2) + pow(y0 - y1,2));
}

// reveals all the player critter can currently see, use in turn determination
void reveal_los() {
    for (int i=0;i<MAP_MAXX;i++) {
        for (int j=0;j<MAP_MAXY;j++) {
            // can see? reveal
            if (distance_between_tiles(player.x,i,player.y,j) < 10) 
                if (in_line_of_sight(PLAYER_CRITTER,player.level_id,i,j)) {
                    game.levels[player.level_id].tiles[i][j].explored = true;
            }
        }
    }
}
