#include <stdio.h>
#include "stack.h"
#include <cfl.h> // Fl_init_all, Fl_lock, Fl_run
#include <cfl_box.h>
#include <cfl_enums.h>
#include <cfl_button.h>
#include <cfl_image.h> // Fl_register_images
#include <cfl_widget.h>
#include <cfl_window.h>
#include <cfl_text.h>
#include <cfl_dialog.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>

#define START "Start"
#define STOP "Stop"
#define OPEN "Open ROM"
#define HORIZONTAL_BASE 0
#define VERTICAL_BASE   0
#define WINDOW_X        100
#define WINDOW_Y        100
#define WINDOW_WIDTH    640
#define SCREEN_X        HORIZONTAL_BASE
#define SCREEN_Y        VERTICAL_BASE 
#define SCREEN_WIDTH    WINDOW_WIDTH
#define SCREEN_HEIGHT   320
#define SCREEN_BOX      SCREEN_X, SCREEN_Y, SCREEN_WIDTH, SCREEN_HEIGHT, NULL
#define MENU_X          HORIZONTAL_BASE 
#define MENU_Y          (SCREEN_Y + SCREEN_HEIGHT)
#define MENU_WIDTH      WINDOW_WIDTH
#define MENU_HEIGHT     280
#define MENU_BOX        MENU_X, MENU_Y, MENU_WIDTH, MENU_HEIGHT, NULL
#define LOG_X           HORIZONTAL_BASE 
#define LOG_Y           (MENU_Y + MENU_HEIGHT)
#define LOG_WIDTH       WINDOW_WIDTH
#define LOG_HEIGHT      30
#define LOG_BOX         LOG_X, LOG_Y, LOG_WIDTH, LOG_HEIGHT, NULL
#define WINDOW_HEIGHT   (SCREEN_HEIGHT + MENU_HEIGHT + LOG_HEIGHT) 
#define WINDOW_SPAWN    WINDOW_X, WINDOW_Y, WINDOW_WIDTH, WINDOW_HEIGHT, "Chip 8 Emulator"

#define HORIZONTAL_PAD  20
#define VERTICAL_PAD    20
#define BUTTON_WIDTH    100
#define BUTTON_HEIGHT   30
#define BUTTON_X        (HORIZONTAL_BASE + HORIZONTAL_PAD)
#define START_BUTTON_Y  (MENU_Y + VERTICAL_PAD)
#define START_BUTTON    BUTTON_X, START_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, START 
#define OPEN_BUTTON_Y   (START_BUTTON_Y + BUTTON_HEIGHT + VERTICAL_PAD)
#define OPEN_BUTTON     BUTTON_X, OPEN_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, OPEN 

bool running = false;
char global_filename[PATH_MAX];

void toggle_start_stop(Fl_Widget *w, void *data)
{
    Fl_Box* passed_log_box = (Fl_Box*) data;
    char buf[6];
    if (running == true) {
        running = false;
        Fl_Widget_set_label(w, START);
        Fl_Widget_set_label(passed_log_box, "Info: Stopped emulation");
    }
    else {
        running = true;
        Fl_Widget_set_label(w, STOP);
        Fl_Widget_set_label(passed_log_box, "Info: Started emulation");
    }
}

#define ABS_PATH 0
void open_file_browser(Fl_Widget *w, void *data)
{
    Fl_Box* passed_log_box = (Fl_Box*) data;
    char* filename = Fl_file_chooser("Open ROM file?", "*.rom", "/home/azzentys", ABS_PATH);
    if (filename != NULL) {
        strcpy(global_filename, filename);
        char buffer[PATH_MAX + 20];
        snprintf(buffer, PATH_MAX + 20, "Info: Loaded - %s", global_filename);
        Fl_Box_set_label(passed_log_box, buffer);
    }
}

const char* PXM[] = {
        "64 32 2 1",
        "0 c #000000",
        "1 c #ffffff",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000001111000000000000000000000000000000000111100000000000",
        "0000000000001001000000000000000000000000000000000100100000000000",
        "0000000000001001000000000000000000000000000000000100100000000000",
        "0000000000001111000000000000000000000000000000000111100000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000110000000000000000000011000000000000000000",
        "0000000000000000000000011000000000000000000110000000000000000000",
        "0000000000000000000000001111111111111111111100000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000"
};

int main(void) {
    Fl_init_all();        // init all styles

    // Window
    Fl_Window *w = Fl_Window_new(WINDOW_SPAWN);

    // Screen Box
    Fl_Box* screen_box = Fl_Box_new(SCREEN_BOX);
    Fl_Box_set_box(screen_box, Fl_BoxType_GleamDownBox);
    Fl_Box_set_color(screen_box, Fl_Color_Black); 

    // Menu Box
    Fl_Box* button_box = Fl_Box_new(MENU_BOX);
    Fl_Box_set_box(button_box, Fl_BoxType_GleamThinDownBox);
    // Menu Box - Start/Stop Button
    Fl_Button* start_button = Fl_Button_new(START_BUTTON);
    Fl_Button_set_box(start_button, Fl_BoxType_GleamUpBox);
    Fl_Button_set_color(start_button, Fl_Color_White);
    // Menu Box - Open Button
    Fl_Button* open_button = Fl_Button_new(OPEN_BUTTON);
    Fl_Button_set_box(open_button, Fl_BoxType_GleamUpBox);
    Fl_Button_set_color(open_button, Fl_Color_White);

    // Log Box
    Fl_Box* log_box = Fl_Box_new(LOG_BOX);
    Fl_Box_set_box(log_box, Fl_BoxType_DownBox);
    Fl_Box_set_color(log_box, Fl_Color_Black);
    Fl_Box_set_label_color(log_box, Fl_Color_Green);
    Fl_Box_set_label_size(log_box, 12);
    Fl_Box_set_label_font(log_box, Fl_Font_Screen);
    Fl_Box_set_label_type(log_box, Fl_LabelType_Normal);
    Fl_Button_set_callback(start_button, toggle_start_stop, log_box);
    Fl_Button_set_callback(open_button, open_file_browser, log_box);
    Fl_Pixmap* i = Fl_Pixmap_new(PXM);
    Fl_Pixmap_scale(i, 640, 320, true, true);
    Fl_Box_set_image(screen_box, i);

    Fl_Window_end(w);
    Fl_Window_show(w);
    return Fl_run();
}
