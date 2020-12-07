#include "../inc/client.h"

void build_all(GtkWidget **content_selection_area, GtkWidget **main_area) 
{
    // Loading CSS file
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/data/css/leftbar.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    //
    // Connecting leftbar widget to CSS
    GtkWidget *left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);                     // Создаем виджет левого бара
    gtk_widget_set_name(GTK_WIDGET(left_box), "leftbar");                               // Присваиваем ему имя для связи с CSS
    gtk_widget_set_size_request(GTK_WIDGET(left_box), LEFTBAR_W, CUR_HEIGHT);           // Настройка размера виджета
    gtk_fixed_put(GTK_FIXED(*main_area), left_box, 0, 0);                               // Настройка позиции виджета

    build_home_screen(main_area);       // Вызываю постройку домашнего экрана
    active_screen = home_scr;           // Назначаю домашний экран активным
    build_messanger_screen(main_area);  // Вызываю постройку экрана сообщений
    //
    // Creating selection area
    *content_selection_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);                 // Создаем вертикальный бокс для кнопок
    gtk_fixed_put(GTK_FIXED(*main_area), *content_selection_area, 0, 0);                // Настройка позиции
    gtk_container_set_border_width(GTK_CONTAINER(*content_selection_area), 0);          // Настройка чего-то
    gtk_widget_set_size_request(GTK_WIDGET(*content_selection_area), LEFTBAR_W, 0);     // Настройка границ
    //
    // Creating selection area for settings
    GtkWidget *block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // Создаем такой же бокс, только для кнопок снизу-вверх
    gtk_fixed_put(GTK_FIXED(*main_area), block, 0, 585);         // 640
    gtk_container_set_border_width(GTK_CONTAINER(block), 0);
    gtk_widget_set_size_request(GTK_WIDGET(block), LEFTBAR_W, 0);
    //
    // Placing icons
    gtk_widget_set_name(GTK_WIDGET(t_img_event_box.home_box), "homebutton");
    gtk_box_pack_start(GTK_BOX(*content_selection_area),
        t_img_event_box.home_box, TRUE, FALSE, LEFTBAR_GAP);            // Вызываем функцию ддя размещения иконки из бокса
    gtk_widget_set_halign(t_img_event_box.home_box, GTK_ALIGN_CENTER);  // Центрируем

    gtk_widget_set_name(GTK_WIDGET(t_img_event_box.messages_box), "msgbutton");
    gtk_box_pack_start(GTK_BOX(*content_selection_area),
        t_img_event_box.messages_box, TRUE, FALSE, LEFTBAR_GAP);
    gtk_widget_set_halign(t_img_event_box.messages_box, GTK_ALIGN_CENTER);

    gtk_widget_set_name(GTK_WIDGET(t_img_event_box.group_box), "groupbutton");
    gtk_box_pack_start(GTK_BOX(*content_selection_area),
        t_img_event_box.group_box, TRUE, FALSE, LEFTBAR_GAP);
    gtk_widget_set_halign(t_img_event_box.group_box, GTK_ALIGN_CENTER);

    gtk_widget_set_name(GTK_WIDGET(t_img_event_box.events_box), "eventsbutton");     
    gtk_box_pack_start(GTK_BOX(*content_selection_area),
        t_img_event_box.events_box, TRUE, FALSE, LEFTBAR_GAP);
    gtk_widget_set_halign(t_img_event_box.events_box, GTK_ALIGN_CENTER);

    GtkWidget *avatar_container = gtk_fixed_new();
    GtkWidget *avatar = gtk_drawing_area_new();
    GtkWidget *status = gtk_image_new_from_file("client/data/images/status_online.png");    // Дописать функцию выбора статуса
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 40, 40);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar), (int*)40);
    gtk_box_pack_start(GTK_BOX(block), avatar_container, TRUE, FALSE, LEFTBAR_GAP);          
    gtk_fixed_put(GTK_FIXED(avatar_container), avatar, 0, 0);
    gtk_fixed_put(GTK_FIXED(avatar_container), status, 25, 25);
    gtk_widget_set_halign(avatar_container, GTK_ALIGN_CENTER);

    gtk_widget_set_name(GTK_WIDGET(t_img_event_box.settings_box), "settingsbutton");
    gtk_box_pack_start(GTK_BOX(block),
        t_img_event_box.settings_box, TRUE, FALSE, LEFTBAR_GAP);
    gtk_widget_set_halign(t_img_event_box.settings_box, GTK_ALIGN_CENTER); 
    //
    // Checking for events
    g_signal_connect(G_OBJECT(t_img_event_box.home_box), "enter-notify-event",   // Проверка на наведение мыши,                                                                      
        G_CALLBACK(home_enter_notify), NULL);                                    // G_OBJECT - бокс с картинкой,
    g_signal_connect(G_OBJECT(t_img_event_box.home_box), "leave-notify-event",   // "...-...-event" ивенты из библиотеки,
        G_CALLBACK(home_leave_notify), NULL);                                    // G_CALLBACK функция которая вызывается при действии.
    g_signal_connect(G_OBJECT(t_img_event_box.home_box), "button_press_event",   // gpointer - для доп. данных
        G_CALLBACK(home_click), NULL);
 
    g_signal_connect(G_OBJECT(t_img_event_box.messages_box), "enter-notify-event",
        G_CALLBACK(messages_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.messages_box), "leave-notify-event",
        G_CALLBACK(messages_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.messages_box), "button_press_event",
        G_CALLBACK(messages_click), NULL);

    g_signal_connect(G_OBJECT(t_img_event_box.group_box), "enter-notify-event",
        G_CALLBACK(group_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.group_box), "leave-notify-event",
        G_CALLBACK(group_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.group_box), "button_press_event",
        G_CALLBACK(group_click), NULL);

    g_signal_connect(G_OBJECT(t_img_event_box.events_box), "enter-notify-event",
        G_CALLBACK(events_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.events_box), "leave-notify-event",
        G_CALLBACK(events_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.events_box), "button_press_event",
        G_CALLBACK(events_click), NULL);    

    g_signal_connect(G_OBJECT(avatar_container), "enter-notify-event",
        G_CALLBACK(status_enter_notify), NULL);
    g_signal_connect(G_OBJECT(avatar_container), "leave-notify-event",
        G_CALLBACK(status_leave_notify), NULL);
    g_signal_connect(G_OBJECT(avatar_container), "button_press_event",
        G_CALLBACK(status_click), NULL);    

    g_signal_connect(G_OBJECT(t_img_event_box.settings_box), "enter-notify-event",
        G_CALLBACK(settings_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.settings_box), "leave-notify-event",
        G_CALLBACK(settings_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.settings_box), "button_press_event",
        G_CALLBACK(settings_click), NULL);
    //
}
