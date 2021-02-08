#ifndef ALLEGRO_H_INCLUDED
#define ALLEGRO_H_INCLUDED

class Allegro {

    private:

        // Member variables - mainly all pointers for allegro
        ALLEGRO_DISPLAY *display;
        ALLEGRO_FONT *arial, *smallArial;
        ALLEGRO_TIMER *timer;
        ALLEGRO_EVENT_QUEUE *eventQueue;
        ALLEGRO_EVENT event;
        ALLEGRO_SAMPLE *gameMusic, *buttonClick;
        ALLEGRO_BITMAP *disk[DISKS_COUNT];

        // Button properties vector struct
        apvector<BUTTON> button;

        // An enum of all game modes
        GAMEMODE gameMode;

    public:

        // Inline constructor & destructor
        Allegro() { gameMode = MAIN_MENU; }
        ~Allegro() { releaseMemory(); }

        // Untilities
        int initializeAllegro();
        void releaseMemory();
        void printAllText(Stack peg[], int numberOfMoves);

        // Acessors
        ALLEGRO_EVENT_QUEUE *getEventQueue() { return eventQueue; }
        GAMEMODE getGameMode() { return gameMode; }
        ALLEGRO_FONT *getArialFont() { return arial; }
        ALLEGRO_FONT *getSmallArialFont() { return smallArial; }
        ALLEGRO_EVENT &getEvent() { return event; }

        // Modifier
        void setGameMode(GAMEMODE newGameMode) { gameMode = newGameMode; }

        // Display disks methods
        void displayDisks(Stack peg[], PEG pegProperties[]);
        void preparePegsForDrawing(PEG pegProperties[]);
        apvector<SCREEN_POSITIONS> calculateScreenPositionsForDisks(apvector<int> currentPegValues, int pegNumber);
        void displayDisksForPeg(apvector<SCREEN_POSITIONS> screenPositions, apvector<int> currentPegValues);

        // Buttons
        void buttonSetup();
        void setButtonProperties(int buttonNumber, int upperLeftX, int upperLeftY, int lowerRightX, int lowerRightY, bool largeText, string buttonTitle);
        void drawButtons();
        void checkButtonState(bool &continuePlaying, Stack peg[]);
        void checkButtonAction(PEG pegProperties[]);
        void playButtonClickSound() { al_play_sample(buttonClick, 10.0, 0, 30.0, ALLEGRO_PLAYMODE_ONCE, 0); }
};

#endif // ALLEGRO_H_INCLUDED
