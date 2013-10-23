#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#define MAP_MAXX 64
#define MAP_MAXY 36 // ugh, silly

#define STATE_INITIAL 0
#define STATE_CHARGEN 1
#define STATE_MAPMODE 2
#define STATE_TITLE 3
#define STATE_AFTER_CHARGEN 4
#define STATE_GENERATE_WORLD 5
#define STATE_INVENTORY 6
#define STATE_GAME_OVER 7
#define STATE_GAME_CONTINUES 8
#define STATE_MESSAGE_LOG 9
#define STATE_HELP_MAPMODE 10
#define STATE_EXIT 255

#ifdef __cplusplus
    #include <cstdlib>
    #include <stdlib.h>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_getenv.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>
#else
#ifdef __MINGW32__
#include <SDL/SDL.h>
#include <SDL_getenv.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_gfxPrimitives.h>
#else
#include <SDL/SDL.h>
#include <SDL/SDL_getenv.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>
#endif
#endif

#include <cstring>
#include <time.h>
#include <math.h>

#include "structs.h"

bool load_media();
bool clean_up();
int put_text(int x, int y, const char *text);
void clear_screen();
int intro();
int chargen();
int after_chargen();
int generate_maps ();
int mapmode();
void tiles_setup();
int print_tile(int x, int y, Tile tile);
void colors_setup();
void critters_setup();
void items_setup();
int generate_critters(int level_id);
int advance_turn();
bool check_solid(int x, int y, int map_id);
int put_text(int x, int y, const char *text, SDL_Color fg, SDL_Color bg);
int new_game_setup();
bool is_a_critter_there(int x, int y, int map_id);
int add_status_msg(const char * text);
int attack_critter(int attacker, int defender);
int title_screen();
int show_inventory();
int get_atk(int critter_id);
int get_def(int critter_id);
int get_arm(int critter_id);
int get_dmg(int critter_id);
int get_critter_name(char * output, int critter_id);
int game_over();
int print_text_cutscene(const char* text);
int message_log();
int print_help_mapmode();

#endif // HEADER_H_INCLUDED
