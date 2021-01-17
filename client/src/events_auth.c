#include "../inc/client.h"

void login_button_click(GtkWidget *widget, GdkEventButton *event, gpointer main_area)
{
    if(widget){}
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_destroy(GTK_WIDGET(t_auth.mystic_event));
        gtk_widget_destroy(GTK_WIDGET(t_auth.instinct_event));
        gtk_widget_destroy(GTK_WIDGET(t_auth.valor_event));
        gtk_widget_destroy(GTK_WIDGET(t_auth.registration_menu));
        build_authorization((GtkWidget**)main_area);
    }
}

void register_button_click(GtkWidget *widget, GdkEventButton *event, gpointer main_area)
{
    if(widget){}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_destroy(GTK_WIDGET(t_auth.login_menu));
        build_registration((GtkWidget**)main_area);
    }
}

void mystic_event_button_click(GtkWidget *widget, GdkEventButton *event)
{
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) 
    {
        gtk_widget_unset_state_flags(GTK_WIDGET(t_auth.instinct_event), GTK_STATE_FLAG_LINK);
        gtk_widget_unset_state_flags(GTK_WIDGET(t_auth.valor_event), GTK_STATE_FLAG_LINK);
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account_temp.team = 1;
    }
}

void instinct_event_button_click(GtkWidget *widget, GdkEventButton *event)
{
    if(widget){}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) 
    {
        gtk_widget_unset_state_flags(GTK_WIDGET(t_auth.mystic_event), GTK_STATE_FLAG_LINK);
        gtk_widget_unset_state_flags(GTK_WIDGET(t_auth.valor_event), GTK_STATE_FLAG_LINK);
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account_temp.team = 2;
    }
}

void valor_event_button_click(GtkWidget *widget, GdkEventButton *event)
{
    if(widget){}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) 
    {
        gtk_widget_unset_state_flags(GTK_WIDGET(t_auth.mystic_event), GTK_STATE_FLAG_LINK);
        gtk_widget_unset_state_flags(GTK_WIDGET(t_auth.instinct_event), GTK_STATE_FLAG_LINK);
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account_temp.team = 3;
    }
}

void login_butt_click(GtkWidget *widget){
    if(widget) {}

    cJSON *json = cJSON_CreateObject();
    cJSON *json_login_user = cJSON_CreateObject();
    cJSON_AddStringToObject(json_login_user, "username", t_account_temp.username);
    cJSON_AddStringToObject(json_login_user, "password", t_account_temp.password);
    cJSON_AddItemToObject(json, "login_user", json_login_user);
    char *json_string = cJSON_PrintUnformatted(json);
    printf("%s\n", json_string);
    char *result = NULL;
    ssl_client(json_string, &result);
    cJSON *response = cJSON_Parse(result);
    if (!cJSON_IsNull(response) && strcmp(result, "")) {
        int user_id = cJSON_GetNumberValue(cJSON_GetObjectItem(response, "user_id"));
        char *name = cJSON_GetStringValue(cJSON_GetObjectItem(response, "name"));
        char *code = cJSON_GetStringValue(cJSON_GetObjectItem(response, "code"));
        short team = cJSON_GetNumberValue(cJSON_GetObjectItem(response, "team"));
        int avatar = cJSON_GetNumberValue(cJSON_GetObjectItem(response, "avatar"));
        short theme = cJSON_GetNumberValue(cJSON_GetObjectItem(response, "theme"));
        short bg = cJSON_GetNumberValue(cJSON_GetObjectItem(response, "background"));
        printf("My old user id: %d\n", user_id);
        printf("My name: %s\n", name);
        printf("My code: %s\n", code);
        printf("My team: %d\n", team);
        printf("My theme: %d\n", theme);
        printf("My bg: %d\n", bg);
        t_account.id = user_id;
        t_account.name = name;
        t_account.code = code;
        t_account.username = t_account_temp.username;
        t_account.password = t_account_temp.password;
        t_account.avatar = get_avatar_by_number(avatar); // make check by id (custom file or builtin)
        t_account.team = team;
        t_account.theme = theme;
        t_account.background = bg;

        fill_pokemon();     // Filling random data on home tab
        t_leftbar.active = 1;   // Active button in leftbar
        gtk_widget_destroy(GTK_WIDGET(t_application.auth));
        load_providers();
        build_all(&t_application.messanger);  // Main builder function
        gtk_widget_show_all(t_application.messanger);          // Showing window
        gtk_widget_hide(GTK_WIDGET(t_leftbar.msg_scr));     // Hiding messanger tab
        gtk_widget_hide(GTK_WIDGET(t_leftbar.settings_scr));// Hiding settings tab
    }
    else {
        printf("Login error!\n");
    }
    mx_strdel(&result);
    mx_strdel(&json_string);
    mx_strdel(&msg_data.content_final);
    cJSON_Delete(json);
    cJSON_Delete(response);

}

