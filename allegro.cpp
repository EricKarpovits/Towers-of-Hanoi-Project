#include "declarations.h"

// A method that releases the memory that was allocated for allegro
// This function exits everything for no memory loss
void Allegro::releaseMemory(){

    //Release the bitmap data and exit with no errors
	al_destroy_display(display);
	al_destroy_event_queue(eventQueue);
	al_destroy_font(arial);
	al_destroy_font(smallArial);
	al_destroy_sample(gameMusic);
	al_destroy_sample(buttonClick);
}

// This is the main method to display the disks
void Allegro::displayDisks(Stack peg[], PEG pegProperties[]) {

    // Declare the ap vectors for screen positions and the current peg values
    apvector<int> currentPegValues;
    apvector<SCREEN_POSITIONS> screenPositions;

    preparePegsForDrawing(pegProperties);

    // Draws each peg one by one - I did this as it is the most modular
    // approach which is efficent and does not have copy of the same code
    for (int i = 0; i < PEGS_COUNT; i++) {

        currentPegValues = peg[i].getAllValues();
        screenPositions = calculateScreenPositionsForDisks(currentPegValues, i);
        displayDisksForPeg(screenPositions, currentPegValues);
    }
}

// This method prepars the pegs so that they can be drawn on
void Allegro::preparePegsForDrawing(PEG pegProperties[]) {

    ALLEGRO_COLOR colour;

    for (int i = 1; i <= PEGS_COUNT; i++) {

        // Draw it red if mouse is hovering over
        if (pegProperties[i - 1].filled){
            colour = BLACK;
        } else {
            colour = WHITE;
        }
        al_draw_filled_rounded_rectangle((SCREEN_WIDTH / 4) * i - 5, PEG_HEIGHT, (SCREEN_WIDTH / 4) * i + 5, SCREEN_HEIGHT - 95, 7, 7, colour);
    }

    colour = WHITE;

    // Draw each peg and stand
    al_draw_filled_rounded_rectangle(50 , SCREEN_HEIGHT - 100, SCREEN_WIDTH - 50, SCREEN_HEIGHT - 75, 7, 7, colour);
}

// This method calculates the screen positions
apvector<SCREEN_POSITIONS> Allegro::calculateScreenPositionsForDisks(apvector<int> currentPegValues, int pegNumber) {

    // Declare variables
    int bitmapTotalWidth = 0;
    int bitmapCurrentHeight = 0;
    int bitmapPreviousHeight = SCREEN_HEIGHT - 100;
    int maxPegLength = currentPegValues.length();
    // An apvector of a struct for screen coordinates
    apvector<SCREEN_POSITIONS> screenPositions(maxPegLength);

    for (int i = maxPegLength - 1; i > -1; i--) {

        // Initialize variables
        int pegValue = currentPegValues[i];
        bitmapTotalWidth = al_get_bitmap_width(disk[pegValue]);
        bitmapCurrentHeight = al_get_bitmap_height(disk[pegValue]);
        bitmapPreviousHeight -= bitmapCurrentHeight;

        screenPositions[i].xTopLeftCorner = (((SCREEN_WIDTH / 4) * (pegNumber + 1)) - (bitmapTotalWidth / 2));
        screenPositions[i].yTopLeftCorner = bitmapPreviousHeight;
    }

    return screenPositions;
}

void Allegro::displayDisksForPeg(apvector<SCREEN_POSITIONS> screenPositions, apvector<int> currentPegValues) {

    int pegValue = 0;
    for (int i = 0; i < currentPegValues.length(); i++){
        pegValue = currentPegValues[i];
        al_draw_bitmap(disk[pegValue], screenPositions[i].xTopLeftCorner, screenPositions[i].yTopLeftCorner, 0);
    }
}

/// Buttons

