#include "../inc/client.h"

void display_new_chat() {
    t_chat_list *p = chatlist;
    for(;p->next; p = p->next);
    GtkWidget *single = add_single(p);
    gtk_box_pack_start(GTK_BOX(t_msg.chatlist), single, FALSE, FALSE, 3);
    gtk_box_reorder_child(GTK_BOX(t_msg.chatlist), single, 0);
    gtk_widget_show_all(GTK_WIDGET(t_msg.chatlist));

    g_signal_connect(G_OBJECT(single), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(single), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(single), "button_press_event", G_CALLBACK(person_click), NULL);
}

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
        // printf("Added: %s\n", name);
        int user_id = 0, avatar = 0;
        new_group = malloc(sizeof(t_new_group));
        new_group->count = 0;
        new_group->users_id = NULL;
        new_group->title = NULL;
        if (!add_user_to_group(name, &user_id, &avatar)) {
            create_notification(t_application.messanger, "Invalid username!", 1, LEFTBAR_W+10, 58, 340, 10);
            return;
        }
        gtk_entry_set_text(GTK_ENTRY(search_field), "");

        int chat_id = 0;
        create_group(&chat_id);
        if (!chat_id) {
            create_notification(t_application.messanger, "You already have DM with this user!", 1, LEFTBAR_W+10, 58, 340, 10);
            return;
        }
        // t_chat_data *chat = malloc(sizeof(t_chat_data));
        // chat->user = malloc(sizeof(t_user));
        // chat->chat_id = chat_id;
        // get_chat(chat);
        // get_user(chat->user);
        // chat_push_back(&chatlist, chat);
        // free_user(chat->user);
        // mx_strdel(&chat->title);
        // free(chat);

        // display_new_chat();
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

        res = gtk_dialog_run(GTK_DIALOG(dialog));
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
    if (buf.st_size < 3145728) { // 3mb
        photo_data.chat_id = msg_data.chat_id;
        photo_data.photo_path = strdup(path);
        pthread_t thread = NULL;
        pthread_create(&thread, NULL, send_photo, NULL);
        new_outgoing_embedded(t_msg.chat_screen, path);
    }
    else
        create_notification(t_application.messanger, "Your file is too big!", 1, WINDOW_WIDTH-216, 10, 200, 20);
    free(path);
}

void send_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1 && msg_data.chat_id)
    {
        msg_data.content = mx_strtrim(msg_data.content);
        if(msg_data.content == NULL || !strcmp(msg_data.content, "") || !strcmp(msg_data.content, " "))
            return;
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
        new_outgoing_message(t_msg.chat_screen);   // Передавать как параметры: имя, фото, текст сообщения
        gtk_entry_set_text(GTK_ENTRY(t_msg.entry), "");
        msg_data.content = NULL;

        GList *inner = gtk_container_get_children(GTK_CONTAINER(t_msg.chatlist));
            while(inner != NULL)
            {
                GtkStateFlags flags = gtk_widget_get_state_flags(GTK_WIDGET(inner->data));
                if (flags & GTK_STATE_FLAG_LINK)
                    gtk_box_reorder_child(GTK_BOX(t_msg.chatlist), inner->data, 0);
                inner = inner->next;
            }
        g_list_free(g_steal_pointer(&inner));
    }
    else if(!msg_data.chat_id)
        create_notification(t_application.messanger, "Select recipient first!", 1, WINDOW_WIDTH-206, WINDOW_HEIGHT-ENTRY_H-28, 200, 20);
}

void send_press(GtkWidget *widget) {
    if(msg_data.chat_id)
    {
        msg_data.content = mx_strtrim(msg_data.content);
        if(msg_data.content == NULL || !strcmp(msg_data.content, "") || !strcmp(msg_data.content, " "))
            return;
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
        new_outgoing_message(t_msg.chat_screen);   // Передавать как параметры: имя, фото, текст сообщения
        gtk_entry_set_text(GTK_ENTRY(widget), "");
    }
    else create_notification(t_application.messanger, "Select recipient first!", 1, WINDOW_WIDTH-206, WINDOW_HEIGHT-ENTRY_H-28, 200, 20);
}

void entry_text_change_event(GtkWidget *widget) {
    msg_data.content = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget)));
}

void sticker_click(GtkWidget *widget, GdkEventButton *event, gpointer main) {
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1)
        create_stickerlist((GtkWidget*)main);
}

