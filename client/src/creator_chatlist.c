#include "../inc/client.h"

static GtkWidget *create_single()
{
    GtkWidget *single = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_size_request(GTK_WIDGET(single), LIST_W-20, 46);
    gtk_widget_set_name(GTK_WIDGET(single), "single");

    GtkWidget *avatar_container = gtk_fixed_new();
    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 34, 34);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar), (int*)34);
    GtkWidget *status = gtk_event_box_new();
    gtk_widget_set_size_request(GTK_WIDGET(status), 16, 16);
    gtk_widget_set_name(GTK_WIDGET(status), "status");
    gtk_fixed_put(GTK_FIXED(avatar_container), avatar, 0, 0);
    gtk_fixed_put(GTK_FIXED(avatar_container), status, 24, 20);
    gtk_widget_set_halign(avatar_container, GTK_ALIGN_START);
    gtk_widget_set_valign(avatar_container, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(single), avatar_container, FALSE, FALSE, 0);

    GtkWidget *nickname = gtk_label_new("Gazaris");
    gtk_widget_set_name(GTK_WIDGET(nickname), "nickname");                 // Имя
    gtk_box_pack_start(GTK_BOX(single), nickname, FALSE, FALSE, 5);

    return single;
}

GtkWidget *create_chatlist() {
    GtkWidget *chatlist = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(chatlist, LIST_W-20, LIST_H-104);

    for(int i = 0; i < 5; i++)
    {
        GtkWidget *single_event = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(single_event), "single");
        GtkWidget *single = create_single();
        gtk_container_add(GTK_CONTAINER(single_event), single);
        gtk_box_pack_start(GTK_BOX(chatlist), single_event, FALSE, FALSE, 3);
    }

    return chatlist;
}
