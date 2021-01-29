#include "../inc/client.h"

static GtkWidget *create_single(t_chat_list* list)
{
    GtkWidget *single = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_size_request(GTK_WIDGET(single), LIST_W-20, 46);

    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 34, 34);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar), (gpointer)(intptr_t)list->avatar);   // Получить avatar пользовтеля
    gtk_widget_set_halign(avatar, GTK_ALIGN_START);
    gtk_widget_set_valign(avatar, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(single), avatar, FALSE, FALSE, 0);

    GtkWidget *nickname = gtk_label_new(list->username);                        // Получить username пользователя
    gtk_widget_set_name(GTK_WIDGET(nickname), "nickname");                 // Имя
    gtk_box_pack_start(GTK_BOX(single), nickname, FALSE, FALSE, 5);

    if(list->status){
        GtkWidget *status = gtk_drawing_area_new();
        gtk_widget_set_size_request(GTK_WIDGET(status), 7, 7);
        g_signal_connect(G_OBJECT(status), "draw", G_CALLBACK(draw_event_status), (int*)7); // Проверить статус в сети
        gtk_widget_set_halign(status, GTK_ALIGN_START);
        gtk_widget_set_valign(status, GTK_ALIGN_CENTER);
        gtk_box_pack_start(GTK_BOX(single), status, FALSE, FALSE, 0);
    }

    return single;
}

GtkWidget *add_single(t_chat_list* list)
{
    GtkWidget *single_event = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(single_event), "single");
    gtk_event_box_set_above_child(GTK_EVENT_BOX(single_event), TRUE);

    GtkWidget *single = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_size_request(GTK_WIDGET(single), LIST_W-20, 46);
    gtk_widget_set_name(GTK_WIDGET(single), "singlepad");
    gtk_container_add(GTK_CONTAINER(single_event), single);

    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 34, 34);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar), (gpointer)(intptr_t)list->avatar);   // Получить avatar пользовтеля
    gtk_widget_set_halign(avatar, GTK_ALIGN_START);
    gtk_widget_set_valign(avatar, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(single), avatar, FALSE, FALSE, 0);

    GtkWidget *nickname = gtk_label_new(list->username);                        // Получить username пользователя
    gtk_widget_set_name(GTK_WIDGET(nickname), "nickname");                 // Имя
    gtk_box_pack_start(GTK_BOX(single), nickname, FALSE, FALSE, 5);

    GtkWidget *chat_id = gtk_label_new(mx_itoa(list->chat_id));           // CHAT_ID сюда
    gtk_widget_set_name(GTK_WIDGET(chat_id), "hidden");
    gtk_box_pack_start(GTK_BOX(single), chat_id, FALSE, FALSE, 0);

    GtkWidget *user_id = gtk_label_new(mx_itoa(list->user_id));           // USER_ID сюда
    gtk_widget_set_name(GTK_WIDGET(user_id), "hidden");
    gtk_box_pack_start(GTK_BOX(single), user_id, FALSE, FALSE, 0);

    if(list->status){
        GtkWidget *status = gtk_drawing_area_new();
        gtk_widget_set_size_request(GTK_WIDGET(status), 7, 7);
        g_signal_connect(G_OBJECT(status), "draw", G_CALLBACK(draw_event_status), (int*)7); // Проверить статус в сети
        gtk_widget_set_halign(status, GTK_ALIGN_START);
        gtk_widget_set_valign(status, GTK_ALIGN_CENTER);
        gtk_box_pack_start(GTK_BOX(single), status, FALSE, FALSE, 0);
    }

    return single_event;
}

GtkWidget *create_chatlist() {
    GtkWidget *chatlist_widget = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(chatlist_widget, LIST_W-20, LIST_H-104);

    t_chat_list *p = chatlist;
    while(p)
    {
        GtkWidget *single_event = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(single_event), "single");
        gtk_event_box_set_above_child(GTK_EVENT_BOX(single_event), TRUE);
        gtk_box_pack_start(GTK_BOX(chatlist_widget), single_event, FALSE, FALSE, 3);

        GtkWidget *single = create_single(p);
        gtk_widget_set_name(GTK_WIDGET(single), "singlepad");
        gtk_container_add(GTK_CONTAINER(single_event), single);

        g_signal_connect(G_OBJECT(single_event), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
        g_signal_connect(G_OBJECT(single_event), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
        g_signal_connect(G_OBJECT(single_event), "button_press_event", G_CALLBACK(person_click), NULL);
        tooltip("Message/Profile",single_event);
        p = p->next;
    }

    return chatlist_widget;
}
