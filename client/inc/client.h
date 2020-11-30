#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cairo.h>
#include <math.h>
#include <gtk/gtk.h>
// #include "libmx.h"
// #include "cJSON.h"

// Windows 
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
gint CUR_WIDTH;
gint CUR_HEIGHT;

// Chat elements
#define LEFTBAR_W 67
#define LEFTBAR_GAP 9

typedef struct s_image_button
{
    bool active;
    char *basic;
    char *hovered;
    GtkWidget *standard;
    GtkWidget *colorful;
} t_image_button;

t_image_button home_img;
t_image_button messages_img;
t_image_button group_img;
t_image_button events_img;
t_image_button settings_img;

t_image_button *t_active;

struct
{
    GtkWidget *home_box;
    GtkWidget *messages_box;
    GtkWidget *group_box;
    GtkWidget *events_box;
    GtkWidget *settings_box;
} t_img_event_box;

GtkWidget *home_scr;
GtkWidget *msg_scr;
GtkWidget *settings_menu;
GtkWidget *active_screen;
char* avatar_generated;

void preload_images();
char* avatar_random();
void build_all(GtkWidget **content_selection_area, GtkWidget **main_area);
void build_main_area(GtkWidget **main_area, GtkWidget **window);
void build_home_screen(GtkWidget **content_selection_area, GtkWidget **main_area);
void build_messanger_screen(GtkWidget **content_selection_area, GtkWidget **main_area);
gboolean mx_draw_event_avatar(GtkWidget *widget, cairo_t *cr);

void home_enter_notify(GtkWidget *widget);
void home_leave_notify(GtkWidget *widget);
void home_click(GtkWidget *widget, GdkEventButton *event);
void messages_enter_notify(GtkWidget *widget);
void messages_leave_notify(GtkWidget *widget);
void messages_click(GtkWidget *widget, GdkEventButton *event);
void group_enter_notify(GtkWidget *widget);
void group_leave_notify(GtkWidget *widget);
void group_click(GtkWidget *widget, GdkEventButton *event);
void events_enter_notify(GtkWidget *widget);
void events_leave_notify(GtkWidget *widget);
void events_click(GtkWidget *widget, GdkEventButton *event);
void settings_enter_notify(GtkWidget *widget);
void settings_leave_notify(GtkWidget *widget);
void settings_click(GtkWidget *widget, GdkEventButton *event);
