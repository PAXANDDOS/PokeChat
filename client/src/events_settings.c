#include "../inc/client.h"

/* =========== SERVER REQUESTS ZONE ===========*/

static void update_user_main() {
    cJSON *json = cJSON_CreateObject();
    cJSON *json_fields = cJSON_CreateObject();
    cJSON_AddNumberToObject(json_fields, "user_id", t_account.id);
    cJSON_AddStringToObject(json_fields, "username", t_account.username);
    cJSON_AddStringToObject(json_fields, "name", t_account.name);
    cJSON_AddStringToObject(json_fields, "code", t_account.code);
    cJSON_AddStringToObject(json_fields, "password", t_account.password);
    cJSON_AddItemToObject(json, "update_user_main", json_fields);
    char *json_string = cJSON_PrintUnformatted(json);
    char *result = NULL;
    ssl_client(json_string, &result);
    mx_strdel(&result);
    cJSON_Delete(json);
}

static void update_user_team() {
    cJSON *json = cJSON_CreateObject();
    cJSON *json_fields = cJSON_CreateObject();
    cJSON_AddNumberToObject(json_fields, "user_id", t_account.id);
    cJSON_AddNumberToObject(json_fields, "team", t_account.team);
    cJSON_AddItemToObject(json, "update_user_team", json_fields);
    char *json_string = cJSON_PrintUnformatted(json);
    char *result = NULL;
    ssl_client(json_string, &result);
    mx_strdel(&result);
    cJSON_Delete(json);
}

static void update_user_theme() {
    cJSON *json = cJSON_CreateObject();
    cJSON *json_fields = cJSON_CreateObject();
    cJSON_AddNumberToObject(json_fields, "user_id", t_account.id);
    cJSON_AddNumberToObject(json_fields, "theme", t_account.theme);
    cJSON_AddItemToObject(json, "update_user_theme", json_fields);
    char *json_string = cJSON_PrintUnformatted(json);
    char *result = NULL;
    ssl_client(json_string, &result);
    mx_strdel(&result);
    cJSON_Delete(json);
}

static void update_user_background() {
    cJSON *json = cJSON_CreateObject();
    cJSON *json_fields = cJSON_CreateObject();
    cJSON_AddNumberToObject(json_fields, "user_id", t_account.id);
    cJSON_AddNumberToObject(json_fields, "background", t_account.background);
    cJSON_AddItemToObject(json, "update_user_background", json_fields);
    char *json_string = cJSON_PrintUnformatted(json);
    char *result = NULL;
    ssl_client(json_string, &result);
    mx_strdel(&result);
    cJSON_Delete(json);
}

/* ========== GTK WIDGET EVENTS ZONE ========= */

void exit_button_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1)
    {
        gtk_widget_destroy(GTK_WIDGET(t_application.messanger));
        gtk_window_close(GTK_WINDOW(t_application.window));
    }
}

void add_button_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1)
    {
        GtkWidget *dialog;

        GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
        gint res;

        dialog = gtk_file_chooser_dialog_new("Choose an image", GTK_WINDOW(t_application.window), action,  "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
        GtkFileFilter *filter = gtk_file_filter_new();
        gtk_file_filter_add_pattern(filter, "*.png");
        gtk_file_filter_add_pattern(filter, "*.jpg");
        gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(dialog), filter);

        res = gtk_dialog_run (GTK_DIALOG (dialog));
        if (res == GTK_RESPONSE_ACCEPT) {
            char *filename;
            GtkFileChooser *chooser = NULL;
            chooser = GTK_FILE_CHOOSER(dialog);
            filename = gtk_file_chooser_get_filename(chooser);
            char *pwd = getenv("PWD");
            char **path_split = mx_strsplit(pwd, '/');
            int words_count = 0;
            while (path_split[++words_count]);
            char *backward = strdup("");
            for (int i = 0; i < words_count; i++) {
                backward = mx_strrejoin(backward, "..");
                if (i != words_count - 1)
                    backward = mx_strrejoin(backward, "/");
            }
            backward = mx_strrejoin(backward, filename);
            struct stat buf;
            stat(backward, &buf);
            if (buf.st_size < 3145728) // 3mb
                t_account.avatar = strdup(backward);
            else create_notification(t_application.messanger, "Your file is too big!", 1, WINDOW_WIDTH-216, 10, 200, 20);
            mx_strdel(&backward);
            for (int i = 0; path_split[i]; i++)
                free(path_split[i]);
            free(path_split);
            free(filename);
        }

        gtk_widget_destroy (dialog);
    }
}