// This function setups the buttons properies based on the game mode the user is in
void Allegro::buttonSetup() {

    // Switch the game mode so that the buttons are set up in the appropriate game mode
    switch (gameMode) {

        case RESET:
        case SOLVE:
        case START:
        case PLAY:

            // Set the vector size
            button.resize(6);
            // This modular method allows me to set all the button properties in 1 line for all types of button
            setButtonProperties(BUTTON_INCREASE, SCREEN_WIDTH / 8 * 5 - 60, SCREEN_HEIGHT - 60,
                                SCREEN_WIDTH / 8 * 5 + 90, SCREEN_HEIGHT - 15, false, "INCREASE");

            setButtonProperties(BUTTON_DECREASE, SCREEN_WIDTH / 8 * 3 - 90, SCREEN_HEIGHT - 60,
                                SCREEN_WIDTH / 8 * 3 + 60, SCREEN_HEIGHT - 15, false, "DECREASE");

            setButtonProperties(BUTTON_SOLVE, 50, 50, 200, 95, false, "SOLVE");
            setButtonProperties(BUTTON_RESET, 50, 120, 200, 165, false, "RESET");
            setButtonProperties(BUTTON_MAIN_MENU, SCREEN_WIDTH - 200, 50, SCREEN_WIDTH - 50, 95, false, "MAIN MENU");
            setButtonProperties(BUTTON_IN_GAME_QUIT, SCREEN_WIDTH - 200, 120, SCREEN_WIDTH - 50, 165, false, "QUIT");
            break;

        case MAIN_MENU:

            button.resize(4);
            setButtonProperties(BUTTON_START, SCREEN_WIDTH / 3, 150,
                                SCREEN_WIDTH / 3 * 2, 250, true, "START");
            setButtonProperties(BUTTON_INSTRUCTIONS, SCREEN_WIDTH / 3, 285,
                                SCREEN_WIDTH / 3 * 2, 385, true, "INSTRUCTIONS");
            setButtonProperties(BUTTON_CREDITS, SCREEN_WIDTH / 3, 420,
                                SCREEN_WIDTH / 3 * 2, 520, true, "CREDITS");
            setButtonProperties(BUTTON_MAIN_MENU_QUIT, SCREEN_WIDTH / 3, 555,
                                SCREEN_WIDTH / 3 * 2, 655, true, "QUIT");
            break;

        case INSTRUCTIONS:
        case CREDITS:

            button.resize(3);
            setButtonProperties(BUTTON_CREDITS_MAIN_MENU, SCREEN_WIDTH / 10 + 25, SCREEN_HEIGHT - 100,
                                (SCREEN_WIDTH / 10 * 3.2) + 25, SCREEN_HEIGHT - 25, true, "MAIN MENU");

            setButtonProperties(BUTTON_CREDITS_START, SCREEN_WIDTH / 10 + 325, SCREEN_HEIGHT - 100,
                                (SCREEN_WIDTH / 10 * 3.2) + 325, SCREEN_HEIGHT - 25, true, "START");

            setButtonProperties(BUTTON_CREDITS_QUIT, SCREEN_WIDTH / 10 + 625, SCREEN_HEIGHT - 100,
                                (SCREEN_WIDTH / 10 * 3.2) + 625, SCREEN_HEIGHT - 25, true, "QUIT");
            break;

    }

    // Reset the button booleans
    for (int i = 0; i < button.length(); i++) {
        button[i].clicked = false;
        button[i].filled = false;
    }
}

// This reusable function takes the properties from the button setup and allocates them to each specific button
// essentially a modifier method
void Allegro::setButtonProperties(int buttonNumber, int upperLeftX, int upperLeftY, int lowerRightX,
                                  int lowerRightY, bool largeText, string buttonTitle) {

	button[buttonNumber].upperLeftXCoordinate = upperLeftX;
	button[buttonNumber].upperLeftYCoordinate = upperLeftY;
	button[buttonNumber].lowerRightYCoordinate = lowerRightY;
	button[buttonNumber].lowerRightXCoordinate = lowerRightX;
	button[buttonNumber].largeText = largeText;
	button[buttonNumber].buttonTitle = buttonTitle;

}

/// This method draws the buttons
// The button is either drawn with just the outline or filled in, based on the users mouses position
void Allegro::drawButtons() {

    for (int i = 0; i < button.length(); i++) {

        // Based on if the bool is true or not either it draws the box filled or just the outline
        if (!button[i].filled) {

            al_draw_rectangle(button[i].upperLeftXCoordinate, button[i].upperLeftYCoordinate,
                              button[i].lowerRightXCoordinate, button[i].lowerRightYCoordinate, WHITE, 3);

        } else {

            al_draw_filled_rectangle(button[i].upperLeftXCoordinate, button[i].upperLeftYCoordinate,
                                    button[i].lowerRightXCoordinate, button[i].lowerRightYCoordinate, WHITE);
        }

        // Initialize the text font and size based on the buttons properties
        ALLEGRO_FONT *tempFont = NULL;
        int tempFontSize = 0;

        if (button[i].largeText) {
             tempFont = arial;
             tempFontSize = LARGE_FONT_SIZE;
        } else {
            tempFont = smallArial;
            tempFontSize = SMALL_FONT_SIZE;
        }

        // Draw out the button text - 1 line that does it for all buttons
        al_draw_text(tempFont, BLACK, (button[i].upperLeftXCoordinate + button[i].lowerRightXCoordinate) / 2,
                        (button[i].upperLeftYCoordinate + button[i].lowerRightYCoordinate) / 2 - (tempFontSize / 2),
                        ALLEGRO_ALIGN_CENTER, button[i].buttonTitle.c_str());
    }
}

