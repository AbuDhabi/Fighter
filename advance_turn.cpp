#include "header.h"
#include "globals.h"

float d(int x0, int x1, int y0, int y1) {
    return sqrt(pow(x0 - x1,2) + pow(y0 - y1,2));
}

int minimum (int x1, int x2) {
    if (x1 <= x2) return x1;
    if (x2 <= x1) return x2;
    return 0; // wtf!
}

int maximum (int x1, int x2) {
    if (x1 <= x2) return x2;
    if (x2 <= x1) return x1;
    return 0; // wtf!
}

// this is a pathfinding function
// it is inefficient, slowing the game down with 20ish actors at the same time
// it thinks diagonals are the same as proper adjacents, and follows strange paths sometimes
// detects creatures and paths around them
// NOT EFFICIENT
Point babbys_first_pathfinder(int level_id, int x0, int y0, int x1, int y1) {
    Point output = {-1,-1}; // default, meanigless values
    int grid[MAP_MAXX][MAP_MAXY];
    
    // fill out the distance grid with default values
    for (int i=0;i<MAP_MAXX;i++) {
        for (int j=0;j<MAP_MAXY;j++) {
            grid[i][j] = 2550;
            if (game.levels[level_id].tiles[i][j].blocks) { // don't go through walls
                grid[i][j] = 10000;
            }
        }
    }
    for (int i=1;i<game.critter_index;i++) { // don't walk through critters, but player is OK
        if (game.critters[i].level_id == level_id) {
           //grid[game.critters[i].x][game.critters[i].y] = grid[game.critters[i].x][game.critters[i].y] + 10;
           grid[game.critters[i].x][game.critters[i].y] = 0xBEEF;
        }
    }
    // we start here
    grid[x0][y0] = 0;
    
    // now to calculate distances from the origin
    // iterate over the entire damn space, filling out +10 per step
    bool done = false;
    int counter = 0;
    int minval;
    while (!done) {
        done = true;
        counter++;
        for (int i=0;i<MAP_MAXX;i++) {
            for (int j=0;j<MAP_MAXY;j++) {
                if (grid[i][j] == 2550 && !(i == 0 || j == 0 || i == MAP_MAXX-1 || j == MAP_MAXY-1)) {
                    // +10 per step
                    minval = minimum(minimum(minimum(minimum(minimum(minimum(minimum(grid[i+1][j+1],grid[i+1][j]),grid[i+1][j-1]),
                                    grid[i][j+1]),grid[i][j-1]),
                                    grid[i-1][j+1]),grid[i-1][j]),grid[i-1][j-1])
                                   +10;
                    grid[i][j] = minval;
                    // hey, hey, don't change the 2550s!
                    if (grid[i][j] > 2550 && grid[i][j] < 10000) grid[i][j] = 2550;
                    done = false; // if there are any more unvisited (2550) blocks, continue
                }
            }
        }
        if (grid[x1][y1] != 2550) break; // found a path!
        if (counter > MAP_MAXX) return output; // can't find path (fast enough)
    }
    /*
    for (int i=0;i<MAP_MAXX;i++) {
        for (int j=0;j<MAP_MAXY;j++) {
                printf(" %d",grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    */
    // now to find our way back and report the step to be taken
    bool found = false;
    int curx = x1, cury = y1; // start in destination
    int lastx, lasty;
    int counter2 = 0;
    while (!found) {
        counter2++;
        if (counter2 > MAP_MAXX*MAP_MAXY) return output; // safety check, there oughtn't be any route as long
        lastx = curx;
        lasty = cury;
        if      (grid[curx+1][cury+1] < grid[curx][cury]) { curx++; cury++; }
        else if (grid[curx+1][cury] < grid[curx][cury])   { curx++;         }
        else if (grid[curx+1][cury-1] < grid[curx][cury]) { curx++; cury--; }
        else if (grid[curx][cury+1] < grid[curx][cury])   {         cury++; }
        else if (grid[curx][cury-1] < grid[curx][cury])   {         cury--; }
        else if (grid[curx-1][cury+1] < grid[curx][cury]) { curx--; cury++; }
        else if (grid[curx-1][cury] < grid[curx][cury])   { curx--;         }
        else if (grid[curx-1][cury-1] < grid[curx][cury]) { curx--; cury--; }
        // if we're at the starting point, output the previous block
        if (grid[curx][cury] == 0) {
            found = true;
            output.x = lastx;
            output.y = lasty;
            //char temp[80];
            //snprintf(temp,80,"Path found, going to (%d,%d).",lastx,lasty);
            //add_status_msg(temp);
        }
    }
    
    return output;
};