void person_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1 && !upd_data.busy)
    {
        GList *parent = gtk_container_get_children(GTK_CONTAINER(widget));
        GList *children = gtk_container_get_children(GTK_CONTAINER(parent->data));
        children = children->next;

        if(strcmp(t_msg.current, (char*)gtk_label_get_text(GTK_LABEL(children->data))))
        {
            gtk_entry_set_text(GTK_ENTRY(t_msg.entry), "");
            msg_data.content = NULL;
            upd_data.suspend = true;
            gtk_container_forall(GTK_CONTAINER(t_msg.chat_screen), (GtkCallback)gtk_widget_destroy, NULL);
        }

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        if(strcmp(t_msg.current, "here...")) {
            if(strcmp(t_msg.current, (char*)gtk_label_get_text(GTK_LABEL(children->data)))) {
                GList *inner = gtk_container_get_children(GTK_CONTAINER(t_msg.chatlist));
                while(inner != NULL)
                {
                    GList *inner_child = gtk_container_get_children(GTK_CONTAINER(inner->data));
                    GList *inner_child2 = gtk_container_get_children(GTK_CONTAINER(inner_child->data));
                    inner_child2 = inner_child2->next;
                    char* chosen = (char*)gtk_label_get_text(GTK_LABEL(inner_child2->data));
                    g_list_free(g_steal_pointer(&inner_child2));
                    g_list_free(g_steal_pointer(&inner_child));
                    if(!strcmp(t_msg.current, chosen)) {
                        gtk_widget_unset_state_flags(GTK_WIDGET(inner->data), GTK_STATE_FLAG_LINK);
                        break;
                    }
                    inner = inner->next;
                }
                g_list_free(g_steal_pointer(&inner));
            }
        }

        if(strcmp(t_msg.current, (char*)gtk_label_get_text(GTK_LABEL(children->data))))
        {
            t_msg.current = (char*)gtk_label_get_text(GTK_LABEL(children->data));

            children = children->next;
            char* chat_id_from_label = (char*)gtk_label_get_text(GTK_LABEL(children->data));
            children = children->next;
            // char* user_id_from_label = (char*)gtk_label_get_text(GTK_LABEL(children->data));
            for (int i = 0; i < upd_data.count; i++)
                if (upd_data.chats_id[i] == msg_data.chat_id) {
                    upd_data.messages_id[i] = 0;
                    break;
                }
            msg_data.chat_id = atoi(chat_id_from_label);
            upd_data.suspend = false;
        }

        g_list_free(g_steal_pointer(&children));
        g_list_free(g_steal_pointer(&parent));
    }
    if(event->type == GDK_BUTTON_PRESS && event->button == 3)
    {
        GList *parent = gtk_container_get_children(GTK_CONTAINER(widget)); // GList *parent_c = parent;
        GList *children = gtk_container_get_children(GTK_CONTAINER(parent->data)); // GList *children_c = children;
        children = children->next;
        char* username = (char*)gtk_label_get_text(GTK_LABEL(children->data));
        children = children->next;
        char* chat_id_from_label = (char*)gtk_label_get_text(GTK_LABEL(children->data));
        children = children->next;
        char* user_id_from_label = (char*)gtk_label_get_text(GTK_LABEL(children->data));
        // printf("%s %s %s\n", username, chat_id_from_label, user_id_from_label);

        int chat_id = atoi(chat_id_from_label);
        if (atoi(user_id_from_label) == 0) {
            creator_groupsettings(t_msg.main, username, 0); /*chat_id*/
        }
        else {
            t_user *user = malloc(sizeof(t_user));
            user->id = atoi(user_id_from_label);
            get_user(user);
            creator_userprofile(t_msg.main, user, chat_id);
            free_user(user);
        }
        g_list_free(g_steal_pointer(&children)); // g_list_free(children_c); //
        g_list_free(g_steal_pointer(&parent)); // g_list_free(parent_c); //
    }
}

void msggroup_click(GtkWidget *widget, GdkEventButton *event, gpointer main) {
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1)
        creator_group((GtkWidget*)main);
}

static void *scrolling_to_bottom() {
    GtkAdjustment *adjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(t_msg.scrolled_message));
    for (int i = 1; i <= 30; i++) {
        gtk_adjustment_set_value(adjustment, gtk_adjustment_get_value(adjustment) + i);
        gtk_scrolled_window_set_vadjustment(GTK_SCROLLED_WINDOW(t_msg.scrolled_message), adjustment);
        usleep(5000);
    }
    gtk_adjustment_set_value(adjustment, G_MAXDOUBLE);
    gtk_scrolled_window_set_vadjustment(GTK_SCROLLED_WINDOW(t_msg.scrolled_message), adjustment);
    gtk_widget_reshow(t_msg.scrolled_message);
    gtk_widget_reshow(t_msg.arrow);
    return NULL;
}

void arrow_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) {
        pthread_t scrolling_thread = NULL;
        pthread_create(&scrolling_thread, NULL, scrolling_to_bottom, NULL);
    }
}
