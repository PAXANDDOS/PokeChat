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
#include <gtk/gtk.h>
// #include "libmx.h"
// #include "cJSON.h"

// Windows 
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
gint CUR_WIDTH;
gint CUR_HEIGHT;

// Colors
#define HEX_1F1F1F 0.12
#define HEX_E1E1E1 0.89

// Structures
struct s_settings
{
    GtkWidget *standard;
    GtkWidget *colorful;
} t_settings;

struct s_contacts
{
    GtkWidget *standard;
    GtkWidget *colorful;
} t_contacts;

struct s_messages
{
    GtkWidget *standard;
    GtkWidget *colorful;
} t_messages;

// Event boxes
struct s_eventbox
{
    GtkWidget *contacts_box;
    GtkWidget *settings_box;
    GtkWidget *messages_box;
} t_img_event_box;

void preload_images();
void build_left_bar(GtkWidget **content_selection_area, GtkWidget **main_area);
void build_main_area(GtkWidget **main_area, GtkWidget **background, GtkWidget **window);
gboolean mx_draw_event_background(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean mx_draw_event_chat_enter_area(GtkWidget *widget, cairo_t *cr, gpointer user_data);
