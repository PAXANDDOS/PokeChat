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
        gtk_entry_set_text(GTK_ENTRY(search_field), "");
        
        // Получить данные пользователя: аватар, имя, статус
        chat_push_back(&tchatlist, name, 54, true);
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
        
        dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(t_application.window), action,  "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
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
    new_outgoing_embedded(t_chat.chat_screen, path);
}

void send_click(GtkWidget *widget, GdkEventButton *event, GtkWidget *entry_text) {
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) 
    {
        msg_data.content = mx_strtrim(msg_data.content);
        if(msg_data.content == NULL || !strcmp(msg_data.content, "") || !strcmp(msg_data.content, " "))
            return;
        msg_data.sent = true;
        msg_data.content_final = strdup(msg_data.content);
        pthread_t thread = NULL;
        pthread_create(&thread, NULL, send_message, NULL);
        new_outgoing_message(t_chat.chat_screen);   // Передавать как параметры: имя, фото, текст сообщения
        send_message();
        gtk_entry_set_text(GTK_ENTRY(entry_text), "");
        msg_data.sent = false;
    }
}

void entry_text_change_event(GtkWidget *widget) {
    msg_data.content_len = strlen(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget))));
    msg_data.content = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget)));
}

void sticker_click(GtkWidget *widget, GdkEventButton *event, GtkWidget *main) {
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1)
        create_stickerlist(main);
}

void single_event_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) 
    {

    }
}

void msggroup_click(GtkWidget *widget, GdkEventButton *event, GtkWidget *main) {
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1)
        creator_group(main);
}
