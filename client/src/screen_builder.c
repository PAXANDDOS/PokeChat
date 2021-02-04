#include "../inc/client.h"

void build_all(GtkWidget **main_area)
{
    GtkWidget *selection = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);                         // Создаем виджет левого бара
    gtk_widget_set_name(GTK_WIDGET(selection), "leftbar");                         // Присваиваем ему имя для связи с CSS
    gtk_widget_set_size_request(GTK_WIDGET(selection), LEFTBAR_W, WINDOW_HEIGHT);  // Настройка размера виджета
    gtk_fixed_put(GTK_FIXED(*main_area), selection, 0, 0);                         // Настройка позиции виджета

    build_home_screen(main_area);       // Вызываю постройку домашнего экрана
    build_messanger_screen(main_area);  // Вызываю постройку экрана сообщений
    build_settings_menu(main_area);     // Вызываю постройку экрана настроек
    t_screen.active_screen = t_screen.home_scr;           // Назначаю домашний экран активным

    GtkWidget *home_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(home_box), "homebutton");
    gtk_widget_set_halign(GTK_WIDGET(home_box), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(home_box), 50, 50);
    gtk_box_pack_start(GTK_BOX(selection), home_box, FALSE, FALSE, 10);
    gtk_widget_set_state_flags(GTK_WIDGET(home_box), GTK_STATE_FLAG_LINK, FALSE);
    tooltip("Home",home_box);

    GtkWidget *msg_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(msg_box), "msgbutton");
    gtk_widget_set_halign(GTK_WIDGET(msg_box), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(msg_box), 50, 50);
    gtk_box_pack_start(GTK_BOX(selection), msg_box, FALSE, FALSE, 10);
    tooltip("Messages",msg_box);

    GtkWidget *group_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(group_box), "groupbutton");
    gtk_widget_set_halign(GTK_WIDGET(group_box), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(group_box), 50, 50);
    gtk_box_pack_start(GTK_BOX(selection), group_box, FALSE, FALSE, 10);
    tooltip("Team chat",group_box);

    GtkWidget *events_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(events_box), "eventsbutton");
    gtk_widget_set_halign(GTK_WIDGET(events_box), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(events_box), 50, 50);
    gtk_box_pack_start(GTK_BOX(selection), events_box, FALSE, FALSE, 10);
    tooltip("Team events",events_box);

    GtkWidget *settings_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET( settings_box), "settingsbutton");
    gtk_widget_set_halign(GTK_WIDGET( settings_box), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET( settings_box), 46, 46);
    gtk_box_pack_end(GTK_BOX(selection),  settings_box, FALSE, FALSE, 10);
    tooltip("Settings",settings_box);

    GtkWidget* status_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(status_box), "statusbutton");
    gtk_widget_set_halign(GTK_WIDGET(status_box), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(status_box), 42, 42);
    gtk_box_pack_end(GTK_BOX(selection), status_box, FALSE, FALSE, 10);
    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 42, 42);
    gtk_widget_set_halign(GTK_WIDGET(avatar), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(avatar), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar_account), (int*)42);
    gtk_event_box_set_above_child(GTK_EVENT_BOX(status_box), TRUE);
    gtk_container_add(GTK_CONTAINER(status_box), avatar);

    // Checking for events
    g_signal_connect(G_OBJECT(home_box), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(home_box), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(home_box), "button_press_event", G_CALLBACK(home_click), selection);

    g_signal_connect(G_OBJECT(msg_box), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(msg_box), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(msg_box), "button_press_event", G_CALLBACK(messages_click), selection);

    g_signal_connect(G_OBJECT(group_box), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(group_box), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(group_box), "button_press_event", G_CALLBACK(group_click), selection);

    g_signal_connect(G_OBJECT(events_box), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(events_box), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(events_box), "button_press_event", G_CALLBACK(events_click), selection);

    g_signal_connect(G_OBJECT(status_box), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(status_box), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(status_box), "button_press_event", G_CALLBACK(status_click), selection);

    g_signal_connect(G_OBJECT(settings_box), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(settings_box), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(settings_box), "button_press_event", G_CALLBACK(settings_click), selection);
}
