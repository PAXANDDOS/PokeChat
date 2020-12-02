#include "../inc/client.h"

void build_home_screen(GtkWidget **homescreen) 
{
    // Loading CSS file
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/data/css/home_screen.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    //

    // Creating workspace
    home_scr = gtk_grid_new();   // Эта падла меня задрала. Создал grid чтобы можно было применить CSS ибо в fixed нельзя.
    gtk_widget_set_name(GTK_WIDGET(home_scr), "homescreen");                            
    gtk_widget_set_size_request(GTK_WIDGET(home_scr), CUR_WIDTH-LEFTBAR_W, CUR_HEIGHT); 
    gtk_fixed_put(GTK_FIXED(*homescreen), home_scr, LEFTBAR_W, 0);                       
    GtkWidget *main = gtk_fixed_new();
    gtk_grid_attach(GTK_GRID(home_scr), main, 0, 0, CUR_WIDTH-LEFTBAR_W, CUR_HEIGHT); // Запихиваю новый fixed в первую ячейку грида, для того чтобы можно было нормально размещать элементы.
    //

    // Creating block for "ACTIVITY BANNER"
    GtkWidget *activity_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    gtk_widget_set_name(GTK_WIDGET(activity_block), "activity");                       // Имя
    gtk_widget_set_size_request(GTK_WIDGET(activity_block), ACTIVITY_W, ACTIVITY_H);   // Размер
    gtk_fixed_put(GTK_FIXED(main), activity_block, ACTIVITY_X, ACTIVITY_Y);            // Позиция
    // Label for header
    GtkWidget *active_text = gtk_label_new("ACTIVE NOW");
    gtk_widget_set_name(GTK_WIDGET(active_text), "active_text");            // Имя
    gtk_widget_set_halign(active_text, GTK_ALIGN_START);                    // Позиция текста
    gtk_box_pack_start(GTK_BOX(activity_block), active_text, FALSE, FALSE, 0); 
    // ACTIVE PERSON 1
    GtkWidget *active1_box = gtk_event_box_new();
    gtk_event_box_set_above_child (GTK_EVENT_BOX(active1_box), TRUE);
    gtk_widget_set_name(GTK_WIDGET(active1_box), "active");
    GtkWidget *active1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(active1), ACTIVE_PERSON_W, ACTIVE_PERSON_H);
    gtk_widget_set_halign(active1, GTK_ALIGN_START);
    gtk_container_add(GTK_CONTAINER(active1_box), active1);
    gtk_box_pack_start(GTK_BOX(activity_block), active1_box, FALSE, FALSE, 0);
    GtkWidget *avatar_container = gtk_fixed_new();
    gtk_widget_set_halign(avatar_container, GTK_ALIGN_START);
    GtkWidget *avatar = gtk_drawing_area_new();
    GtkWidget *status = gtk_image_new_from_file("client/data/images/status_online.png");    // Дописать функцию выбора статуса
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 35, 35);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar), (int*)35);
    gtk_box_pack_start(GTK_BOX(active1), avatar_container, FALSE, FALSE, 0);          
    gtk_fixed_put(GTK_FIXED(avatar_container), avatar, 3, 2);
    gtk_fixed_put(GTK_FIXED(avatar_container), status, 20, 20);
    GtkWidget *active1_name = gtk_label_new("PAXANDDOS");              // Получить имя
    gtk_widget_set_name(GTK_WIDGET(active1_name), "active_name");
    gtk_widget_set_halign(active1_name, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(active1), active1_name, FALSE, FALSE, 5); 
    //
    GtkWidget *active2_box = gtk_event_box_new();
    gtk_event_box_set_above_child (GTK_EVENT_BOX(active2_box), TRUE);
    gtk_widget_set_name(GTK_WIDGET(active2_box), "active");
    GtkWidget *active2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
    gtk_widget_set_size_request(GTK_WIDGET(active2), ACTIVE_PERSON_W, ACTIVE_PERSON_H);
    gtk_widget_set_halign(active2, GTK_ALIGN_START);
    gtk_container_add(GTK_CONTAINER(active2_box), active2);
    gtk_box_pack_start(GTK_BOX(activity_block), active2_box, FALSE, FALSE, 3);
    //
    GtkWidget *active3_box = gtk_event_box_new();
    gtk_event_box_set_above_child (GTK_EVENT_BOX(active3_box), TRUE);
    gtk_widget_set_name(GTK_WIDGET(active3_box), "active");
    GtkWidget *active3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
    gtk_widget_set_size_request(GTK_WIDGET(active3), ACTIVE_PERSON_W, ACTIVE_PERSON_H);
    gtk_widget_set_halign(active3, GTK_ALIGN_START);
    gtk_container_add(GTK_CONTAINER(active3_box), active3);
    gtk_box_pack_start(GTK_BOX(activity_block), active3_box, FALSE, FALSE, 3);
    //
    GtkWidget *active4_box = gtk_event_box_new();
    gtk_event_box_set_above_child (GTK_EVENT_BOX(active3_box), TRUE);
    gtk_widget_set_name(GTK_WIDGET(active4_box), "active");
    GtkWidget *active4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
    gtk_widget_set_size_request(GTK_WIDGET(active4), ACTIVE_PERSON_W, ACTIVE_PERSON_H);
    gtk_widget_set_halign(active4, GTK_ALIGN_START);
    gtk_container_add(GTK_CONTAINER(active4_box), active4);
    gtk_box_pack_start(GTK_BOX(activity_block), active4_box, FALSE, FALSE, 3);
    //
    GtkWidget *active5_box = gtk_event_box_new();
    gtk_event_box_set_above_child (GTK_EVENT_BOX(active5_box), TRUE);
    gtk_widget_set_name(GTK_WIDGET(active5_box), "active");
    GtkWidget *active5 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
    gtk_widget_set_size_request(GTK_WIDGET(active5), ACTIVE_PERSON_W, ACTIVE_PERSON_H);
    gtk_widget_set_halign(active5, GTK_ALIGN_START);
    gtk_container_add(GTK_CONTAINER(active5_box), active5);
    gtk_box_pack_start(GTK_BOX(activity_block), active5_box, FALSE, FALSE, 3);
    //

    // Creating block for "FACT BANNER"
    GtkWidget *fact_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_widget_set_name(GTK_WIDGET(fact_block), "fact");
    gtk_widget_set_size_request(GTK_WIDGET(fact_block), FACT_W, FACT_H);
    gtk_fixed_put(GTK_FIXED(main), fact_block, FACT_X, FACT_Y);
    // Label for header
    GtkWidget *fact_text = gtk_label_new("HERE'S A FACT!");
    gtk_widget_set_name(GTK_WIDGET(fact_text), "fact_text");                // Имя
    gtk_widget_set_halign(fact_text, GTK_ALIGN_CENTER);                     // Позиция текста
    gtk_box_pack_start(GTK_BOX(fact_block), fact_text, FALSE, FALSE, 0);
    //  Дописать генерацию картинки и текста к ней

    // Creating block for "WELCOMING BANNER". The latest and the hardest
    GtkWidget *welcome_container = gtk_fixed_new();                                 // Контейнер для всех блоков внутри
    GtkWidget *welcome_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);          // Главный блок
    gtk_widget_set_name(GTK_WIDGET(welcome_block), "welcome");                      // Имя
    gtk_widget_set_size_request(GTK_WIDGET(welcome_block), WELCOME_W, WELCOME_H);   // Размер
    gtk_fixed_put(GTK_FIXED(welcome_container), welcome_block, 0, 0);               // Позиция
    gtk_fixed_put(GTK_FIXED(main), welcome_container, WELCOME_X, WELCOME_Y);        // Кладем контейнер в общий экран
    // Placing linker block to messages
    GtkWidget *tomsg = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(tomsg), "tomsg");                                        // Имя
    gtk_widget_set_size_request(GTK_WIDGET(tomsg), WELCOME_LINK_W, WELCOME_LINK_H);         // Размер
    gtk_fixed_put(GTK_FIXED(welcome_container), tomsg, WELCOME_LINK_MSG_X, WELCOME_LINK_Y); // Позиция
    // Placing linker block to group chat
    GtkWidget *togroup = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(togroup), "togroup");                                        // Имя
    gtk_widget_set_size_request(GTK_WIDGET(togroup), WELCOME_LINK_W, WELCOME_LINK_H);           // Размер
    gtk_fixed_put(GTK_FIXED(welcome_container), togroup, WELCOME_LINK_GROUP_X, WELCOME_LINK_Y); // Позиция
    // Placing linker block to settings
    GtkWidget *tosettings = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(tosettings), "tosettings");                                          // Имя
    gtk_widget_set_size_request(GTK_WIDGET(tosettings), WELCOME_LINK_W, WELCOME_LINK_H);                // Размер
    gtk_fixed_put(GTK_FIXED(welcome_container), tosettings, WELCOME_LINK_SETTINGS_X, WELCOME_LINK_Y);   // Позиция
    //
    // Events
        // ACTIVITY EVENTS
    g_signal_connect(G_OBJECT(active1_box), "enter-notify-event",
        G_CALLBACK(tomsg_enter_notify), NULL);
    g_signal_connect(G_OBJECT(active1_box), "leave-notify-event",
        G_CALLBACK(tomsg_leave_notify), NULL);
    g_signal_connect(G_OBJECT(active1_box), "button_press_event",
        G_CALLBACK(tomsg_click), NULL);

    g_signal_connect(G_OBJECT(active2_box), "enter-notify-event",
        G_CALLBACK(togroup_enter_notify), NULL);
    g_signal_connect(G_OBJECT(active2_box), "leave-notify-event",
        G_CALLBACK(togroup_leave_notify), NULL);
    g_signal_connect(G_OBJECT(active2_box), "button_press_event",
        G_CALLBACK(togroup_click), NULL);

    g_signal_connect(G_OBJECT(active3_box), "enter-notify-event",
        G_CALLBACK(tosettings_enter_notify), NULL);
    g_signal_connect(G_OBJECT(active3_box), "leave-notify-event",
        G_CALLBACK(tosettings_leave_notify), NULL);
    g_signal_connect(G_OBJECT(active3_box), "button_press_event",
        G_CALLBACK(tosettings_click), NULL);

    g_signal_connect(G_OBJECT(active4_box), "enter-notify-event",
        G_CALLBACK(togroup_enter_notify), NULL);
    g_signal_connect(G_OBJECT(active4_box), "leave-notify-event",
        G_CALLBACK(togroup_leave_notify), NULL);
    g_signal_connect(G_OBJECT(active4_box), "button_press_event",
        G_CALLBACK(togroup_click), NULL);

    g_signal_connect(G_OBJECT(active5_box), "enter-notify-event",
        G_CALLBACK(tosettings_enter_notify), NULL);
    g_signal_connect(G_OBJECT(active5_box), "leave-notify-event",
        G_CALLBACK(tosettings_leave_notify), NULL);
    g_signal_connect(G_OBJECT(active5_box), "button_press_event",
        G_CALLBACK(tosettings_click), NULL);

        // WELCOME BANNER EVENTS
    g_signal_connect(G_OBJECT(tomsg), "enter-notify-event",
        G_CALLBACK(tomsg_enter_notify), NULL);
    g_signal_connect(G_OBJECT(tomsg), "leave-notify-event",
        G_CALLBACK(tomsg_leave_notify), NULL);
    g_signal_connect(G_OBJECT(tomsg), "button_press_event",
        G_CALLBACK(tomsg_click), NULL);

    g_signal_connect(G_OBJECT(togroup), "enter-notify-event",
        G_CALLBACK(togroup_enter_notify), NULL);
    g_signal_connect(G_OBJECT(togroup), "leave-notify-event",
        G_CALLBACK(togroup_leave_notify), NULL);
    g_signal_connect(G_OBJECT(togroup), "button_press_event",
        G_CALLBACK(togroup_click), NULL);

    g_signal_connect(G_OBJECT(tosettings), "enter-notify-event",
        G_CALLBACK(tosettings_enter_notify), NULL);
    g_signal_connect(G_OBJECT(tosettings), "leave-notify-event",
        G_CALLBACK(tosettings_leave_notify), NULL);
    g_signal_connect(G_OBJECT(tosettings), "button_press_event",
        G_CALLBACK(tosettings_click), NULL);
}
