#include "../inc/client.h"

void login_button_click(GtkWidget *widget, GdkEventButton *event, gpointer main_area)
{
    if(widget){}
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
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

void mystic_event_button_click(GtkWidget *widget, GdkEventButton *event, gpointer menu)
{
    if(event->type == GDK_BUTTON_PRESS && event->button == 1)
    {
        GList *parent = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)menu));
        while(parent) {
            gtk_widget_unset_state_flags(GTK_WIDGET(parent->data), GTK_STATE_FLAG_LINK);
            parent = parent->next;
        }
        g_list_free(g_steal_pointer(&parent));

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account_temp.team = 1;
    }
}

void instinct_event_button_click(GtkWidget *widget, GdkEventButton *event, gpointer menu)
{
    if(widget){}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1)
    {
        GList *parent = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)menu));
        while(parent) {
            gtk_widget_unset_state_flags(GTK_WIDGET(parent->data), GTK_STATE_FLAG_LINK);
            parent = parent->next;
        }
        g_list_free(g_steal_pointer(&parent));

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account_temp.team = 2;
    }
}

void valor_event_button_click(GtkWidget *widget, GdkEventButton *event, gpointer menu)
{
    if(widget){}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1)
    {
        GList *parent = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)menu));
        while(parent) {
            gtk_widget_unset_state_flags(GTK_WIDGET(parent->data), GTK_STATE_FLAG_LINK);
            parent = parent->next;
        }
        g_list_free(g_steal_pointer(&parent));
        
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account_temp.team = 3;
    }
}

void login_butt_click(GtkWidget *widget){
    if(widget) {}

    t_account_temp.username = mx_del_extra_spaces(t_account_temp.username);
    t_account_temp.name = mx_del_extra_spaces(t_account_temp.name);

    if(t_account_temp.username == NULL \
    || !strcmp(t_account_temp.username, "") \
    || t_account_temp.password == NULL \
    || !strcmp(t_account_temp.password, "")
    || strlen(t_account_temp.password) < 5)
        return;

    cJSON *json = cJSON_CreateObject();
    cJSON *json_login_user = cJSON_CreateObject();
    cJSON_AddStringToObject(json_login_user, "username", t_account_temp.username);
    cJSON_AddStringToObject(json_login_user, "password", t_account_temp.password);
    cJSON_AddItemToObject(json, "login_user", json_login_user);
    char *json_string = cJSON_PrintUnformatted(json);
    // printf("%s\n", json_string);
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
        // printf("My old user id: %d\n", user_id);
        // printf("My name: %s\n", name);
        // printf("My code: %s\n", code);
        // printf("My team: %d\n", team);
        // printf("My theme: %d\n", theme);
        // printf("My bg: %d\n", bg);
        t_account.id = user_id;
        t_account.name = name;
        t_account.code = code;
        t_account.username = strdup(t_account_temp.username);
        t_account.password = strdup(t_account_temp.password);
        t_account.avatar = get_avatar_by_number(avatar); // make check by id (custom file or builtin)
        t_account.team = team;
        t_account.theme = theme;
        t_account.background = bg;

        cJSON *json_online = cJSON_CreateObject();
        cJSON *json_user_id = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_user_id, "user_id", user_id);
        cJSON_AddItemToObject(json_online, "update_user_online", json_user_id);
        char *json_online_string = cJSON_PrintUnformatted(json_online);
        // printf("%s\n", json_online_string);
        char *result2 = NULL;
        ssl_client(json_online_string, &result2);
        mx_strdel(&json_online_string);
        mx_strdel(&result2);
        cJSON_Delete(json_online);

        fill_pokemon();     // Filling random data on home tab
        t_screen.active = 1;   // Active button in leftbar
        gtk_widget_destroy(GTK_WIDGET(t_application.auth));
        load_providers();
        build_all(&t_application.messanger);  // Main builder function
        gtk_widget_show_all(t_application.messanger);          // Showing window
        gtk_widget_hide(GTK_WIDGET(t_screen.msg_scr));     // Hiding messanger tab
        gtk_widget_hide(GTK_WIDGET(t_screen.settings_scr));// Hiding settings tab
    }
    else {
        create_notification(t_application.auth, "Login error!", 1, 430, 160, 420, 10);
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
    cJSON_AddNumberToObject(json_reg_user, "team", t_account.team);
    cJSON_AddItemToObject(json, "register_user", json_reg_user);
    char *json_string = cJSON_PrintUnformatted(json);
    // ("%s\n", json_string);
    char *result = NULL;
    ssl_client(json_string, &result);
    cJSON *response = cJSON_Parse(result);
    if (cJSON_IsNull(response) || !strcmp(result, "")) {
        printf("Registration error!\n");
    }
    else {
        int user_id = cJSON_GetNumberValue(cJSON_GetObjectItem(response, "user_id"));
        t_account.id = user_id;
        if (user_id > 0) {
            update_user_avatar(t_avatar.avatar_num);
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
    || strlen(t_account_temp.password) < 5)
        return;

    if(strcmp(t_account_temp.repass, t_account_temp.password)){
        create_notification(t_application.auth, "Passwords do not match!", 1, 430, 30, 420, 10);
        return;
    }

    if(t_account_temp.team == 0){
        create_notification(t_application.auth, "Select a team!", 1, 430, 30, 420, 10);
        return;
    }

    t_account.avatar = t_avatar.avatar_generated;
    t_account.username = strdup(t_account_temp.username);
    t_account.name = t_account_temp.name;
    if(t_account_temp.code == NULL || !strcmp(t_account_temp.code, "")) t_account.code = "000000000000";
    else t_account.code = mx_strjoin(t_account_temp.code, "\0");
    t_account.team = t_account_temp.team;
    t_account.password = strdup(t_account_temp.password);
    t_account.theme = 2;
    t_account.background = 1;
    t_account.id = 0;

    // printf("REGISTERED:\nUser = %s\n", t_account.username);
    // printf("Name = %s\n", t_account.name);
    // printf("Code = %s\n", t_account.code);
    // printf("Pass = %s\n", t_account.password);
    // printf("Team = %hd\n", t_account.team);

    reg_send_request();
    if (t_account.id == 0) {
        create_notification(t_application.auth, "This username is already taken!", 1, 430, 30, 420, 10);
        return;
    }

    fill_pokemon();     // Filling random data on home tab
    t_screen.active = 1;   // Active button in leftbar
    gtk_widget_destroy(GTK_WIDGET(t_application.auth));
    load_providers();
    build_all(&t_application.messanger);  // Main builder function
    gtk_widget_show_all(t_application.messanger);          // Showing window
    gtk_widget_hide(GTK_WIDGET(t_screen.msg_scr));     // Hiding messanger tab
    gtk_widget_hide(GTK_WIDGET(t_screen.settings_scr));// Hiding settings tab
}
