#include "../inc/client.h"

void adduser_click(GtkWidget *widget, GdkEventButton *event, gpointer search_field) {
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1)
    {
        char *name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)search_field)));
        if(name != NULL)
            name = mx_del_extra_spaces(name);
        if(!strcmp(name, "") || !strcmp(name, " "))
            return;

        // проверить имя пользователя name на существование
        printf("Added: %s\n", name);
        int user_id = 0, avatar = 0;
        new_group = malloc(sizeof(t_new_group));
        new_group->count = 0;
        new_group->users_id = NULL;
        new_group->title = NULL;
        if (!add_user_to_group(name, &user_id, &avatar)) {
            create_notification(t_application.main_area, "Invalid username!", 1, LEFTBAR_W+10, 58, 340, 10);
            return;
        }
        create_group();
        gtk_entry_set_text(GTK_ENTRY(search_field), "");

        // Получить данные пользователя: аватар, имя, статус
        chat_push_back(&tchatlist, name, avatar, true);  // TODO status
        t_chat_list *copy = tchatlist;
        for(;copy->next; copy = copy->next);
        GtkWidget *single = add_single(copy);
        gtk_box_pack_start(GTK_BOX(t_msg.chatlist), single, FALSE, FALSE, 3);
        gtk_widget_show_all(GTK_WIDGET(t_msg.chatlist));

        g_signal_connect(G_OBJECT(single), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
        g_signal_connect(G_OBJECT(single), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
        g_signal_connect(G_OBJECT(single), "button_press_event", G_CALLBACK(person_click), NULL);
    }
}

void attach_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    char *path = NULL;
    if(event->type == GDK_BUTTON_PRESS && event->button == 1)
    {
        GtkWidget *dialog;
        GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
        gint res;

        dialog = gtk_file_chooser_dialog_new("Select an image (< 3 Mb)", GTK_WINDOW(t_application.window), action,  "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
        GtkFileFilter *filter = gtk_file_filter_new();
        gtk_file_filter_add_pattern(filter, "*.png");
        gtk_file_filter_add_pattern(filter, "*.jpg");
        gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(dialog), filter);

        res = gtk_dialog_run (GTK_DIALOG (dialog));
        if (res == GTK_RESPONSE_ACCEPT) {
            char *filename;
            GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
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
            path = strdup(backward);
            mx_strdel(&backward);
            for (int i = 0; path_split[i]; i++)
                free(path_split[i]);
            free(path_split);
            free(filename);
        }
        gtk_widget_destroy(dialog);
    }
    if(path == NULL)
        return;
    struct stat buf;
    stat(path, &buf);
    if (buf.st_size < 3145728) // 3mb
        new_outgoing_embedded(t_chat.chat_screen, path);
}

void send_click(GtkWidget *widget, GdkEventButton *event, GtkWidget *entry_text) {
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1 && msg_data.chat_id)
    {
        msg_data.content = mx_strtrim(msg_data.content);
        if(msg_data.content == NULL || !strcmp(msg_data.content, "") || !strcmp(msg_data.content, " "))
            return;
        msg_data.sent = true;
        if (msg_data.date) {
            mx_strdel(&msg_data.date_prev);
            msg_data.date_prev = strdup(msg_data.date);
        }
        mx_strdel(&msg_data.date);
        msg_data.date = mx_str_getdate();
        mx_strdel(&msg_data.time);
        msg_data.time = mx_str_gettime();
        msg_data.content_final = strdup(msg_data.content);
        pthread_t thread = NULL;
        pthread_create(&thread, NULL, send_message, NULL);
        new_outgoing_message(t_chat.chat_screen);   // Передавать как параметры: имя, фото, текст сообщения
        gtk_entry_set_text(GTK_ENTRY(entry_text), "");
        msg_data.content = NULL;
        msg_data.sent = false;
    }
}

void send_press(GtkWidget *widget) {
    if(msg_data.chat_id)
    {
        msg_data.content = mx_strtrim(msg_data.content);
        if(msg_data.content == NULL || !strcmp(msg_data.content, "") || !strcmp(msg_data.content, " "))
            return;
        msg_data.sent = true;
        if (msg_data.date) {
            mx_strdel(&msg_data.date_prev);
            msg_data.date_prev = strdup(msg_data.date);
        }
        mx_strdel(&msg_data.date);
        msg_data.date = mx_str_getdate();
        mx_strdel(&msg_data.time);
        msg_data.time = mx_str_gettime();
        msg_data.content_final = strdup(msg_data.content);
        pthread_t thread = NULL;
        pthread_create(&thread, NULL, send_message, NULL);
        new_outgoing_message(t_chat.chat_screen);   // Передавать как параметры: имя, фото, текст сообщения
        gtk_entry_set_text(GTK_ENTRY(widget), "");
        msg_data.sent = false;
    }
}

void entry_text_change_event(GtkWidget *widget) {
    msg_data.content = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget)));
}

void sticker_click(GtkWidget *widget, GdkEventButton *event, GtkWidget *main) {
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1)
        create_stickerlist(main);
}

void person_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1 && !upd_data.busy)
    {
        upd_data.suspend = true;
        gtk_container_forall(GTK_CONTAINER(t_chat.chat_screen), (GtkCallback)gtk_widget_destroy, NULL);
        GList *parent = gtk_container_get_children(GTK_CONTAINER(widget)); // GList *parent_c = parent;
        GList *children = gtk_container_get_children(GTK_CONTAINER(parent->data)); // GList *children_c = children;
        children = children->next;
        char* chosen = (char*)gtk_label_get_text(GTK_LABEL(children->data));
        printf("%s\n", chosen);
        g_list_free(g_steal_pointer(&children)); // g_list_free(children_c); // 
        g_list_free(g_steal_pointer(&parent)); // g_list_free(parent_c); // 
        for (int i = 0; i < upd_data.count; i++)
            if (upd_data.chats_id[i] == msg_data.chat_id)
                upd_data.messages_id[i] = 0;
        msg_data.chat_id = 1; // TODO test
        upd_data.suspend = false;
    }
    if(event->type == GDK_BUTTON_PRESS && event->button == 3)
    {
        GList *parent = gtk_container_get_children(GTK_CONTAINER(widget)); // GList *parent_c = parent;
        GList *children = gtk_container_get_children(GTK_CONTAINER(parent->data)); // GList *children_c = children;
        children = children->next;
        char* username = (char*)gtk_label_get_text(GTK_LABEL(children->data));

        bool status = false;
        children = children->next;
        if(children != NULL)
            status = true;

        creator_userprofile(t_msg.main, username, status);
        g_list_free(g_steal_pointer(&children)); // g_list_free(children_c); // 
        g_list_free(g_steal_pointer(&parent)); // g_list_free(parent_c); // 
    }
}

void msggroup_click(GtkWidget *widget, GdkEventButton *event, GtkWidget *main) {
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1)
        creator_group(main);
}
