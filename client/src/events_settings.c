#include "../inc/client.h"

void add_button_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void add_button_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void add_button_click_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
}
