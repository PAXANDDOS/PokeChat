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
#include <ctype.h>
#include <dirent.h>
#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include "SDL2_mixer/SDL_mixer.h"
#include "libmx.h"
#include "cJSON.h"
#include "openssl/bio.h"
#include "openssl/evp.h"
#include <pthread.h>

// Windows
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

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

// Settings screen size and positions
#define TEAM_W 220
#define TEAM_H 264
#define BGPREVIEW_W 104
#define BGPREVIEW_H 79

int temp;

//-------> Overall
struct {
    GtkWidget *window;
    char *app;
    char *user;
}   t_application;

struct                      // Structure for current user account data
{
    char *username;         // For account username
    char *name;             // For account real name
    char *password;         // char* for password
    char *code;             // 12-digit trainer code
    short team;             // 1-3 team choice
    short theme;            // 1-3 app theme
    short background;       // 1-4 chat background
    char *avatar;           // Path to chosen avatar
    short avatar_chosen;    // Number of chosen avatar. Transfers to t_account.avatar
} t_account;

struct                  // TEMPORAL Structure for tracking entries
{
    char *username;         // For account username
    char *name;             // For account real name
    char *password;         // char* for password
    char *repass;
    char *code;             // 12-digit trainer code
} t_account_temp;


//-------> Leftbar
struct
{   
    GtkWidget *home_box;
    GtkWidget *msg_box;
    GtkWidget *group_box;
    GtkWidget *events_box;
    //GtkWidget *status_box;
    GtkWidget *settings_box;
    short active;
    GtkWidget *home_scr;
    GtkWidget *msg_scr;
    GtkWidget *settings_scr;
    GtkWidget *active_screen;
}   t_leftbar;


//-------> Home
struct      // Structure for random pokemon data
{
    GtkWidget *pokemon_text;
    char* pokemon_fact_image;
    char* pokemon_fact_text;
    char* pokemon_fact_audio;
}   t_pokefact;


//-------> Messages
typedef struct s_msg_data   // Structure for data in messages
{
    bool sent;              // If send button was pressed
    char *avatar;           // For avatars
    char *nickname;         // For nicknmes
    char *content;          // Content of message
    int content_len;        // Length of message
} t_msg_data;
t_msg_data msg_data;

typedef struct s_chat_list      // Structure for people in the chat list
{
    char *nickname;
    int avatar;
    bool status;
    struct s_chat_list *next;   // To next person
}   t_chat_list;

struct s_chat   // Selected user in chatlist
{
    GtkWidget *chat_screen;
    char* current;
    GtkWidget *stickers;
    struct s_chat *next;
}   t_chat;


//-------> Settings
struct
{
    GtkCssProvider *styles;
    GtkCssProvider *chat;
    GtkCssProvider *theme;
}   t_providers;

struct                  // Labels for settings screen
{
    GtkWidget *username;
    GtkWidget *name;
    GtkWidget *backgound;
}   t_settings;

struct
{
    GtkWidget *team_mystic;
    GtkWidget *team_instinct;
    GtkWidget *team_valor;
}   t_teams;

struct
{
    GtkWidget *theme_default;
    GtkWidget *theme_dark;
    GtkWidget *theme_light;
}   t_theme;

struct
{
    GtkWidget *bg1;
    GtkWidget *bg2;
    GtkWidget *bg3;
    GtkWidget *bg4;
}   t_chat_bg;

struct      // Удалить после нормальной реализации аватаров к людям. Сейчас это заглушка с рандомным аватаром
{
    char* avatar_generated;
    char *avatar_path;
}   t_avatar;

struct tm *tm_struct;
char *mx_str_gettime();
char *mx_str_getdate();

int ssl_client(char*, int, char*);
void send_message();
void send_sticker();
void send_photo();

void test_autofill();
void fill_pokemon();
void play_audio();
void preload_images();
void avatar_random();
void pokemon_random();
void build_all(GtkWidget **content_selection_area, GtkWidget **main_area);
void build_home_screen(GtkWidget **homescreen);
void build_messanger_screen(GtkWidget **msgscreen);
void build_settings_menu(GtkWidget **stgscreen);
void create_gallery(GtkWidget *main);
void create_stickerlist(GtkWidget *main);

