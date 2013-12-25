#include "header.h"
#include "globals.h"

void dig_corridor (int level_id, int x0, int y0, int x1, int y1) {
    // sanity check
    if (x0 == x1 && y0 == y1) return; // whew, that was easy!
    // TODO: maybe vary the order of horizontal/vertical digging? not a big bother
    // horizontal
    // first go from x0,y0 to x1,y0
    bool hitwall = false, hitroom = false;
    for (int i=minimum(x0,x1);i<=maximum(x1,x0);i++) {
        if (game.levels[level_id].tiles[i][y0].tile_id == TILE_WALL_SIMPLE && !hitwall) {
            game.levels[level_id].tiles[i][y0] = TILES[TILE_DOOR_LOCKED];
            hitwall = true;
            hitroom = false;
        } else if (game.levels[level_id].tiles[i][y0].tile_id == TILE_FLOOR && hitwall && !hitroom) {
            game.levels[level_id].tiles[i-1][y0] = TILES[TILE_DOOR_LOCKED];
            if (!(game.levels[level_id].tiles[i][y0].tile_id == TILE_DOOR_LOCKED))
                game.levels[level_id].tiles[i][y0] = TILES[TILE_FLOOR];
            hitroom = true;
            hitwall = false;
        } else {
            if (!(game.levels[level_id].tiles[i][y0].tile_id == TILE_DOOR_LOCKED))
                game.levels[level_id].tiles[i][y0] = TILES[TILE_FLOOR];
        }
    }
    // vertical
    // then go from x1,y0 to x1,y1
    hitwall = false; hitroom = false;
    for (int i=minimum(y0,y1);i<=maximum(y1,y0);i++) {
        if (game.levels[level_id].tiles[x1][i].tile_id == TILE_WALL_SIMPLE && !hitwall) {
            game.levels[level_id].tiles[x1][i] = TILES[TILE_DOOR_LOCKED];
            hitwall = true;
            hitroom = false;
        } else if (game.levels[level_id].tiles[x1][i].tile_id == TILE_FLOOR && hitwall && !hitroom) {
            game.levels[level_id].tiles[x1][i-1] = TILES[TILE_DOOR_LOCKED];
            if (!(game.levels[level_id].tiles[x1][i].tile_id == TILE_DOOR_LOCKED))
                game.levels[level_id].tiles[x1][i] = TILES[TILE_FLOOR];
            hitroom = true;
            hitwall = false;
        } else {
            if (!(game.levels[level_id].tiles[x1][i].tile_id == TILE_DOOR_LOCKED))
                game.levels[level_id].tiles[x1][i] = TILES[TILE_FLOOR];
        }
    }
}

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
        //if  (i == ((ry+ry+rom_size)/2)) game.levels[0].tiles[rx+rom_size][i] = TILES[TILE_FLOOR];
    }
    // first level can stay static - for now
    // others can be generated
    
    int first_level_exit_x = 11;
    int first_level_exit_y = 11;
    
    game.levels[0].tiles[first_level_exit_x][first_level_exit_y] = TILES[TILE_EXIT];
    game.levels[0].tiles[first_level_exit_x][first_level_exit_y].exit.destination_level = 1;
    game.levels[0].tiles[first_level_exit_x][first_level_exit_y].exit.x = 0; // this will get
    game.levels[0].tiles[first_level_exit_x][first_level_exit_y].exit.y = 21; // overwritten 
    
    // main generation loop
    int last_exit_x = 0, last_exit_y = 0;
    Point rooms[20]; // list of room centers, I don't need to know their sizes much
    // starting at 1 because 0 is the starting level
    for (int curlev=1;curlev<MAX_LEVELS;curlev++) {
        // fill level with walls
        // mi, mj - map coords
        for (int mi=0;mi<MAP_MAXX;mi++){
            for (int mj=0;mj<MAP_MAXY;mj++) {
                game.levels[curlev].tiles[mi][mj] = TILES[TILE_WALL_SIMPLE];
            }
        }
        // before exits, do terrain
        int room_size_x, room_size_y; // sizes FROM THE 'CENTER'
        // room generation
        for (int room=0;room<20;room++) {
            rooms[room].x = (rand()%(MAP_MAXX-3))+2; // no rooms that appear too near the border
            rooms[room].y = (rand()%(MAP_MAXY-3))+2;
            room_size_x = rand()%3 +1; // 'radii'
            room_size_y = rand()%3 +1;
            // drill rooms in the rock
            for (int mi=rooms[room].x-room_size_x;mi<rooms[room].x+room_size_x;mi++) {
                for (int mj=rooms[room].y-room_size_y;mj<rooms[room].y+room_size_y;mj++) {
                    game.levels[curlev].tiles[mi][mj] = TILES[TILE_FLOOR];
                }
            }
        }
        // insert corridors between rooms
        // mandatory corridors (placeholder?) 0-10-19 to guarantee navigableness
        dig_corridor(curlev,rooms[0].x,rooms[0].y,rooms[10].x,rooms[10].y);
        dig_corridor(curlev,rooms[10].x,rooms[10].y,rooms[19].x,rooms[19].y);
        int roll = rand()%10;
        int room1, room2;
        // more random corridors
        for (int i=0;i<roll;i++) {
            room1 = rand()%20; room2 = rand()%20;
            dig_corridor(curlev,rooms[room1].x,rooms[room1].y,rooms[room2].x,rooms[room2].y);
        }
        // slap a border around the whole thing
        for (int mi=0;mi<MAP_MAXX;mi++){
            if (mi == 0 || mi == MAP_MAXX-1) {
                for (int mj=0;mj<MAP_MAXY;mj++)
                    game.levels[curlev].tiles[mi][mj] = TILES[TILE_WALL_SIMPLE];
            } //else {
                game.levels[curlev].tiles[mi][0] = TILES[TILE_WALL_SIMPLE];                
                game.levels[curlev].tiles[mi][MAP_MAXY-1] = TILES[TILE_WALL_SIMPLE];            
            //}
        }
        // if it's the first room, place entrance there
        // NON-randomly placed entrance (where you get it and can go back)
        int entrance_x = rooms[0].x;
        int entrance_y = rooms[0].y;
        game.levels[curlev].tiles[entrance_x][entrance_y] = TILES[TILE_ENTRANCE];
        game.levels[curlev].tiles[entrance_x][entrance_y].exit.destination_level = curlev-1;
        // special case for first generated level
        if (curlev == 1) {
            last_exit_x = first_level_exit_x;
            last_exit_y = first_level_exit_y;
        }
        // this defaults to 0, but should take the former iteration's exit's x and y
        game.levels[curlev].tiles[entrance_x][entrance_y].exit.x = last_exit_x;
        game.levels[curlev].tiles[entrance_x][entrance_y].exit.y = last_exit_y;
        // and to make the last exit point to the entrance
        game.levels[curlev-1].tiles[last_exit_x][last_exit_y].exit.x = entrance_x;
        game.levels[curlev-1].tiles[last_exit_x][last_exit_y].exit.y = entrance_y;
        // if it's the last room, place exit there
        // randomly placed exit
        // must be different from entrance
        int exit_x;
        int exit_y;
        exit_x = rooms[19].x; 
        exit_y = rooms[19].y;
        // storing values
        last_exit_x = exit_x;
        last_exit_y = exit_y;
        // making a placeholder exit (if not out of bounds)
        if (curlev < MAX_LEVELS) {
            game.levels[curlev].tiles[exit_x][exit_y] = TILES[TILE_EXIT];
            game.levels[curlev].tiles[exit_x][exit_y].exit.destination_level = curlev+1;
        }
    }
    
    // generate critters
    for (int curlev=1;curlev<MAX_LEVELS;curlev++) {
        for (int i=0;i<=curlev;i++) {
            int roll=rand()%4+1;
            for (int j=0;j<roll;j++)
                generate_critters(curlev);
        }
    }

    return 0;
}

int generate_critters(int level_id) {
    // this is a placeholder OF COURSE
    if (game.critter_index < MAX_CRITTERS) {
                game.critters[game.critter_index] = game.CRITTER_TEMPLATES[rand()%255];
                int critter_x;
                int critter_y;
                do {
                    critter_x = (rand()%MAP_MAXX-2)+1;
                    critter_y = (rand()%MAP_MAXX-2)+1;
                } while (game.levels[level_id].tiles[critter_x][critter_y].blocks); // this might hang in rare cases
                game.critters[game.critter_index].x = critter_x;
                game.critters[game.critter_index].y = critter_y;
                game.critters[game.critter_index].level_id = level_id;
                // according to level, give some level-ups
                int roll = rand()%level_id;
                for (int i=0;i<roll;i++)
                    level_up_critter(game.critter_index);
                game.critter_index++;
    }
    
    
    
    return 0;
}
