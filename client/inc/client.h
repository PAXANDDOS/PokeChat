#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
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
    char *pressed;
    GtkWidget *standard;
    GtkWidget *colorful;
} t_image_button;

t_image_button home_img;
t_image_button messages_img;
t_image_button group_img;
t_image_button events_img;
t_image_button status_img;
t_image_button settings_img;
t_image_button homeBG_img;
t_image_button msgBG_img;

t_image_button *t_active;

struct
{
    GtkWidget *home_box;
    GtkWidget *messages_box;
    GtkWidget *group_box;
    GtkWidget *events_box;
    GtkWidget *status_box;
    GtkWidget *settings_box;
    GtkWidget *homeBG_box;
    GtkWidget *msgBG_box;
} t_img_event_box;

void preload_images();
void build_left_bar(GtkWidget **content_selection_area, GtkWidget **main_area);
void build_main_area(GtkWidget **main_area, GtkWidget **window);
void build_home_screen(GtkWidget **content_selection_area, GtkWidget **main_area);
void build_messanger_screen(GtkWidget **content_selection_area, GtkWidget **main_area);

void home_enter_notify(GtkWidget *widget, gpointer data);
void home_leave_notify(GtkWidget *widget, gpointer data);
void home_click(GtkWidget *widget, gpointer data);
void messages_enter_notify(GtkWidget *widget, gpointer data);
void messages_leave_notify(GtkWidget *widget, gpointer data);
void messages_click(GtkWidget *widget, gpointer data);
void contacts_enter_notify(GtkWidget *widget, gpointer data);
void contacts_leave_notify(GtkWidget *widget, gpointer data);
void contacts_click(GtkWidget *widget, gpointer data);
void settings_enter_notify(GtkWidget *widget, gpointer data);
void settings_leave_notify(GtkWidget *widget, gpointer data);
void settings_click(GtkWidget *widget, gpointer data);
void goto_home(GtkWidget *widget, gpointer ch);
void goto_msg(GtkWidget *widget, gpointer ch);
//void goto_settings(GtkWidget *widget, gpointer data);
