#include "../inc/client.h"

//--//--//--// OVERALL //--//--//--//

void event_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void event_false_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, FALSE);
}

void event_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

//--//--//--//         //--//--//--//

void active1_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
}

void active2_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
}

void active3_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
}

void active4_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
}

void active5_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
}