void reg_send_request() {
    cJSON *json = cJSON_CreateObject();
    cJSON *json_reg_user = cJSON_CreateObject();
    cJSON_AddStringToObject(json_reg_user, "username", t_account.username);
    cJSON_AddStringToObject(json_reg_user, "name", t_account.name);
    cJSON_AddStringToObject(json_reg_user, "code", t_account.code);
    cJSON_AddStringToObject(json_reg_user, "password", t_account.password);
    cJSON_AddItemToObject(json, "register_user", json_reg_user);
    char *json_string = cJSON_PrintUnformatted(json);
    printf("%s\n", json_string);
    char *result = NULL;
    ssl_client(json_string, &result);
    cJSON *response = cJSON_Parse(result);
    if (cJSON_IsNull(response) || !strcmp(result, "")) {
        printf("Registration error!\n");
    }
    else {
        int user_id = cJSON_GetNumberValue(cJSON_GetObjectItem(response, "user_id"));
        t_account.id = user_id;
        if (user_id == -1) {
            printf("This username is already occuped, choose another one\n");
        }
        else {
            printf("My new user id: %d\n", user_id);
        }
    }
    mx_strdel(&result);
    mx_strdel(&json_string);
    mx_strdel(&msg_data.content_final);
    cJSON_Delete(json);
    cJSON_Delete(response);
}

void reg_butt_click(GtkWidget *widget){
    if(widget) {}

    t_account_temp.username = mx_del_extra_spaces(t_account_temp.username);
    t_account_temp.name = mx_del_extra_spaces(t_account_temp.name);
    
    if(t_account_temp.username == NULL \
    || !strcmp(t_account_temp.username, "") \
    || t_account_temp.name == NULL \
    || !strcmp(t_account_temp.name, "")
    || t_account_temp.password == NULL \
    || !strcmp(t_account_temp.password, "")
    || t_account_temp.repass == NULL \
    || !strcmp(t_account_temp.repass, "")
    || strlen(t_account_temp.password) < 5 \
    || strcmp(t_account_temp.repass, t_account_temp.password))
        return;
    
    t_account.avatar = t_avatar.avatar_generated;
    t_account.username = t_account_temp.username;
    t_account.name = t_account_temp.name;
    if(t_account_temp.code == NULL || !strcmp(t_account_temp.code, "")) t_account.code = "000000000000";
    else t_account.code = mx_strjoin(t_account_temp.code, "\0");
    t_account.team = t_account_temp.team;
    t_account.password = t_account_temp.password;
    t_account.theme = 2;
    t_account.background = 1;
    t_account.id = 0;
    
    printf("REGISTERED:\nUser = %s\n", t_account.username);
    printf("Name = %s\n", t_account.name);
    printf("Code = %s\n", t_account.code);
    printf("Pass = %s\n", t_account.password);
    printf("Team = %hd\n", t_account.team);

    reg_send_request();
    printf("-- %d\n", t_account.id);
    if (t_account.id <= 0) {
        // Appears an error message on the screen
        return;
    }

    fill_pokemon();     // Filling random data on home tab
    t_leftbar.active = 1;   // Active button in leftbar
    gtk_widget_destroy(GTK_WIDGET(t_application.auth));
    load_providers();
    build_all(&t_application.messanger);  // Main builder function
    gtk_widget_show_all(t_application.messanger);          // Showing window
    gtk_widget_hide(GTK_WIDGET(t_leftbar.msg_scr));     // Hiding messanger tab
    gtk_widget_hide(GTK_WIDGET(t_leftbar.settings_scr));// Hiding settings tab
}
