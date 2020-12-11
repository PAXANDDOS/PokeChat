#include "../inc/client.h"

void adduser_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void adduser_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void adduser_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
}

////

void attach_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void attach_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void attach_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
}

////

void send_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void send_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void send_click(GtkWidget *widget, GdkEventButton *event, GtkWidget *entry_text) {
    if(widget) {}
    if(event) {}
    if(msg_data.content == NULL || !strcmp(msg_data.content, ""))
        return;
    msg_data.sent = true;
    if(msg_data.sent == true) {
        new_outgoing_message(chat_screen);                                   // Передавать как параметры: имя, фото, текст сообщения
        gtk_entry_set_text(GTK_ENTRY(entry_text), "");
        msg_data.sent = false;
    }
}

void entry_text_change_event(GtkWidget *widget) {
    msg_data.content_len = strlen(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget))));
    msg_data.content = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget)));
}

////

void sticker_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void sticker_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void sticker_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
}

///

void single_event_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void single_event_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void single_event_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
}
