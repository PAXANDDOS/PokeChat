#include "../inc/client.h"

// Home button
//============================================================
void home_enter_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    if (!home_img.active)
        gtk_image_set_from_file(GTK_IMAGE(home_img.standard), home_img.hovered);
}

void home_leave_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    if (!home_img.active)
        gtk_image_set_from_file(GTK_IMAGE(home_img.standard), home_img.basic);
}

void home_click(GtkWidget *widget, gpointer data) {
    if (home_img.active) return;
    if (widget) {}
    if (data) {}
    t_active->active = false;
    gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->basic);
    t_active = &home_img;
    t_active->active = true;
    gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->pressed);
}
//============================================================

// Messages button
//============================================================
void messages_enter_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    if (!messages_img.active)
        gtk_image_set_from_file(GTK_IMAGE(messages_img.standard), messages_img.hovered);
}

void messages_leave_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    if (!messages_img.active)
        gtk_image_set_from_file(GTK_IMAGE(messages_img.standard), messages_img.basic);
}

void messages_click(GtkWidget *widget, gpointer data) {
    if (messages_img.active) return;
    if (widget) {}
    if (data) {}
    t_active->active = false;
    gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->basic);
    t_active = &messages_img;
    t_active->active = true;
    gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->pressed);
}
//============================================================

// Settings button
//============================================================
void settings_enter_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    if (!settings_img.active)
        gtk_image_set_from_file(GTK_IMAGE(settings_img.standard), settings_img.hovered);
}

void settings_leave_notify(GtkWidget *widget, gpointer data) {
    if (data) {}
    if (widget) {}
    if (!settings_img.active)
        gtk_image_set_from_file(GTK_IMAGE(settings_img.standard), settings_img.basic);
}

void settings_click(GtkWidget *widget, gpointer data) {
    if (settings_img.active) return;
    if (widget) {}
    if (data) {}
    t_active->active = false;
    gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->basic);
    t_active = &settings_img;
    t_active->active = true;
    gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->hovered);
}
//============================================================
