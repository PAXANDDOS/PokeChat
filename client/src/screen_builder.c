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

    t_screen.boxes[0] = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_screen.boxes[0]), "homebutton");
    gtk_widget_set_halign(GTK_WIDGET(t_screen.boxes[0]), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(t_screen.boxes[0]), 50, 50);
    gtk_box_pack_start(GTK_BOX(selection), t_screen.boxes[0], FALSE, FALSE, 10);
    gtk_widget_set_state_flags(GTK_WIDGET(t_screen.boxes[0]), GTK_STATE_FLAG_LINK, FALSE);
    tooltip("Home", t_screen.boxes[0]);

    t_screen.boxes[1] = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_screen.boxes[1]), "msgbutton");
    gtk_widget_set_halign(GTK_WIDGET(t_screen.boxes[1]), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(t_screen.boxes[1]), 50, 50);
    gtk_box_pack_start(GTK_BOX(selection), t_screen.boxes[1], FALSE, FALSE, 10);
    tooltip("Messages", t_screen.boxes[1]);

    t_screen.boxes[2] = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_screen.boxes[2]), "groupbutton");
    gtk_widget_set_halign(GTK_WIDGET(t_screen.boxes[2]), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(t_screen.boxes[2]), 50, 50);
    gtk_box_pack_start(GTK_BOX(selection), t_screen.boxes[2], FALSE, FALSE, 10);
    tooltip("Team chat", t_screen.boxes[2]);

    t_screen.boxes[3] = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_screen.boxes[3]), "eventsbutton");
    gtk_widget_set_halign(GTK_WIDGET(t_screen.boxes[3]), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(t_screen.boxes[3]), 50, 50);
    gtk_box_pack_start(GTK_BOX(selection), t_screen.boxes[3], FALSE, FALSE, 10);
    tooltip("Team events",t_screen.boxes[3]);

    t_screen.boxes[5] = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_screen.boxes[5]), "settingsbutton");
    gtk_widget_set_halign(GTK_WIDGET(t_screen.boxes[5]), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(t_screen.boxes[5]), 46, 46);
    gtk_box_pack_end(GTK_BOX(selection), t_screen.boxes[5], FALSE, FALSE, 10);
    tooltip("Settings", t_screen.boxes[5]);

    t_screen.boxes[4] = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_screen.boxes[4]), "statusbutton");
    gtk_widget_set_halign(GTK_WIDGET(t_screen.boxes[4]), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(t_screen.boxes[4]), 42, 42);
    gtk_box_pack_end(GTK_BOX(selection), t_screen.boxes[4], FALSE, FALSE, 10);
    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 42, 42);
    gtk_widget_set_halign(GTK_WIDGET(avatar), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(avatar), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar_account), (int*)42);
    gtk_event_box_set_above_child(GTK_EVENT_BOX(t_screen.boxes[4]), TRUE);
    gtk_container_add(GTK_CONTAINER(t_screen.boxes[4]), avatar);

    // Checking for events
    g_signal_connect(G_OBJECT(t_screen.boxes[0]), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_screen.boxes[0]), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_screen.boxes[0]), "button_press_event", G_CALLBACK(home_click), NULL);

    g_signal_connect(G_OBJECT(t_screen.boxes[1]), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_screen.boxes[1]), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_screen.boxes[1]), "button_press_event", G_CALLBACK(messages_click), NULL);

    g_signal_connect(G_OBJECT(t_screen.boxes[2]), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_screen.boxes[2]), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_screen.boxes[2]), "button_press_event", G_CALLBACK(group_click), NULL);

    g_signal_connect(G_OBJECT(t_screen.boxes[3]), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_screen.boxes[3]), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_screen.boxes[3]), "button_press_event", G_CALLBACK(events_click), NULL);

    g_signal_connect(G_OBJECT(t_screen.boxes[4]), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_screen.boxes[4]), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_screen.boxes[4]), "button_press_event", G_CALLBACK(status_click), NULL);

    g_signal_connect(G_OBJECT(t_screen.boxes[5]), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_screen.boxes[5]), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_screen.boxes[5]), "button_press_event", G_CALLBACK(settings_click), NULL);
}
