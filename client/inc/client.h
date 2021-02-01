#ifndef UCHAT_H
#define UCHAT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
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
#include <errno.h>
#include <malloc/malloc.h>
#include <resolv.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

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
#define ENTRY_H 60
#define CHAT_H WINDOW_HEIGHT-ENTRY_H

// Settings screen size and positions
#define TEAM_W 220
#define TEAM_H 264
#define BGPREVIEW_W 104
#define BGPREVIEW_H 79
#define MAX_USERNAME 10
#define MAX_NAME 20
#define MAX_CODE 12
#define MAX_PASS 16
#define MAX_MESSAGE 1000

#define MEDIA_DIR "media_client/"
#define TEMP_DIR "temp/"

typedef unsigned long long csum_t;

//-------> Overall
struct {
    GtkWidget *window;
    GtkWidget *auth;
    GtkWidget *messanger;
    GtkWidget *notificaton;
    char *app;
    char *user;
}   t_application;

struct                      // Structure for current user account data
{
    int id;
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
    short team;
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
    int avatar;             // For avatars
    char *username;         // For nicknmes
    char *time;
    char *date;
    char *date_prev;
    char *content;          // Content of message
    char *content_final;    // For async func
    int chat_id;
} t_msg_data;
t_msg_data msg_data;

typedef struct s_sticker_data
{
    int sticker_id;
    int chat_id;
} t_sticker_data;
t_sticker_data sticker_data;

typedef struct s_photo_data
{
    char *photo_path;
    int chat_id;
} t_photo_data;
t_photo_data photo_data;

typedef struct s_updater
{
    int *chats_id;
    int *messages_id;
    int count;
    csum_t control_sum;
    bool suspend;
    bool busy;
    bool filling_init;
}   t_updater;
t_updater upd_data;

typedef struct s_chat_list              // Structure for people in the chat list
{
    int chat_id;
    int user_id;
    char *username;
    int avatar;
    int members;
    bool status;
    struct s_chat_list *next;   // To next person
}   t_chat_list;
t_chat_list *chatlist;

struct
{
    GtkWidget *main;
    GtkWidget *entry;
    GtkWidget *embedded_view;
    GtkWidget *background;
    GtkWidget *stickers;
    GtkWidget *crlist;
    GtkWidget *chatlist;
    GtkWidget *scrolled_message;
    GtkWidget *chat_screen;
    char* current;
}   t_msg;

typedef struct s_user
{
    int id;
    char *username;
    char *name;
    char *code;
    int team;
    int avatar;
    bool online;
} t_user;

typedef struct s_group
{
    int chat_id;
    char *title;
    int members;
    t_user *user;
} t_chat_data;

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
    GtkWidget *background;
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

//-------> Authorization
struct
{
    GtkWidget *login_menu;
    GtkWidget *registration_menu;
    GtkWidget *mystic_event;
    GtkWidget *instinct_event;
    GtkWidget *valor_event;
}   t_auth;

//-------> Group creation
typedef struct s_new_group
{
    GtkWidget *search_field;
    int *users_id;
    int count;
    int current_user_id;
    char *title;
}   t_new_group;
t_new_group *new_group;

struct      // Удалить после нормальной реализации аватаров к людям. Сейчас это заглушка с рандомным аватаром
{
    char *avatar_generated;
    char *avatar_path;
    int avatar_num;
}   t_avatar;

struct tm *tm_struct;

void tooltip(char *str, void *data);
char *mx_str_gettime();
char *mx_str_getdate();

SSL_CTX* InitCTX(void);
int OpenConnection(const char *hostname, int port);
int ssl_client(char*, char**);
int ssl_client_alloc_len(char*, char**);
void *send_message();
void *send_sticker();
void *send_photo();
void *updater();
bool add_user_to_group(char*, int*, int*);
void create_group(int*);
void get_user(t_user*);
void free_user(t_user*);
void get_chat(t_chat_data*);
void chat_clear_list(t_chat_list**);

