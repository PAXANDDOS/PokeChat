#include "../inc/client.h"

void home_click(GtkWidget *widget, GdkEventButton *event, gpointer menu) {
    if(t_leftbar.active == 1) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GList *parent = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)menu));
        while(parent) {
            gtk_widget_unset_state_flags(GTK_WIDGET(parent->data), GTK_STATE_FLAG_LINK);
            parent = parent->next;
        }
        g_list_free(g_steal_pointer(&parent));

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_leftbar.active = 1;

        gtk_widget_hide(GTK_WIDGET(t_leftbar.active_screen));
        t_leftbar.active_screen = t_leftbar.home_scr;
        gtk_widget_show(GTK_WIDGET(t_leftbar.active_screen));

        t_pokefact.pokemon_fact_text = "client/data/pokemon-text/";
        t_pokefact.pokemon_fact_image = "client/data/pokemon/";
        t_pokefact.pokemon_fact_audio = "client/data/pokemon-audio/";
        pokemon_random();
        gtk_label_set_text(GTK_LABEL(t_pokefact.pokemon_text), mx_file_to_str(t_pokefact.pokemon_fact_text));
    }
}

void messages_click(GtkWidget *widget, GdkEventButton *event, gpointer menu) {
    if(t_leftbar.active == 2) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GList *parent = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)menu));
        while(parent) {
            gtk_widget_unset_state_flags(GTK_WIDGET(parent->data), GTK_STATE_FLAG_LINK);
            parent = parent->next;
        }
        g_list_free(g_steal_pointer(&parent));

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_leftbar.active = 2;

        gtk_widget_hide(GTK_WIDGET(t_leftbar.active_screen));
        t_leftbar.active_screen = t_leftbar.msg_scr;
        gtk_widget_show(GTK_WIDGET(t_leftbar.active_screen));
    }
}

void group_click(GtkWidget *widget, GdkEventButton *event, gpointer menu) {
    if(t_leftbar.active == 3) return;
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) {
        create_notification(t_application.messanger, "Not available at the moment!", 1, LEFTBAR_W, 160, 0, 30);
        // GList *parent = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)menu));
        // while(parent) {
        //     gtk_widget_unset_state_flags(GTK_WIDGET(parent->data), GTK_STATE_FLAG_LINK);
        //     parent = parent->next;
        // }
        // g_list_free(g_steal_pointer(&parent));

        // gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        // t_leftbar.active = 3;
    }
    if(widget || menu) {}
}

void events_click(GtkWidget *widget, GdkEventButton *event, gpointer menu) {
    if(t_leftbar.active == 4) return;
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) {
        create_notification(t_application.messanger, "Not available at the moment!", 1, LEFTBAR_W, 230, 0, 30);
        if(menu) {}
        // GList *parent = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)menu));
        // while(parent) {
        //     gtk_widget_unset_state_flags(GTK_WIDGET(parent->data), GTK_STATE_FLAG_LINK);
        //     parent = parent->next;
        // }
        // g_list_free(g_steal_pointer(&parent));

        // gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        // t_leftbar.active = 4;
    }
    if(widget || menu) {}
}

void status_click(GtkWidget *widget, GdkEventButton *event, gpointer menu) {
    if(widget || event || menu) {}
}

void settings_click(GtkWidget *widget, GdkEventButton *event, gpointer menu) {
    if(t_leftbar.active == 6) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GList *parent = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)menu));
        while(parent) {
            gtk_widget_unset_state_flags(GTK_WIDGET(parent->data), GTK_STATE_FLAG_LINK);
            parent = parent->next;
        }
        g_list_free(g_steal_pointer(&parent));

        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_leftbar.active = 6;

        gtk_widget_hide(GTK_WIDGET(t_leftbar.active_screen));
        t_leftbar.active_screen = t_leftbar.settings_scr;
        gtk_widget_show(GTK_WIDGET(t_leftbar.active_screen));
    }
}
