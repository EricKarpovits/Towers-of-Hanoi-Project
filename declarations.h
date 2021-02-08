#ifndef DECLARATIONS_H_INCLUDED
#define DECLARATIONS_H_INCLUDED

// Libraries
#include <iostream>
#include <windows.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

using namespace std;

#include "string.h"

// Structs for buttons and screen positions for disks
struct SCREEN_POSITIONS {
    int xTopLeftCorner;
    int yTopLeftCorner;
};

struct BUTTON {
    int upperLeftXCoordinate, upperLeftYCoordinate, lowerRightXCoordinate, lowerRightYCoordinate;
    bool clicked;
    bool filled;
    string buttonTitle;
    bool largeText;
};

// Node struct
struct Node {
    int info;
    Node *next;
};

// All the gamemodes in 1 nice enclosure
enum GAMEMODE {
    MAIN_MENU,
    INSTRUCTIONS,
    CREDITS,
    START,
    SOLVE,
    RESET,
    PLAY
};

struct PEG {
    bool clicked;
    bool released;
    bool filled;
};

// Colours
#define BLUE        al_map_rgb(112,128,144)
#define WHITE       al_map_rgb(255, 255, 255)
#define BLACK       al_map_rgb(0, 0, 0)
#define ORANGE      al_map_rgb(255, 207, 158)
#define LIGHT_BLUE  al_map_rgb(153, 187, 255)
#define AMBER       al_map_rgb(255, 191, 0)
#define RED         al_map_rgb(255, 0, 0)
#define GREEN       al_map_rgb(0, 128, 0)

/// Constants
// Stack class constants
const int ONE_NODE = 1;

// Allegro constants
const int NUMBER_OF_MUSIC_SAMPLES = 2;
const int SCREEN_WIDTH = 1100;
const int SCREEN_HEIGHT = 700;
const int FPS = 60;
const int LARGE_FONT_SIZE = 25;
const int SMALL_FONT_SIZE = 18;

/// Button type - This was very crutial and I am glad I did it as it allowed me to keep track of what each button does
/// and so that I did not have remember what each button does
// In game buttons
const int BUTTON_INCREASE = 0;
const int BUTTON_DECREASE = 1;
const int BUTTON_SOLVE = 2;
const int BUTTON_RESET = 3;
const int BUTTON_MAIN_MENU = 4;
const int BUTTON_IN_GAME_QUIT = 5;

// Main menu buttons
const int BUTTON_START = 0;
const int BUTTON_INSTRUCTIONS = 1;
const int BUTTON_CREDITS = 2;
const int BUTTON_MAIN_MENU_QUIT = 3;

// Credits and instructions buttons
const int BUTTON_CREDITS_MAIN_MENU = 0;
const int BUTTON_CREDITS_START = 1;
const int BUTTON_CREDITS_QUIT = 2;

/// Hanoi constants
const int PEGS_COUNT = 3;
const int DISKS_COUNT = 10;
const int PEG_HEIGHT = 200;
const int NUMBER_OF_STARTING_DISKS = 3;

// Pegs
const int SOURCE = 0;
const int DESTINATION = 2;
const int INTERMEDIATE = 1;

/// Error code constants - allows for easier debugging and keeps program professional and allows the user to
/// to know what went wrong
const int ERROR_DISPLAY = -1;
const int ERROR_LOAD_BITMAP = -2;
const int ERROR_IMG_ADDON = -3;
const int ERROR_PRIMATIVE_ADDON = -4;
const int ERROR_MOUSE_ADDON = -5;
const int ERROR_FPSTIMER = -6;
const int ERROR_SOLVER_TIMER = -7;
const int ERROR_EVENT_QUEUE = -8;
const int ERROR_ARIAL_FONT = -9;
const int ERROR_SMALL_ARIAL_FONT = -10;
const int ERROR_FONT_ADDON = -11;
const int ERROR_TTF_ADDON = -12;
const int ERROR_ALLEGRO = -13;
const int ERROR_IMAGE_ADDON = -14;
const int ERROR_INSTALL_AUDIO = -15;
const int ERROR_ACODEC_ADDON = -16;
const int ERROR_MUSIC_FILE_GAMEMUSIC = -17;
const int ERROR_MUSIC_FILE_BUTTONCLICK = -18;

// Header files
#include "apvector.h"
#include "stack.h"
#include "allegro.h"
#include "consoleColor.h"
#include "gameManagement.h"

#endif // DECLARATIONS_H_INCLUDED