//1) Add the starting square (or node) to the open list.
//2) Repeat the following:
//    a) Look for the lowest F cost square on the open list. We refer to this as the current square.
//    b) Switch it to the closed list.
//    c) For each of the 8 squares adjacent to this current square …
//        -If it is not walkable or if it is on the closed list, ignore it. Otherwise do the following.           
//        -If it isn’t on the open list, add it to the open list. Make the current square the parent of this square. Record the F, G, and H costs of the square. 
//        -If it is on the open list already, check to see if this path to that square is better, using G cost as the measure. A lower G cost means that this is a better path. If so, change the parent of the square to the current square, and recalculate the G and F scores of the square. If you are keeping your open list sorted by F score, you may need to resort the list to account for the change.
//    d) Stop when you:
//        -Add the target square to the closed list, in which case the path has been found (see note below), or
//        -Fail to find the target square, and the open list is empty. In this case, there is no path.   
//3) Save the path. Working backwards from the target square, go from each square to its parent square until you reach the starting square. That is your path. 

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
    //int newx, newy;
    int critx, crity;
    critx = game.critters[critter_id].x;
    crity = game.critters[critter_id].y;
    
    Point move_here = babbys_first_pathfinder(level_id,critx,crity,player.x,player.y);
    if (move_here.x != -1 && move_here.y != -1 && !check_solid(move_here.x,move_here.y,level_id)) {
        game.critters[critter_id].x = move_here.x;
        game.critters[critter_id].y = move_here.y;
        return 0;
    }
    
    // welp, gotta be confused, pathing failed
    confused_move(critter_id,level_id);
    return 0;
}

int move_critters(int level_id) {
    for (int i=0;i<game.critter_index;i++) {
        if (i != PLAYER_CRITTER) {
            if (game.critters[i].level_id == level_id) {
                if (distance_between_critters(i,PLAYER_CRITTER) < 2) attack_critter(i,PLAYER_CRITTER); // placeholder for allegiance system
                else if (distance_between_critters(i,PLAYER_CRITTER) < 15) chase_move(i,level_id);
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
            snprintf(temp,80,"The %s is destroyed!",lol);
            add_status_msg(temp);
        }
    }
    return 0;
}

int level_up_critter(int critter_id) {
    game.critters[critter_id].xp = 0;
    game.critters[critter_id].hit_dice++;
    // placeholder stat gainz
    game.critters[critter_id].atk += game.critters[critter_id].atk / (game.critters[critter_id].hit_dice-1);
    game.critters[critter_id].def += game.critters[critter_id].def / (game.critters[critter_id].hit_dice-1);
    game.critters[critter_id].arm += game.critters[critter_id].arm / (game.critters[critter_id].hit_dice-1);
    game.critters[critter_id].dmg += game.critters[critter_id].dmg / (game.critters[critter_id].hit_dice-1);
    game.critters[critter_id].hp += game.critters[critter_id].hp / (game.critters[critter_id].hit_dice-1);
    game.critters[critter_id].maxhp += game.critters[critter_id].maxhp / (game.critters[critter_id].hit_dice-1);
    game.critters[critter_id].sp += game.critters[critter_id].sp / (game.critters[critter_id].hit_dice-1);
    game.critters[critter_id].maxsp += game.critters[critter_id].maxsp / (game.critters[critter_id].hit_dice-1);
    return 0;
}

int give_level_ups() {
    for (int i=0;i<game.critter_index;i++) {
        if (game.critters[i].xp >= 100) {
                level_up_critter(i);
                if (i == PLAYER_CRITTER) {
                    char temp[80];
                    snprintf(temp,80,"Welcome to level %d.",player.hit_dice);
                    add_status_msg(temp);
                }
        }
    }
    return 0;
}

int natural_healing() {
    for (int i=0;i<game.critter_index;i++) {
        if (game.turns % 10 < 2 && game.turns % 2 == i % 2) {
            if (game.critters[i].hp < game.critters[i].maxhp)
                game.critters[i].hp++;
        }
    }
    return 0;
}

int advance_turn() {
    // let's not have dead people do stuff (unless they're undead)
    admit_to_afterlife();
    // heal those who are wounded
    natural_healing();
    // level up those still alive and at the threshold
    give_level_ups();
    
    move_critters(player.level_id);
    
    // reveal map that the player can see
    reveal_los();
    
    game.turns++;
    if (player.hp < 1) return STATE_GAME_OVER;
    return STATE_GAME_CONTINUES;
}
