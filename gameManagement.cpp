#include "declarations.h"

/// Constructor
GameManagement::GameManagement(Allegro &display, Stack *peg) : display(display), peg(peg) {

    continuePlaying = true;
    userMadeValidMove = false;
    resetNeeded = false;
    hanoiRunning = false;
    numberOfMoves = 0;
    whichPegNeedsToPush = -1;
    whichPegNeedsToPop = -1;

    for (int i = 0; i < PEGS_COUNT; i++) {
        pegProperties[i].clicked = false;
        pegProperties[i].released = false;
        pegProperties[i].filled = false;
    }
}

/**
* Main function of the game which loops
* It allows every game mode to run and the user to play the game
**/
void GameManagement::play() {

    // Declare variables and create an event
    GAMEMODE gameMode = display.getGameMode();
    ALLEGRO_FONT *arial = display.getArialFont();
    ALLEGRO_FONT *smallArial = display.getSmallArialFont();
    int numberOfStartingDisks = peg[SOURCE].getNumberOfStatingNodes();

    ALLEGRO_EVENT &event = display.getEvent();
    ALLEGRO_EVENT_QUEUE *evQueue = display.getEventQueue();
    al_wait_for_event(evQueue, &event);

    al_clear_to_color(LIGHT_BLUE);

    switch (gameMode) {

        case SOLVE:

            if (!resetNeeded) {

                resetNeeded = true;
                hanoiRunning = true;
                hanoi(numberOfStartingDisks, SOURCE, DESTINATION, INTERMEDIATE);
                hanoiRunning = false;
                // Useful function to clear all the events the user was trying to perform while hanoi was running
                al_flush_event_queue(evQueue);
            }

            if (!hanoiRunning) {
                al_draw_text(arial, GREEN, SCREEN_WIDTH / 2, 75, ALLEGRO_ALIGN_CENTER, "DONE");
            } else {
                al_draw_text(smallArial, RED, SCREEN_WIDTH / 2, 75, ALLEGRO_ALIGN_CENTER, "EXCECUTING - BUTTONS ARE DISABLED");
            }

            display.displayDisks(peg, pegProperties);
            break;

        case PLAY:

            if (userMadeValidMove) {
                moveUserDisk();
                userMadeValidMove = false;
            }

            display.displayDisks(peg, pegProperties);
            break;

        case RESET:

            resetEverything();
            display.displayDisks(peg, pegProperties);
            break;

        case START:

            // This is an if statement that is checking if the user went to the main menu after solving
            // which then the program would have to reset everything so that it is ready to be used again
            if (resetNeeded){
                resetEverything();
            }
            display.displayDisks(peg, pegProperties);
            break;

        // These cases have nothing special, they just print out text and have buttons
        // included so that there would be no warnings
        case CREDITS:
        case INSTRUCTIONS:
        case MAIN_MENU:
            break;
    }

    // A method that prints all the gamemodes text onto a screen
    display.printAllText(peg, numberOfMoves);

    // A method which draws all the buttons for the specific gamemodes
    display.drawButtons();
    al_flip_display();

    // Checks if the user closed the display
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {

        continuePlaying = false;

    // Check mouse down events
    } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

        // Check which buttons was clicked
        display.playButtonClickSound();
        // Checks which button if any if the mouse was clicked
        display.checkButtonAction(pegProperties);
        display.checkButtonState(continuePlaying, peg);

    } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

        display.checkButtonAction(pegProperties);

        if (checkIsUserMoveValid()) {

            userMadeValidMove = true;

            if (gameMode != PLAY) {
                resetNeeded = true;
                display.setGameMode(PLAY);
                display.buttonSetup();
            }
        }

    // Check mouse movement event
    } else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {

        // Check if the button needs to be filled in if the mouse is hovering over it
        if (!hanoiRunning) {
            display.checkButtonAction(pegProperties);
        }
    }
}


void GameManagement::hanoi(int diskCount, int source, int destination, int intermediate) {

    // Base case
    if (diskCount == 1) {

        moveDisks(source, destination);

    } else {

        // Take all top disks but the last one and move to intermediate
        hanoi(diskCount - 1, source, intermediate, destination);
        // Move last disk to destination
        moveDisks(source, destination);
        // Move all top disks as a stack from interm to destination
        hanoi(diskCount - 1, intermediate, destination, source);
     }
}

// Move disk method from the source to the destination
void GameManagement::moveDisks(int source, int destination) {

    // Pushing a popped disked
    peg[destination].push(peg[source].pop());
    // Increase the number of moves / recursion calls - they are the same thing (tested it)
    numberOfMoves++;
    // Call main loop again to display everything
    play();
    al_rest(0.5);
}

// A method that resets everything
void GameManagement::resetEverything() {

    // Clears each peg's linked list
    for(int i = 0; i < PEGS_COUNT; i++){
        peg[i].clearList();
    }
    // Populates the source peg with 3 disks
    peg[SOURCE].populateSourcePeg();
    // Sets game mode to START, button setup for game mode START and reset everything esle
    display.setGameMode(START);
    display.buttonSetup();
    numberOfMoves = 0;
    resetNeeded = false;
}

// This is the main loop that essentailly it is called when the mouse button is released
// and it makes a at which peg it was clicked if any and where it was released
// If it was clicked and released at 2 different pegs it is a valid and will return true
bool GameManagement::checkIsUserMoveValid() {

    int numberOfClicked = 0;
    int numberOfReleased = 0;
    bool validUserMove = false;

    // Counting the number of instances of clicks / releases
    // This may seem useless at first but sometimes allegro bugs out and
    // adds a mouse button down event (rare but good for safe measures)
    for (int i = 0; i < PEGS_COUNT; i++) {

        if (pegProperties[i].clicked) {
            numberOfClicked++;
        }
        if (pegProperties[i].released) {
            numberOfReleased++;
        }
    }

    if (numberOfClicked == 1 && numberOfReleased == 1) {
        for (int i = 0; i < PEGS_COUNT; i++) {

            // This if statement is checking that the user did not click and release on the same peg
            if (pegProperties[i].clicked != pegProperties[i].released) {
                validUserMove = true;

                if (pegProperties[i].released) {
                    whichPegNeedsToPush = i;
                } else if (pegProperties[i].clicked) {
                    whichPegNeedsToPop = i;
                }
            }
        }
    }
    // Reseting properties
    for (int i = 0; i < PEGS_COUNT; i++) {
        pegProperties[i].clicked = false;
        pegProperties[i].released = false;
    }

    return validUserMove;
}

// This is the function that does a quick check and then moves the disks by users discression
void GameManagement::moveUserDisk() {

    if (!peg[whichPegNeedsToPop].isEmpty(ONE_NODE) && (peg[whichPegNeedsToPush].isEmpty(ONE_NODE) ||
        peg[whichPegNeedsToPush].getValue(0) > peg[whichPegNeedsToPop].getValue(0))) {

        peg[whichPegNeedsToPush].push(peg[whichPegNeedsToPop].pop());
        numberOfMoves++;
    }
}
