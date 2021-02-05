#include "../inc/client.h"

void home_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget && t_screen.active == 1) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_unset_state_flags(GTK_WIDGET(t_screen.boxes[t_screen.active-1]), GTK_STATE_FLAG_LINK);
        t_screen.active = 1;
        gtk_widget_set_state_flags(GTK_WIDGET(t_screen.boxes[t_screen.active-1]), GTK_STATE_FLAG_LINK, TRUE);

        gtk_widget_hide(GTK_WIDGET(t_screen.active_screen));
        t_screen.active_screen = t_screen.home_scr;
        gtk_widget_show(GTK_WIDGET(t_screen.active_screen));

        t_pokefact.pokemon_fact_text = "client/data/pokemon-text/";
        t_pokefact.pokemon_fact_image = "client/data/pokemon/";
        t_pokefact.pokemon_fact_audio = "client/data/pokemon-audio/";
        pokemon_random();
        gtk_label_set_text(GTK_LABEL(t_pokefact.pokemon_text), mx_file_to_str(t_pokefact.pokemon_fact_text));
    }
}

void messages_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget && t_screen.active == 2) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_unset_state_flags(GTK_WIDGET(t_screen.boxes[t_screen.active-1]), GTK_STATE_FLAG_LINK);
        t_screen.active = 2;
        gtk_widget_set_state_flags(GTK_WIDGET(t_screen.boxes[t_screen.active-1]), GTK_STATE_FLAG_LINK, TRUE);

        gtk_widget_hide(GTK_WIDGET(t_screen.active_screen));
        t_screen.active_screen = t_screen.msg_scr;
        gtk_widget_show(GTK_WIDGET(t_screen.active_screen));
    }
}

void group_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget && t_screen.active == 3) return;
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) {
        create_notification(t_application.messanger, "Not available at the moment!", 1, LEFTBAR_W, 160, 0, 30);
        
        // gtk_widget_unset_state_flags(GTK_WIDGET(t_screen.boxes[t_screen.active-1]), GTK_STATE_FLAG_LINK);
        // t_screen.active = 3;
        // gtk_widget_set_state_flags(GTK_WIDGET(t_screen.boxes[t_screen.active-1]), GTK_STATE_FLAG_LINK, TRUE);
    }
    if(widget) {}
}

void events_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget && t_screen.active == 4) return;
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) {
        create_notification(t_application.messanger, "Not available at the moment!", 1, LEFTBAR_W, 230, 0, 30);
        // gtk_widget_unset_state_flags(GTK_WIDGET(t_screen.boxes[t_screen.active-1]), GTK_STATE_FLAG_LINK);
        // t_screen.active = 4;
        // gtk_widget_set_state_flags(GTK_WIDGET(t_screen.boxes[t_screen.active-1]), GTK_STATE_FLAG_LINK, TRUE);
    }
    if(widget) {}
}

void status_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget || event) {}
}

void settings_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget && t_screen.active == 6) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_unset_state_flags(GTK_WIDGET(t_screen.boxes[t_screen.active-1]), GTK_STATE_FLAG_LINK);
        t_screen.active = 6;
        gtk_widget_set_state_flags(GTK_WIDGET(t_screen.boxes[t_screen.active-1]), GTK_STATE_FLAG_LINK, TRUE);

        gtk_widget_hide(GTK_WIDGET(t_screen.active_screen));
        t_screen.active_screen = t_screen.settings_scr;
        gtk_widget_show(GTK_WIDGET(t_screen.active_screen));
    }
}