void gallery_button_click(GtkWidget *widget, GdkEventButton *event, gpointer main) {
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1)
        create_gallery((GtkWidget*)main);
}

//

void username_field_change_event(GtkWidget *widget) {
    if(strlen(gtk_entry_get_text(GTK_ENTRY(widget))) > 0)
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK);
    else
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);

    t_account_temp.username = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget)));
}

void firstname_field_change_event(GtkWidget *widget) {
    if(strlen(gtk_entry_get_text(GTK_ENTRY(widget))) > 0)
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK);
    else
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);

    t_account_temp.name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget)));
}

void firstname_input_event(GtkEditable *editable, const gchar *text, gint length, gint *position, gpointer data)
{
    if(position || data) {}
    int i;
    for (i = 0; i < length; i++) {
        if (!isalpha(text[i])) {
            g_signal_stop_emission_by_name(G_OBJECT(editable), "insert-text");
            return;
        }
    }
}

void code_field_change_event(GtkWidget *widget) {
    if(strlen(gtk_entry_get_text(GTK_ENTRY(widget))) > 0)
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK);
    else
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);

    t_account_temp.code = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget)));
}

void code_input_event(GtkEditable *editable, const gchar *text, gint length, gint *position, gpointer data)
{
    if(position || data) {}
    int i;
    for (i = 0; i < length; i++) {
        if (!isdigit(text[i])) {
            g_signal_stop_emission_by_name(G_OBJECT(editable), "insert-text");
            return;
        }
    }
}

void all_input_event(GtkEditable *editable, const gchar *text, gint length, gint *position, gpointer data)
{
    if(position || data) {}
    int i;
    for (i = 0; i < length; i++) {
        if (!isascii(((int)text[i]))) {
            g_signal_stop_emission_by_name(G_OBJECT(editable), "insert-text");
            return;
        }
    }
}

void pass_field_change_event(GtkWidget *widget) {
    if(strlen(gtk_entry_get_text(GTK_ENTRY(widget))) <= 4){
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE);
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
    }
    else if(4 < strlen(gtk_entry_get_text(GTK_ENTRY(widget))) && 8 >= strlen(gtk_entry_get_text(GTK_ENTRY(widget)))) {
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK);
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE, TRUE);
    }
    else {
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_ACTIVE);
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK);
    }
    t_account_temp.password = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget)));
}

void repass_field_change_event(GtkWidget *widget) {
    t_account_temp.repass = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget)));
    if(!strcmp(t_account_temp.repass, t_account_temp.password))
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK);
    else
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
}