char *get_avatar_by_number(int num);
GdkPixbuf *create_pixbuf(const gchar *filename);
GdkPixbuf *get_pixbuf_with_size(char *path, int w, int h);
gboolean draw_event_avatar(GtkWidget *widget, cairo_t *cr, int avatar);
gboolean draw_event_avatar_account(GtkWidget *widget, cairo_t *cr, int size);
gboolean draw_event_pokemon(GtkWidget *widget, cairo_t *cr, int size);
gboolean draw_event_avatar_list(GtkWidget *widget, cairo_t *cr, char* path);
gboolean draw_event_status(GtkWidget *widget, cairo_t *cr, int size);
gboolean draw_event_sticker_list(GtkWidget *widget, cairo_t *cr, char* path);

GtkWidget *create_chatlist(t_chat_list* list);
void new_outgoing_message(GtkWidget *messages_block);
void new_incoming_message(GtkWidget *messages_block);

// Events
void event_enter_notify(GtkWidget *widget);
void event_false_enter_notify(GtkWidget *widget);
void event_leave_notify(GtkWidget *widget);
void all_input_event(GtkEditable *editable, const gchar *text, gint length, gint *position, gpointer data);

void home_click(GtkWidget *widget, GdkEventButton *event);
void messages_click(GtkWidget *widget, GdkEventButton *event);
void group_click(GtkWidget *widget, GdkEventButton *event);
void events_click(GtkWidget *widget, GdkEventButton *event);
void status_click(GtkWidget *widget, GdkEventButton *event);
void settings_click(GtkWidget *widget, GdkEventButton *event);

void active1_click(GtkWidget *widget, GdkEventButton *event);
void active2_click(GtkWidget *widget, GdkEventButton *event);
void active3_click(GtkWidget *widget, GdkEventButton *event);
void active4_click(GtkWidget *widget, GdkEventButton *event);
void active5_click(GtkWidget *widget, GdkEventButton *event);

void adduser_click(GtkWidget *widget, GdkEventButton *event);
void attach_click(GtkWidget *widget, GdkEventButton *event);
void send_click(GtkWidget *widget, GdkEventButton *event, GtkWidget *entry_text);
void entry_text_change_event(GtkWidget *widget);
void sticker_click(GtkWidget *widget, GdkEventButton *event, GtkWidget *main);
void single_event_click(GtkWidget *widget, GdkEventButton *event);

void username_field_change_event(GtkWidget *widget);
void firstaname_field_change_event(GtkWidget *widget);
void code_field_change_event(GtkWidget *widget);
void code_input_event(GtkEditable *editable, const gchar *text, gint length, gint *position, gpointer data);
void pass_field_change_event(GtkWidget *widget);
void repass_field_change_event(GtkWidget *widget);
void apply_butt_click(GtkWidget *widget);
void exit_button_click(GtkWidget *widget, GdkEventButton *event);
void add_button_click(GtkWidget *widget, GdkEventButton *event);
void gallery_button_click(GtkWidget *widget, GdkEventButton *event, GtkWidget *main);
void team_mystic_click(GtkWidget *widget, GdkEventButton *event);
void team_instinct_click(GtkWidget *widget, GdkEventButton *event);
void team_valor_click(GtkWidget *widget, GdkEventButton *event);
void theme_default_click(GtkWidget *widget, GdkEventButton *event);
void theme_dark_click(GtkWidget *widget, GdkEventButton *event);
void theme_light_click(GtkWidget *widget, GdkEventButton *event);
void bg1_preview_click(GtkWidget *widget, GdkEventButton *event);
void bg2_preview_click(GtkWidget *widget, GdkEventButton *event);
void bg3_preview_click(GtkWidget *widget, GdkEventButton *event);
void bg4_preview_click(GtkWidget *widget, GdkEventButton *event);
