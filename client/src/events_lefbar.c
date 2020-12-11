#include "../inc/client.h"

//====================== L E F T  B A R ======================================

// Home button
//============================================================
void home_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void home_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void home_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if (home_img.active) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        t_active->active = false;
        gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->basic);
        t_active = &home_img;
        t_active->active = true;
        gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->hovered);

        gtk_widget_hide(GTK_WIDGET(active_screen));
        active_screen = home_scr;
        gtk_widget_show(GTK_WIDGET(active_screen));
        
        pokemon_fact_text = "client/data/pokemon-text/";
        pokemon_fact_image = "client/data/pokemon/";
        pokemon_random();
        gtk_label_set_text(GTK_LABEL(pokemon_text), mx_file_to_str(pokemon_fact_text));
    }
}
//============================================================

// Messages button
//============================================================
void messages_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void messages_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void messages_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if (messages_img.active) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        t_active->active = false;
        gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->basic);
        t_active = &messages_img;
        t_active->active = true;
        gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->hovered);

        gtk_widget_hide(GTK_WIDGET(active_screen));
        active_screen = msg_scr;
        gtk_widget_show(GTK_WIDGET(active_screen));
    }
}
//============================================================

// Group button
//============================================================
void group_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void group_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void group_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(group_img.active) return;
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) {}
}
//============================================================

// Events button
//============================================================
void events_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void events_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void events_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(events_img.active) return;
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) {}
}
//============================================================

// Status button
//============================================================
void status_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void status_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void status_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
}
//============================================================

// Settings button
//============================================================
void settings_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void settings_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void settings_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(settings_img.active) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        t_active->active = false;
        gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->basic);
        t_active = &settings_img;
        t_active->active = true;
        gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->hovered);
        
        gtk_widget_hide(GTK_WIDGET(active_screen));
        active_screen = settings_scr;
        gtk_widget_show(GTK_WIDGET(active_screen));
    }
}
//============================================================