void load_providers();
void test_autofill();
void fill_pokemon();
void play_audio();
void avatar_random();
void pokemon_random();
char* random_phrase();
void display_new_chat();
void update_user_avatar(int);

void build_authorization(GtkWidget **main_area);
void build_registration(GtkWidget **main_area);
void build_all(GtkWidget **main_area);
void build_home_screen(GtkWidget **homescreen);
void build_messanger_screen(GtkWidget **msgscreen);
void build_settings_menu(GtkWidget **stgscreen);
void create_gallery(GtkWidget *main);
void create_stickerlist(GtkWidget *main);
void creator_group(GtkWidget *main);
void creator_userprofile(GtkWidget *main, t_user *user, int);
void creator_groupsettings(GtkWidget *main, char *name, bool admin);
void create_notification(GtkWidget *widget, char *text, short type, int x, int y, int w, int h);

char *get_avatar_by_number(int num);
GdkPixbuf *create_pixbuf(const gchar *filename);
GdkPixbuf *get_pixbuf_with_size(char *path, int w, int h);
gboolean draw_event_avatar(GtkWidget *widget, cairo_t *cr, gpointer avatar);
gboolean draw_event_avatar_account(GtkWidget *widget, cairo_t *cr, int size);
gboolean draw_event_avatar_profile(GtkWidget *widget, cairo_t *cr, gpointer avatar);
gboolean draw_event_pokemon(GtkWidget *widget, cairo_t *cr, int size);
gboolean draw_event_avatar_list(GtkWidget *widget, cairo_t *cr, char* path);
gboolean draw_event_status(GtkWidget *widget, cairo_t *cr, int size);
gboolean draw_event_sticker_list(GtkWidget *widget, cairo_t *cr, char* path);
gboolean draw_event_sticker(GtkWidget *widget, cairo_t *cr, char* path);
gboolean draw_event_embedded(GtkWidget *widget, cairo_t *cr, char* path);
gboolean draw_event_embedded_full(GtkWidget *widget, cairo_t *cr, char* path);

GtkWidget *create_chatlist();
GtkWidget *add_single(t_chat_list* list);
void new_outgoing_message(GtkWidget *messages_block);
void new_incoming_message(GtkWidget *messages_block);
void new_outgoing_sticker(GtkWidget *messages_block, int sticker_num);
void new_incoming_sticker(GtkWidget *messages_block, int sticker_num);
void new_outgoing_embedded(GtkWidget *messages_block, char* path);
void new_incoming_embedded(GtkWidget *messages_block, char* path);

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

void active_click(GtkWidget *widget, GdkEventButton *event);

void adduser_click(GtkWidget *widget, GdkEventButton *event, gpointer search_field);
void attach_click(GtkWidget *widget, GdkEventButton *event);
void send_click(GtkWidget *widget, GdkEventButton *event, GtkWidget *entry_text);
void send_press(GtkWidget *widget);
void entry_text_change_event(GtkWidget *widget);
void sticker_click(GtkWidget *widget, GdkEventButton *event, GtkWidget *main);
void chat_push_back(t_chat_list **list, t_chat_data* chat);
void person_click(GtkWidget *widget, GdkEventButton *event);
void msggroup_click(GtkWidget *widget, GdkEventButton *event, GtkWidget *main);

void username_field_change_event(GtkWidget *widget);
void firstname_field_change_event(GtkWidget *widget);
void firstname_input_event(GtkEditable *editable, const gchar *text, gint length, gint *position, gpointer data);
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

void login_button_click(GtkWidget *widget, GdkEventButton *event, gpointer main_area);
void register_button_click(GtkWidget *widget, GdkEventButton *event, gpointer main_area);
void mystic_event_button_click(GtkWidget *widget, GdkEventButton *event);
void instinct_event_button_click(GtkWidget *widget, GdkEventButton *event);
void valor_event_button_click(GtkWidget *widget, GdkEventButton *event);
void login_butt_click(GtkWidget *widget);
void reg_butt_click(GtkWidget *widget);
void arrow_click(GtkWidget *widget, GdkEventButton *event);


#endif
