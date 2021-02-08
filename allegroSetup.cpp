#include "declarations.h"

/// This function initializes Allegro
/// Int return type - returns an error code if something is wrong
/// Refer to the constants for what the error codes mean
int Allegro::initializeAllegro() {

    // Initialize Allegro, image and audio add ons
    if (!al_init()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize Allegro5!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return ERROR_ALLEGRO;
    }

    if (!al_init_image_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize image addon!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return ERROR_IMAGE_ADDON;
    }

    if (!al_install_audio()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to install audio!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return ERROR_INSTALL_AUDIO;
    }

    if (!al_init_acodec_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize acodec addon!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return ERROR_ACODEC_ADDON;
    }

    // Reserve space and load music files
    al_reserve_samples(NUMBER_OF_MUSIC_SAMPLES);
    gameMusic = al_load_sample("gameMusic.wav");
    buttonClick = al_load_sample("buttonClick.wav");

    // Check that the music files loaded
    if (!gameMusic) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load gameMusic.wav!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return ERROR_MUSIC_FILE_GAMEMUSIC;
    }
    if (!buttonClick) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load buttonClick.wav!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return ERROR_MUSIC_FILE_BUTTONCLICK;
    }

    // Initialize display
    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return ERROR_DISPLAY;
    }

    // Need to add image processor
    if (!al_init_image_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize image add on!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return ERROR_IMG_ADDON;
    }

    // Initialize primative add on
    if (!al_init_primitives_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize primatives add on!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return ERROR_PRIMATIVE_ADDON;
    }

    // Install mouse
    if (!al_install_mouse()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize mouse add on!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return ERROR_MOUSE_ADDON;
    }

    // Font add on
    if (!al_init_font_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize font add on!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return ERROR_FONT_ADDON;
    }

    // initialize the ttf (True Type Font) addon
    if (!al_init_ttf_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize font ttf on!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return ERROR_TTF_ADDON;
    }

    timer = al_create_timer(1.0 / FPS);

    if (!timer) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize fps timer!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return ERROR_FPSTIMER;
    }

    // Load the fonts
    arial = al_load_ttf_font("C:/Windows/Fonts/arial.ttf", LARGE_FONT_SIZE, 0);
    smallArial = al_load_ttf_font("C:/Windows/Fonts/arial.ttf", SMALL_FONT_SIZE, 0);

    // Check that the fonts were creates
    if (!arial) {
        al_show_native_message_box(display, "Error", "Error", "Could not load arial.ttf", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return ERROR_ARIAL_FONT;
    }
    if (!smallArial) {
        al_show_native_message_box(display, "Error", "Error", "Could not create a small version of arial.ttf", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return ERROR_SMALL_ARIAL_FONT;
    }

    // Set up event queue
    eventQueue = al_create_event_queue();
    if (!eventQueue) {
        al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return ERROR_EVENT_QUEUE;
    }

    al_start_timer(timer);

    // Register Events
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_mouse_event_source());

     // Title the window
    al_set_window_title(display, "Towers Of Hanoi - Eric Karpovits");

    // Play game sound
    al_play_sample(gameMusic, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);

    // Load bitmap disks I wanted to make this a loop so it's modular and so that I did not have to type in
    // the same load bitmap function 10 times with 10 checks
    for (int i = 0; i < DISKS_COUNT; i++) {

        // Digit to char conversion
        char c = '0' + i;

        string diskName = "disk";

        // This was the only way to append multiple strings into one. Apstrings was being buggy and annoying
        diskName += c;
        diskName += ".png";

        disk[i] = al_load_bitmap(diskName.c_str());

        if(disk[i] == NULL) {
            al_show_native_message_box(display, "Error", "Error", "Failed to load disk images! Make sure to include 0-9 images.", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(display);
            return ERROR_LOAD_BITMAP;
        }
    }
    return 0;
}
