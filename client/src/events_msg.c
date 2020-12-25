#include "../inc/client.h"

void adduser_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) 
    {

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
        if(msg_data.sent == true) {
            new_outgoing_message(t_chat.chat_screen);   // Передавать как параметры: имя, фото, текст сообщения
            send_message();
            gtk_entry_set_text(GTK_ENTRY(entry_text), "");
            msg_data.sent = false;
        }
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