void apply_butt_click(GtkWidget *widget){
    if(widget) {}
    t_account_temp.username = mx_del_extra_spaces(t_account_temp.username);
    t_account_temp.name = mx_del_extra_spaces(t_account_temp.name);
    t_account_temp.code = mx_del_extra_spaces(t_account_temp.code);

    if(t_account_temp.username == NULL || !strcmp(t_account_temp.username, "")) {
        create_notification(t_application.messanger, "Incorrect username!", 1, WINDOW_WIDTH-216, 10, 200, 20);
        return;
    }

    if(t_account_temp.name == NULL || !strcmp(t_account_temp.name, "")) {
        create_notification(t_application.messanger, "Incorrect name!", 1, WINDOW_WIDTH-216, 10, 200, 20);
        return;
    }

    if(strlen(t_account_temp.code) < 12 && strlen(t_account_temp.code) > 0) {
        create_notification(t_application.messanger, "Incorrect code!", 1, WINDOW_WIDTH-216, 10, 200, 20);
        return;
    }

    t_account.username = t_account_temp.username;
    t_account.name = t_account_temp.name;
    if(t_account_temp.code == NULL && !strcmp(t_account_temp.code, ""))
        t_account.code = "000000000000";
    else t_account.code = t_account_temp.code;

    if(t_account_temp.password != NULL && t_account_temp.repass != NULL \
    && strcmp(t_account_temp.password, "") && strcmp(t_account_temp.repass, "")) {
        if(strlen(t_account_temp.password) > 4 && !strcmp(t_account_temp.repass, t_account_temp.password)){
            t_account.password = t_account_temp.password;
        }
        else { create_notification(t_application.messanger, "Passwords do not match!", 1, WINDOW_WIDTH-216, 10, 200, 20); return; }
    }

    gtk_label_set_text(GTK_LABEL(t_settings.username), t_account.username);
    gtk_label_set_text(GTK_LABEL(t_settings.name), t_account.name);
    create_notification(t_application.messanger, "Account data updated!", 0, WINDOW_WIDTH-216, 10, 200, 20);
    update_user_main();
}

//
void team_mystic_click(GtkWidget *widget, GdkEventButton *event, gpointer menu) {
    if(t_account.team == 1) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GList *parent = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)menu));
        while(parent) {
            gtk_widget_unset_state_flags(GTK_WIDGET(parent->data), GTK_STATE_FLAG_LINK);
            parent = parent->next;
        }
        g_list_free(g_steal_pointer(&parent));
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account.team = 1;
    }
    update_user_team();

}

void team_instinct_click(GtkWidget *widget, GdkEventButton *event, gpointer menu) {
    if(t_account.team == 2) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GList *parent = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)menu));
        while(parent) {
            gtk_widget_unset_state_flags(GTK_WIDGET(parent->data), GTK_STATE_FLAG_LINK);
            parent = parent->next;
        }
        g_list_free(g_steal_pointer(&parent));

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account.team = 2;
    }
    update_user_team();
}

void team_valor_click(GtkWidget *widget, GdkEventButton *event, gpointer menu) {
    if(t_account.team == 3) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GList *parent = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)menu));
        while(parent) {
            gtk_widget_unset_state_flags(GTK_WIDGET(parent->data), GTK_STATE_FLAG_LINK);
            parent = parent->next;
        }
        g_list_free(g_steal_pointer(&parent));

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account.team = 3;
    }
    update_user_team();
}

//
void theme_light_click(GtkWidget *widget, GdkEventButton *event, gpointer menu) {
    if(t_account.theme == 1) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GList *parent = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)menu));
        while(parent) {
            gtk_widget_unset_state_flags(GTK_WIDGET(parent->data), GTK_STATE_FLAG_LINK);
            parent = parent->next;
        }
        g_list_free(g_steal_pointer(&parent));

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account.theme = 1;
        g_object_unref(G_OBJECT(t_providers.theme));
        t_providers.theme = gtk_css_provider_new();
        gtk_css_provider_load_from_path(t_providers.theme, "client/data/css/themes/theme_light.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.theme), GTK_STYLE_PROVIDER_PRIORITY_USER);
        if(t_account.background == 1)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_light/chatbg1.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.background == 2)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_light/chatbg2.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.background == 3)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_light/chatbg3.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.background == 4)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_light/chatbg4.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
    }
    update_user_theme();
}

void theme_default_click(GtkWidget *widget, GdkEventButton *event, gpointer menu) {
    if(t_account.theme == 2) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GList *parent = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)menu));
        while(parent) {
            gtk_widget_unset_state_flags(GTK_WIDGET(parent->data), GTK_STATE_FLAG_LINK);
            parent = parent->next;
        }
        g_list_free(g_steal_pointer(&parent));

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account.theme = 2;
        g_object_unref(G_OBJECT(t_providers.theme));
        t_providers.theme = gtk_css_provider_new();
        gtk_css_provider_load_from_path(t_providers.theme, "client/data/css/themes/theme_default.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.theme), GTK_STYLE_PROVIDER_PRIORITY_USER);
        if(t_account.background == 1)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg/chatbg1.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.background == 2)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg/chatbg2.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.background == 3)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg/chatbg3.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.background == 4)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg/chatbg4.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
    }
    update_user_theme();
}

