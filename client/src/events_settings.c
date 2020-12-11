#include "../inc/client.h"

void change_avatar_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
    gtk_widget_hide(GTK_WIDGET(t_settings_scr.settings_active));
    t_settings_scr.settings_active = t_settings_scr.select_avatar;
    gtk_widget_show(GTK_WIDGET(t_settings_scr.settings_active));
}

void change_info_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
    gtk_widget_hide(GTK_WIDGET(t_settings_scr.settings_active));
    t_settings_scr.settings_active = t_settings_scr.change_info;
    gtk_widget_show(GTK_WIDGET(t_settings_scr.settings_active));
}
