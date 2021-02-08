#ifndef GAME_MANAGEMEN_H_INCLUDED
#define GAME_MANAGEMENT_H_INCLUDED

// My game class which has the Allegro class object and Stack class object as a members
// allowed me not to have to pass as many arguments into hanoi algorithm
class GameManagement {

    private:

        // Class object members - cool thing I learned
        Allegro &display;
        Stack *peg;
        bool continuePlaying;
        bool resetNeeded;
        bool userMadeValidMove;
        int numberOfMoves;
        bool hanoiRunning;
        // For the playabale game
        int whichPegNeedsToPush;
        int whichPegNeedsToPop;

        PEG pegProperties[PEGS_COUNT];

    public:

        // Constructor - as you can see it is different as I am making the objects as members in this class
        GameManagement(Allegro &display, Stack *peg);
        // Destructor
        ~GameManagement(){;}

        // Main play game loop
        void play();
        // A getter method which gets the continue playing variable
        bool isContinuePlaying() { return continuePlaying; }
        // This method moves the disks from the soure to the destination
        void moveDisks(int source, int destination);
        // This method resets everything
        void resetEverything();
        void hanoi(int numberOfDisks, int source, int destination, int intermediate);

        /// The two functions to make the game playable
        bool checkIsUserMoveValid();
        void moveUserDisk();
};

#endif // GAME_MANAGEMEN_H_INCLUDED