void theme_dark_click(GtkWidget *widget, GdkEventButton *event, gpointer menu) {
    if(t_account.theme == 3) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GList *parent = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)menu));
        while(parent) {
            gtk_widget_unset_state_flags(GTK_WIDGET(parent->data), GTK_STATE_FLAG_LINK);
            parent = parent->next;
        }
        g_list_free(g_steal_pointer(&parent));

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account.theme = 3;
        g_object_unref(G_OBJECT(t_providers.theme));
        t_providers.theme = gtk_css_provider_new();
        gtk_css_provider_load_from_path(t_providers.theme, "client/data/css/themes/theme_dark.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.theme), GTK_STYLE_PROVIDER_PRIORITY_USER);
        if(t_account.background == 1)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_dark/chatbg1.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.background == 2)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_dark/chatbg2.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.background == 3)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_dark/chatbg3.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.background == 4)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_dark/chatbg4.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
    }
    update_user_theme();
}

//

void bg1_preview_click(GtkWidget *widget, GdkEventButton *event, gpointer menu) {
    if(t_account.background == 1) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GList *parent = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)menu));
        while(parent) {
            gtk_widget_unset_state_flags(GTK_WIDGET(parent->data), GTK_STATE_FLAG_LINK);
            parent = parent->next;
        }
        g_list_free(g_steal_pointer(&parent));

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account.background = 1;
        g_object_unref(G_OBJECT(t_providers.chat));
        if(t_account.theme == 1)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_light/chatbg1.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.theme == 2)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg/chatbg1.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.theme == 3)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_dark/chatbg1.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
    }
    update_user_background();
}

void bg2_preview_click(GtkWidget *widget, GdkEventButton *event, gpointer menu) {
    if(t_account.background == 2) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GList *parent = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)menu));
        while(parent) {
            gtk_widget_unset_state_flags(GTK_WIDGET(parent->data), GTK_STATE_FLAG_LINK);
            parent = parent->next;
        }
        g_list_free(g_steal_pointer(&parent));

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account.background = 2;
        g_object_unref(G_OBJECT(t_providers.chat));
        if(t_account.theme == 1)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_light/chatbg2.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.theme == 2)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg/chatbg2.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.theme == 3)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_dark/chatbg2.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
    }
    update_user_background();
}

void bg3_preview_click(GtkWidget *widget, GdkEventButton *event, gpointer menu) {
    if(t_account.background == 3) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GList *parent = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)menu));
        while(parent) {
            gtk_widget_unset_state_flags(GTK_WIDGET(parent->data), GTK_STATE_FLAG_LINK);
            parent = parent->next;
        }
        g_list_free(g_steal_pointer(&parent));

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account.background = 3;
        g_object_unref(G_OBJECT(t_providers.chat));
        if(t_account.theme == 1)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_light/chatbg3.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.theme == 2)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg/chatbg3.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.theme == 3)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_dark/chatbg3.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
    }
    update_user_background();
}

void bg4_preview_click(GtkWidget *widget, GdkEventButton *event, gpointer menu) {
    if(t_account.background == 4) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GList *parent = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)menu));
        while(parent) {
            gtk_widget_unset_state_flags(GTK_WIDGET(parent->data), GTK_STATE_FLAG_LINK);
            parent = parent->next;
        }
        g_list_free(g_steal_pointer(&parent));

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account.background = 4;
        g_object_unref(G_OBJECT(t_providers.chat));
        if(t_account.theme == 1)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_light/chatbg4.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.theme == 2)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg/chatbg4.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if(t_account.theme == 3)
        {
            t_providers.chat = gtk_css_provider_new();
            gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_dark/chatbg4.css", NULL);
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
    }
    update_user_background();
}
