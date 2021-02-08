/*********************************************************************************
 * Eric Karpovits - Towers of Hanoi - Mr. Kronberg                               *
 *                                                                               *
 * Fully functioning game with the user being able to pick between 3-10 disks.   *
 * The game is fully playable and can be solved itself using recursion.          *
 * For this program I really focussed on giving the user a great experience,     *
 * so I make the buttons turn solid when the mouse is hovering and when the user *
 * is near a peg.                                                                *
 *                                                                               *
 * Last Modified: November 2, 2020                                               *
 *********************************************************************************/

#include "declarations.h"

int main() {

    // Create pegs
    Stack peg[PEGS_COUNT];
    // Create allegro object
    Allegro display;
    // Create object game that has the other two objects as members
    GameManagement game(display, &peg[SOURCE]);

    ///******* Initialize allegro *************
    int errorCode = display.initializeAllegro();
    if (errorCode != 0) {
        return errorCode;
    }

    // Setup buttons and populate source peg
    display.buttonSetup();
    peg[SOURCE].populateSourcePeg();

    ///******* Main game loop ********
    while (game.isContinuePlaying()) {
        game.play();
    }

    return 0;
}
