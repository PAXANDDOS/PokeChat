#include "../inc/client.h"

void build_left_bar(GtkWidget **content_selection_area, GtkWidget **main_area) 
{
    // Loading CSS file
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/data/css/theme.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    //
    // Connecting leftbar widget to CSS
    GtkWidget *left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);           // Создаем виджет
    gtk_widget_set_name(GTK_WIDGET(left_box), "leftbar");                     // Присваиваем ему имя для связи с CSS
    gtk_widget_set_size_request(GTK_WIDGET(left_box), LEFTBAR_W, CUR_HEIGHT); // Настройка размера виджета
    gtk_fixed_put(GTK_FIXED(*main_area), left_box, 0, 0);                     // Настройка позиции виджета
    //
    // Creating selection area
    *content_selection_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);             // Создаем вертикальный бокс для кнопок
    gtk_fixed_put(GTK_FIXED(*main_area), *content_selection_area, 0, 0);            // Настройка позиции
    gtk_container_set_border_width(GTK_CONTAINER(*content_selection_area), 0);      // Настройка чего-то
    gtk_widget_set_size_request(GTK_WIDGET(*content_selection_area), LEFTBAR_W, 0); // Настройка границ
    //
    // Creating selection area for settings
    GtkWidget *block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // Создаем такой же бокс, только для кнопок снизу-вверх
    gtk_fixed_put(GTK_FIXED(*main_area), block, 0, 590);         // 640
    gtk_container_set_border_width(GTK_CONTAINER(block), 0);
    gtk_widget_set_size_request(GTK_WIDGET(block), LEFTBAR_W, 0);
    //
    // Placing icons
    gtk_box_pack_start(GTK_BOX(*content_selection_area),
        t_img_event_box.home_box, TRUE, FALSE, LEFTBAR_GAP);            // Вызываем функцию ддя размещения иконки из бокса
    gtk_widget_set_halign(t_img_event_box.home_box, GTK_ALIGN_CENTER);  // Центрируем

    gtk_box_pack_start(GTK_BOX(*content_selection_area),
        t_img_event_box.messages_box, TRUE, FALSE, LEFTBAR_GAP);
    gtk_widget_set_halign(t_img_event_box.messages_box, GTK_ALIGN_CENTER);

    gtk_box_pack_start(GTK_BOX(*content_selection_area),
        t_img_event_box.group_box, TRUE, FALSE, LEFTBAR_GAP);
    gtk_widget_set_halign(t_img_event_box.group_box, GTK_ALIGN_CENTER);

    gtk_box_pack_start(GTK_BOX(*content_selection_area),
        t_img_event_box.events_box, TRUE, FALSE, LEFTBAR_GAP);
    gtk_widget_set_halign(t_img_event_box.events_box, GTK_ALIGN_CENTER);

    gtk_box_pack_start(GTK_BOX(block),
        t_img_event_box.status_box, TRUE, FALSE, LEFTBAR_GAP);          // Вернутся после реализации выбора аватара
    gtk_widget_set_halign(t_img_event_box.status_box, GTK_ALIGN_CENTER); 
    
    gtk_box_pack_start(GTK_BOX(block),
        t_img_event_box.settings_box, TRUE, FALSE, LEFTBAR_GAP);
    gtk_widget_set_halign(t_img_event_box.settings_box, GTK_ALIGN_CENTER); 
    //
    // Checking for events
    int ch = 1;
    gpointer data;
    data = GINT_TO_POINTER(ch);
    g_signal_connect(G_OBJECT(t_img_event_box.home_box), "enter-notify-event",   // Проверка на наведение мыши,                                                                      
        G_CALLBACK(home_enter_notify), NULL);                                    // G_OBJECT - бокс с картинкой,
    g_signal_connect(G_OBJECT(t_img_event_box.home_box), "leave-notify-event",   // "...-...-event" ивенты из библиотеки,
        G_CALLBACK(home_leave_notify), NULL);                                    // G_CALLBACK функция которая вызывается при действии.
    g_signal_connect(G_OBJECT(t_img_event_box.home_box), "button_press_event",   // gpointer - для доп. данных
        G_CALLBACK(home_click), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.home_box), "button_press_event",
        G_CALLBACK(goto_home), data);

    g_signal_connect(G_OBJECT(t_img_event_box.messages_box), "enter-notify-event",
        G_CALLBACK(messages_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.messages_box), "leave-notify-event",
        G_CALLBACK(messages_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.messages_box), "button_press_event",
        G_CALLBACK(messages_click), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.home_box), "button_press_event",
        G_CALLBACK(goto_msg), data);

    g_signal_connect(G_OBJECT(t_img_event_box.settings_box), "enter-notify-event",
        G_CALLBACK(settings_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.settings_box), "leave-notify-event",
        G_CALLBACK(settings_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.settings_box), "button_press_event",
        G_CALLBACK(settings_click), NULL);
    //
    ch = GPOINTER_TO_INT(data);
    if(ch == 1) {
        GtkWidget *home_screen = NULL;
        build_home_screen(&home_screen, main_area);
    }
    else if(ch == 2) {
        GtkWidget *msg_screen = NULL;
        build_messanger_screen(&msg_screen, main_area);
    }
}
