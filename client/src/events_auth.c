#include "../inc/client.h"

void login_button_click(GtkWidget *widget, GdkEventButton *event, gpointer main_area)
{
    if(widget){}
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_destroy(GTK_WIDGET(t_auth.mystic_event));
        gtk_widget_destroy(GTK_WIDGET(t_auth.instinct_event));
        gtk_widget_destroy(GTK_WIDGET(t_auth.valor_event));
        gtk_widget_destroy(GTK_WIDGET(t_auth.registration_menu));
        build_authorization((GtkWidget**)main_area);
    }
}

void register_button_click(GtkWidget *widget, GdkEventButton *event, gpointer main_area)
{
    if(widget){}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_destroy(GTK_WIDGET(t_auth.login_menu));
        build_registration((GtkWidget**)main_area);
    }
}

void mystic_event_button_click(GtkWidget *widget, GdkEventButton *event)
{
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) 
    {
        gtk_widget_unset_state_flags(GTK_WIDGET(t_auth.instinct_event), GTK_STATE_FLAG_LINK);
        gtk_widget_unset_state_flags(GTK_WIDGET(t_auth.valor_event), GTK_STATE_FLAG_LINK);
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
    }
}

void instinct_event_button_click(GtkWidget *widget, GdkEventButton *event)
{
    if(widget){}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) 
    {
        gtk_widget_unset_state_flags(GTK_WIDGET(t_auth.mystic_event), GTK_STATE_FLAG_LINK);
        gtk_widget_unset_state_flags(GTK_WIDGET(t_auth.valor_event), GTK_STATE_FLAG_LINK);
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
    }
}

void valor_event_button_click(GtkWidget *widget, GdkEventButton *event)
{
    if(widget){}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) 
    {
        gtk_widget_unset_state_flags(GTK_WIDGET(t_auth.mystic_event), GTK_STATE_FLAG_LINK);
        gtk_widget_unset_state_flags(GTK_WIDGET(t_auth.instinct_event), GTK_STATE_FLAG_LINK);
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
    }
}
