#include "../inc/client.h"

void build_all(GtkWidget **main_area)
{
    GtkWidget *content_selection_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);                         // Создаем виджет левого бара
    gtk_widget_set_name(GTK_WIDGET(content_selection_area), "leftbar");                         // Присваиваем ему имя для связи с CSS
    gtk_widget_set_size_request(GTK_WIDGET(content_selection_area), LEFTBAR_W, WINDOW_HEIGHT);  // Настройка размера виджета
    gtk_fixed_put(GTK_FIXED(*main_area), content_selection_area, 0, 0);                         // Настройка позиции виджета

    build_home_screen(main_area);       // Вызываю постройку домашнего экрана
    build_messanger_screen(main_area);  // Вызываю постройку экрана сообщений
    build_settings_menu(main_area);     // Вызываю постройку экрана настроек
    t_leftbar.active_screen = t_leftbar.home_scr;           // Назначаю домашний экран активным

    t_leftbar.home_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_leftbar.home_box), "homebutton");
    gtk_widget_set_halign(GTK_WIDGET(t_leftbar.home_box), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(t_leftbar.home_box), 50, 50);
    gtk_box_pack_start(GTK_BOX(content_selection_area), t_leftbar.home_box, FALSE, FALSE, 10);
    gtk_widget_set_state_flags(GTK_WIDGET(t_leftbar.home_box), GTK_STATE_FLAG_LINK, FALSE);
    tooltip("Home",t_leftbar.home_box);

    t_leftbar.msg_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_leftbar.msg_box), "msgbutton");
    gtk_widget_set_halign(GTK_WIDGET(t_leftbar.msg_box), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(t_leftbar.msg_box), 50, 50);
    gtk_box_pack_start(GTK_BOX(content_selection_area), t_leftbar.msg_box, FALSE, FALSE, 10);
    tooltip("Messages",t_leftbar.msg_box);

    t_leftbar.group_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_leftbar.group_box), "groupbutton");
    gtk_widget_set_halign(GTK_WIDGET(t_leftbar.group_box), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(t_leftbar.group_box), 50, 50);
    gtk_box_pack_start(GTK_BOX(content_selection_area), t_leftbar.group_box, FALSE, FALSE, 10);
    tooltip("Team chat",t_leftbar.group_box);

    t_leftbar.events_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_leftbar.events_box), "eventsbutton");
    gtk_widget_set_halign(GTK_WIDGET(t_leftbar.events_box), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(t_leftbar.events_box), 50, 50);
    gtk_box_pack_start(GTK_BOX(content_selection_area), t_leftbar.events_box, FALSE, FALSE, 10);
    tooltip("Team events",t_leftbar.events_box);

    t_leftbar.settings_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET( t_leftbar.settings_box), "settingsbutton");
    gtk_widget_set_halign(GTK_WIDGET( t_leftbar.settings_box), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET( t_leftbar.settings_box), 46, 46);
    gtk_box_pack_end(GTK_BOX(content_selection_area),  t_leftbar.settings_box, FALSE, FALSE, 10);
    tooltip("Settings",t_leftbar.settings_box);

    GtkWidget* status_box = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(status_box), "statusbutton");
    gtk_widget_set_halign(GTK_WIDGET(status_box), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(status_box), 42, 42);
    gtk_box_pack_end(GTK_BOX(content_selection_area), status_box, FALSE, FALSE, 10);
    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 42, 42);
    gtk_widget_set_halign(GTK_WIDGET(avatar), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(avatar), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar_account), (int*)42);
    gtk_event_box_set_above_child(GTK_EVENT_BOX(status_box), TRUE);
    gtk_container_add(GTK_CONTAINER(status_box), avatar);

    // Checking for events
    g_signal_connect(G_OBJECT(t_leftbar.home_box), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_leftbar.home_box), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_leftbar.home_box), "button_press_event", G_CALLBACK(home_click), NULL);

    g_signal_connect(G_OBJECT(t_leftbar.msg_box), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_leftbar.msg_box), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_leftbar.msg_box), "button_press_event", G_CALLBACK(messages_click), NULL);

    g_signal_connect(G_OBJECT(t_leftbar.group_box), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_leftbar.group_box), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_leftbar.group_box), "button_press_event", G_CALLBACK(group_click), NULL);

    g_signal_connect(G_OBJECT(t_leftbar.events_box), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_leftbar.events_box), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_leftbar.events_box), "button_press_event", G_CALLBACK(events_click), NULL);

    g_signal_connect(G_OBJECT(status_box), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(status_box), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(status_box), "button_press_event", G_CALLBACK(status_click), NULL);

    g_signal_connect(G_OBJECT(t_leftbar.settings_box), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_leftbar.settings_box), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_leftbar.settings_box), "button_press_event", G_CALLBACK(settings_click), NULL);
}
