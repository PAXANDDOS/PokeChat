#include "../inc/client.h"

void adduser_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
}

void attach_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
}

void send_click(GtkWidget *widget, GdkEventButton *event, GtkWidget *entry_text) {
    if(widget) {}
    if(event) {}
    if(msg_data.content == NULL || !strcmp(msg_data.content, ""))
        return;
    msg_data.sent = true;
    if(msg_data.sent == true) {
        new_outgoing_message(t_chats.chat_screen);   // Передавать как параметры: имя, фото, текст сообщения
        send_message();
        gtk_entry_set_text(GTK_ENTRY(entry_text), "");
        msg_data.sent = false;
    }
}

void entry_text_change_event(GtkWidget *widget) {
    msg_data.content_len = strlen(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget))));
    msg_data.content = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget)));
}

void sticker_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
}

void single_event_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
}