// This function checks if the users mouse is hovering over the button and if the button was clicked
// Need to pass the button, the mouse coordinates, game mode, and the event type (as a bool clicked or not)
void Allegro::checkButtonAction(PEG pegProperties[]) {

    int mouseXCoordinate = event.mouse.x;
    int mouseYCoordinate = event.mouse.y;
    int eventType = event.type;

    for (int i = 0; i < button.length(); i++) {

        // Check the mouse is hovering over the button
        if (mouseXCoordinate >= button[i].upperLeftXCoordinate &&
            mouseXCoordinate <= button[i].lowerRightXCoordinate &&
            mouseYCoordinate >= button[i].upperLeftYCoordinate &&
            mouseYCoordinate <= button[i].lowerRightYCoordinate) {

            if (eventType == ALLEGRO_EVENT_MOUSE_AXES || (eventType == ALLEGRO_EVENT_MOUSE_BUTTON_UP && gameMode != SOLVE)) {
                button[i].filled = true;
            }

            if (eventType == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                button[i].clicked = true;
            }

        // If the mouse is not hovering over any buttons then the buttons will just be hallow
        } else if (eventType == ALLEGRO_EVENT_MOUSE_AXES) {

                button[i].filled = false;
        }
    }

    // Boundary around the peg so that the user can physically play
    for (int i = 0; i < PEGS_COUNT; i++) {

        if (mouseXCoordinate >= (SCREEN_WIDTH / 4 * (i + 1) - 100) &&
            mouseXCoordinate <= (SCREEN_WIDTH / 4 * (i + 1) + 100) &&
            mouseYCoordinate >= PEG_HEIGHT &&
            mouseYCoordinate <= (SCREEN_HEIGHT - 75) &&
            (gameMode == START || gameMode == PLAY)) {

            if (eventType == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                pegProperties[i].clicked = true;
            } else if (eventType == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                pegProperties[i].released = true;
            }

            pegProperties[i].filled = true;

        } else {
            pegProperties[i].filled = false;
        }
    }
}

/// This function converts which button was clicked to an the appropriate action (game mode or end the game)
void Allegro::checkButtonState(bool &continuePlaying, Stack peg[]) {

    GAMEMODE previousGamemode = gameMode;

    // Switch game mode
    switch (gameMode) {

        case MAIN_MENU:

            // Based on which button was clicked, the appropriate action is performed
            if (button[BUTTON_START].clicked) {
                gameMode = START;
            } else if (button[BUTTON_INSTRUCTIONS].clicked) {
                gameMode = INSTRUCTIONS;
            } else if (button[BUTTON_CREDITS].clicked) {
                gameMode = CREDITS;
            } else if (button[BUTTON_MAIN_MENU_QUIT].clicked) {
                // End the game
                continuePlaying = false;
            }
            break;

        case INSTRUCTIONS:
        case CREDITS:

            if (button[BUTTON_CREDITS_MAIN_MENU].clicked) {
                gameMode = MAIN_MENU;
            } else if (button[BUTTON_CREDITS_START].clicked) {
                gameMode = START;
            } else if (button[BUTTON_CREDITS_QUIT].clicked) {
                continuePlaying = false;
            }
            break;

        case START:

            // Increase and decrease the number of disks
            if (button[BUTTON_INCREASE].clicked) {
                peg[SOURCE].addDisk();
            } else if (button[BUTTON_DECREASE].clicked) {
                peg[SOURCE].discardDisk();
            }
            // There is no break as for some of the modes the buttons are visually there
            // but they are disabled

        case SOLVE:

            if (button[BUTTON_SOLVE].clicked) {
                gameMode = SOLVE;
            }

        case RESET:
        case PLAY:

            if (button[BUTTON_RESET].clicked) {
                gameMode = RESET;
            } else if (button[BUTTON_IN_GAME_QUIT].clicked) {
                continuePlaying = false;
            } else if (button[BUTTON_MAIN_MENU].clicked) {
                gameMode = MAIN_MENU;
            }
            break;
    }
    // Setting the bool of the button back to false
    for (int i = 0; i < button.length(); i++) {
        button[i].clicked = false;
    }

    // Set up the new button coordinates if the gamemode was changed
    if (previousGamemode != gameMode) {
        buttonSetup();
    }
}

