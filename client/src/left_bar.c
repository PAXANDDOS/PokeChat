#include "../inc/client.h"

void build_left_bar(GtkWidget **content_selection_area, GtkWidget **main_area) 
{
    *content_selection_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_fixed_put(GTK_FIXED(*main_area), *content_selection_area, 0, 0);
    gtk_container_set_border_width(GTK_CONTAINER(*content_selection_area), 8);
    gtk_widget_set_size_request(GTK_WIDGET(*content_selection_area), 80, 0);

    gtk_box_pack_start(GTK_BOX(*content_selection_area),
        t_img_event_box.messages_box, TRUE, FALSE, 22);
    gtk_box_pack_start(GTK_BOX(*content_selection_area),
        t_img_event_box.contacts_box, TRUE, FALSE, 30);
    gtk_box_pack_start(GTK_BOX(*content_selection_area),
        t_img_event_box.settings_box, TRUE, FALSE, 30);

    // g_signal_connect(G_OBJECT(t_img_event_box.contacts_box), "enter-notify-event",
    //     G_CALLBACK(contacts_enter_notify), NULL);
    // g_signal_connect(G_OBJECT(t_img_event_box.contacts_box), "leave-notify-event",
    //     G_CALLBACK(contacts_leave_notify), NULL);

    // g_signal_connect(G_OBJECT(t_img_event_box.messages_box), "enter-notify-event",
    //     G_CALLBACK(messages_enter_notify), NULL);
    // g_signal_connect(G_OBJECT(t_img_event_box.messages_box), "leave-notify-event",
    //     G_CALLBACK(messages_leave_notify), NULL);

    // g_signal_connect(G_OBJECT(t_img_event_box.settings_box), "enter-notify-event",
    //     G_CALLBACK(settings_enter_notify), NULL);
    // g_signal_connect(G_OBJECT(t_img_event_box.settings_box), "leave-notify-event",
    //     G_CALLBACK(settings_leave_notify), NULL);
}
