#include "../inc/client.h"

static void *hide_notification() {
    if(t_application.notificaton != NULL){
        usleep(2000000);
        for (double i = 1; i >= 0; i -= 0.05) {
            if(t_application.notificaton == NULL)
                return NULL;
            gtk_widget_set_opacity(t_application.notificaton, i);
            usleep(10000);
        }
        gtk_widget_destroy(t_application.notificaton);
        t_application.notificaton = NULL;
    }
    return NULL;
}

void create_notification(GtkWidget *widget, char *text, short type, int x, int y, int w, int h)
{
    if(t_application.notificaton != NULL)
        gtk_widget_destroy(GTK_WIDGET(t_application.notificaton));

    t_application.notificaton = gtk_event_box_new();
    gtk_widget_set_size_request(GTK_WIDGET(t_application.notificaton), w, h);
    //g_signal_connect(G_OBJECT(t_application.notificaton), "button_press_event", G_CALLBACK(gtk_widget_destroy), NULL);
    gtk_fixed_put(GTK_FIXED(widget), t_application.notificaton, x, y);

    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_size_request(GTK_WIDGET(box), w, h);
    gtk_widget_set_name(GTK_WIDGET(box), "notification_box");
    gtk_container_add(GTK_CONTAINER(t_application.notificaton), box);

    GtkWidget *label = gtk_label_new(text);
    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);

    switch(type)
    {
        case 0: {
            gtk_widget_set_name(GTK_WIDGET(t_application.notificaton), "notification_body");
            gtk_widget_set_name(GTK_WIDGET(label), "notification_text");
            break;
        }
        case 1: {
            gtk_widget_set_name(GTK_WIDGET(t_application.notificaton), "notification_body_error");
            gtk_widget_set_name(GTK_WIDGET(label), "notification_text_error");
            break;
        }
        default: {
            gtk_widget_set_name(GTK_WIDGET(t_application.notificaton), "notification_body");
            gtk_widget_set_name(GTK_WIDGET(label), "notification_text");
            break;
        }
    }
    gtk_widget_show_all(GTK_WIDGET(t_application.notificaton));
    pthread_t hide_thread = NULL;
    pthread_create(&hide_thread, NULL, hide_notification, NULL);
}
