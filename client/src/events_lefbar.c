#include "../inc/client.h"

void home_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if (home_img.active) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        t_active->active = false;
        gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->basic);
        t_active = &home_img;
        t_active->active = true;
        gtk_image_set_from_file(GTK_IMAGE(t_active->standard), t_active->hovered);

        gtk_widget_hide(GTK_WIDGET(t_main_scr.active_screen));
        t_main_scr.active_screen = t_main_scr.home_scr;
        gtk_widget_show(GTK_WIDGET(t_main_scr.active_screen));

        t_pokefact.pokemon_fact_text = "client/data/pokemon-text/";
        t_pokefact.pokemon_fact_image = "client/data/pokemon/";
        t_pokefact.pokemon_fact_audio = "client/data/pokemon-audio/";
        pokemon_random();
        gtk_label_set_text(GTK_LABEL(t_pokefact.pokemon_text), mx_file_to_str(t_pokefact.pokemon_fact_text));
    }
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

        gtk_widget_hide(GTK_WIDGET(t_main_scr.active_screen));
        t_main_scr.active_screen = t_main_scr.msg_scr;
        gtk_widget_show(GTK_WIDGET(t_main_scr.active_screen));
    }
}

void group_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(group_img.active) return;
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) {}
}

void events_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(events_img.active) return;
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) {}
}

void status_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
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

        gtk_widget_hide(GTK_WIDGET(t_main_scr.active_screen));
        t_main_scr.active_screen = t_main_scr.settings_scr;
        gtk_widget_show(GTK_WIDGET(t_main_scr.active_screen));
    }
}
