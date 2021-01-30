#include "../inc/client.h"

//--//--//--// OVERALL //--//--//--//

void event_enter_notify(GtkWidget *widget) {
    GtkStateFlags flags = gtk_widget_get_state_flags(GTK_WIDGET(widget));
    if (!(flags & GTK_STATE_FLAG_LINK))
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void event_false_enter_notify(GtkWidget *widget) {
    GtkStateFlags flags = gtk_widget_get_state_flags(GTK_WIDGET(widget));
    if (!(flags & GTK_STATE_FLAG_LINK))
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, FALSE);
}

void event_leave_notify(GtkWidget *widget) {
    GtkStateFlags flags = gtk_widget_get_state_flags(GTK_WIDGET(widget));
    if (!(flags & GTK_STATE_FLAG_LINK)) 
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

//--//--//--//         //--//--//--//

void active_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
}

