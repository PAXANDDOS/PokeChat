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
#include <sys/types.h>
#include <dirent.h>
#include <gtk/gtk.h>
// #include "libmx.h"
// #include "cJSON.h"

// Windows 
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
gint CUR_WIDTH;
gint CUR_HEIGHT;

// Leftbar size and position
#define LEFTBAR_W 67
#define LEFTBAR_GAP 9

// Home screen size and positions
#define ACTIVITY_W 347
#define ACTIVITY_H 271
#define ACTIVITY_X 13
#define ACTIVITY_Y 11
#define ACTIVE_PERSON_W ACTIVITY_W-26
#define ACTIVE_PERSON_H 40
#define FACT_W ACTIVITY_W
#define FACT_H 407
#define FACT_X ACTIVITY_X
#define FACT_Y 301
#define POKEMON_SIZE 170
#define WELCOME_W 827
#define WELCOME_H 698
#define WELCOME_X 374
#define WELCOME_Y 11
#define WELCOME_LINK_W 225
#define WELCOME_LINK_H 280
#define WELCOME_LINK_Y 377
#define WELCOME_LINK_MSG_X 57
#define WELCOME_LINK_GROUP_X 301
#define WELCOME_LINK_SETTINGS_X 545

// Messanger screen size and positions
#define LIST_W 360
#define LIST_H WINDOW_HEIGHT
#define CHAT_W WINDOW_WIDTH-LIST_W-LEFTBAR_W
#define ENTRY_W CHAT_W
#define ENTRY_H 72
#define CHAT_H WINDOW_HEIGHT-ENTRY_H

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

typedef struct s_msg_data
{   
    bool sent;
    char *avatar;
    char *nickname;
    char *content;
    int content_len;
} t_msg_data;

typedef struct s_chat_list
{
    char *nickname;
    char *avatar;
    char *status;
    struct s_chat_list *next;
}   t_chat_list;

t_msg_data msg_data;

GtkWidget *home_scr;
GtkWidget *msg_scr;
GtkWidget *chat_screen;
GtkWidget *settings_menu;
GtkWidget *active_screen;
char* avatar_generated;
char* pokemon_fact_image;
char* pokemon_fact_text;
GtkWidget *pokemon_text;
char* current_user_dm;

void preload_images();
void avatar_random();
void pokemon_random();
void build_all(GtkWidget **content_selection_area, GtkWidget **main_area);
void build_home_screen(GtkWidget **homescreen);
void build_messanger_screen(GtkWidget **msgscreen);
gboolean draw_event_avatar(GtkWidget *widget, cairo_t *cr, int size);
gboolean draw_event_pokemon(GtkWidget *widget, cairo_t *cr, int size);

GtkWidget *create_chatlist();
void new_outgoing_message(GtkWidget *messages_block);
void new_incoming_message(GtkWidget *messages_block);


char *mx_str_gettime();
char *mx_str_getdate();
// Удалить потом когда будет подключена либа
char *mx_strnew(const int size);
char *mx_file_to_str(const char *filename);
char *mx_strjoin(const char *s1, const char *s2);
char *mx_itoa(int number);

// Events
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
void status_enter_notify(GtkWidget *widget);
void status_leave_notify(GtkWidget *widget);
void status_click(GtkWidget *widget, GdkEventButton *event);
void settings_enter_notify(GtkWidget *widget);
void settings_leave_notify(GtkWidget *widget);
void settings_click(GtkWidget *widget, GdkEventButton *event);

void active1_enter_notify(GtkWidget *widget);
void active1_leave_notify(GtkWidget *widget);
void active1_click(GtkWidget *widget, GdkEventButton *event);
void active2_enter_notify(GtkWidget *widget);
void active2_leave_notify(GtkWidget *widget);
void active2_click(GtkWidget *widget, GdkEventButton *event);
void active3_enter_notify(GtkWidget *widget);
void active3_leave_notify(GtkWidget *widget);
void active3_click(GtkWidget *widget, GdkEventButton *event);
void active4_enter_notify(GtkWidget *widget);
void active4_leave_notify(GtkWidget *widget);
void active4_click(GtkWidget *widget, GdkEventButton *event);
void active5_enter_notify(GtkWidget *widget);
void active5_leave_notify(GtkWidget *widget);
void active5_click(GtkWidget *widget, GdkEventButton *event);
void tomsg_enter_notify(GtkWidget *widget);
void tomsg_leave_notify(GtkWidget *widget);
void togroup_enter_notify(GtkWidget *widget);
void togroup_leave_notify(GtkWidget *widget);
void tosettings_enter_notify(GtkWidget *widget);
void tosettings_leave_notify(GtkWidget *widget);

void adduser_enter_notify(GtkWidget *widget);
void adduser_leave_notify(GtkWidget *widget);
void adduser_click(GtkWidget *widget, GdkEventButton *event);
void attach_enter_notify(GtkWidget *widget);
void attach_leave_notify(GtkWidget *widget);
void attach_click(GtkWidget *widget, GdkEventButton *event);
void send_enter_notify(GtkWidget *widget);
void send_leave_notify(GtkWidget *widget);
void send_click(GtkWidget *widget, GdkEventButton *event, GtkWidget *entry_text);
void entry_text_change_event(GtkWidget *widget);
void sticker_enter_notify(GtkWidget *widget);
void sticker_leave_notify(GtkWidget *widget);
void sticker_click(GtkWidget *widget, GdkEventButton *event);
void single_event_enter_notify(GtkWidget *widget);
void single_event_leave_notify(GtkWidget *widget);
void single_event_click(GtkWidget *widget, GdkEventButton *event);