// This method prints most of the text onto the screen for the user
void Allegro::printAllText(Stack peg[], int numberOfMoves) {

    int numberOfStartingDisks = peg[SOURCE].getNumberOfStatingNodes();
    int numberOfFinalNodes = peg[DESTINATION].getNumberOfNodes();

    switch (gameMode) {

        case MAIN_MENU:

            al_draw_text(arial, BLACK, 0, SCREEN_HEIGHT - 30, 0, "By Eric Karpovits");
            al_draw_text(arial, BLACK, SCREEN_WIDTH / 2, 75, ALLEGRO_ALIGN_CENTER, "TOWERS OF HANOI");
            break;

        case INSTRUCTIONS:

            al_draw_text(arial, BLACK, SCREEN_WIDTH / 2, 40, ALLEGRO_ALIGN_CENTER, "INSTRUCTIONS");
            al_draw_text(smallArial, BLACK, 100, 100, ALLEGRO_ALIGN_LEFT,
                         "Towers of Hanoi consists of three pegs with n amount of disks starting at the source peg.");
            al_draw_text(smallArial, BLACK, 100, 140, ALLEGRO_ALIGN_LEFT,
                         "The goal of the game is to move all the disks to the last disk following two simple rules.");
            al_draw_text(smallArial, RED, 150, 180, ALLEGRO_ALIGN_LEFT,
                         "1. One can only move 1 disk at a time.");
            al_draw_text(smallArial, RED, 150, 220, ALLEGRO_ALIGN_LEFT,
                         "2. A larger disk cannot be placed on top of a smaller disk.");
            al_draw_text(smallArial, BLACK, 100, 260, ALLEGRO_ALIGN_LEFT,
                         "The user has two options to solve this puzzle. They can have the computer solve the puzzle for");
            al_draw_text(smallArial, BLACK, 100, 300, ALLEGRO_ALIGN_LEFT,
                         "them by clicking solve in game, or they can solve it themselves by moving the disks with the mouse.");
            al_draw_text(smallArial, BLACK, 100, 340, ALLEGRO_ALIGN_LEFT,
                         "If you want to play, make sure that the peg turns black; indicating that you are close enough to perform actions on them.");
            al_draw_text(smallArial, BLACK, 100, 380, ALLEGRO_ALIGN_LEFT,
                         "The user can just the amount of disks 3-10, and they always have the option to reset if needed.");
            break;

        case CREDITS:

            al_draw_text(arial, BLACK, SCREEN_WIDTH / 2, 40, ALLEGRO_ALIGN_CENTER, "CREDITS");
            al_draw_text(smallArial, BLACK, SCREEN_WIDTH / 2, 100, ALLEGRO_ALIGN_CENTER,
                         "Version 1.0 - Eric Karpovits - Copyright 2020 - All rights reserved");
            break;

        case PLAY:

            al_draw_text(smallArial, RED, SCREEN_WIDTH / 2, 75, ALLEGRO_ALIGN_CENTER, "YOU ARE PLAYING");
            al_draw_text(smallArial, RED, SCREEN_WIDTH / 2, 110, ALLEGRO_ALIGN_CENTER, "SOLVE, INCREASE, AND DECREASE ARE DISABLED");

            if (numberOfFinalNodes == numberOfStartingDisks) {
                al_draw_text(arial, GREEN, SCREEN_WIDTH / 2, 145, ALLEGRO_ALIGN_CENTER, "CONGRATS, YOU ARE DONE");
            }
            // No break on purpose as the gamemode play shows the next text too

        case START:
        case SOLVE:
        case RESET:

            al_draw_textf(arial, BLACK, SCREEN_WIDTH / 2 - 4, (SCREEN_HEIGHT - 38 - LARGE_FONT_SIZE / 2),
                        ALLEGRO_ALIGN_CENTER, "DISKS: %d", peg[SOURCE].getNumberOfStatingNodes());

            al_draw_textf(arial, BLACK, SCREEN_WIDTH / 2, 25, ALLEGRO_ALIGN_CENTER, "MOVES / RECURSIVE CALLS: %d", numberOfMoves);
            break;
    }
}

