#include "../inc/client.h"

static void build_activity(GtkWidget *main)
{
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
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 35, 35);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar), (int*)35);
    gtk_box_pack_start(GTK_BOX(active1), avatar_container, FALSE, FALSE, 0);          
    gtk_fixed_put(GTK_FIXED(avatar_container), avatar, 3, 2);
    GtkWidget *active1_name = gtk_label_new("Gazaris");              // Получить имя
    gtk_widget_set_name(GTK_WIDGET(active1_name), "active_name");
    gtk_widget_set_halign(active1_name, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(active1), active1_name, FALSE, FALSE, 5); 
    
    // ACTIVE PERSON 2
    GtkWidget *active2_box = gtk_event_box_new();
    gtk_event_box_set_above_child (GTK_EVENT_BOX(active2_box), TRUE);
    gtk_widget_set_name(GTK_WIDGET(active2_box), "active");
    GtkWidget *active2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
    gtk_widget_set_size_request(GTK_WIDGET(active2), ACTIVE_PERSON_W, ACTIVE_PERSON_H);
    gtk_widget_set_halign(active2, GTK_ALIGN_START);
    gtk_container_add(GTK_CONTAINER(active2_box), active2);
    gtk_box_pack_start(GTK_BOX(activity_block), active2_box, FALSE, FALSE, 3);
    GtkWidget *avatar_container2 = gtk_fixed_new();
    gtk_widget_set_halign(avatar_container2, GTK_ALIGN_START);
    GtkWidget *avatar2 = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar2), 35, 35);
    g_signal_connect(G_OBJECT(avatar2), "draw", G_CALLBACK(draw_event_avatar), (int*)35);
    gtk_box_pack_start(GTK_BOX(active2), avatar_container2, FALSE, FALSE, 0);          
    gtk_fixed_put(GTK_FIXED(avatar_container2), avatar2, 3, 2);
    GtkWidget *active2_name = gtk_label_new("leosh1d");              // Получить имя
    gtk_widget_set_name(GTK_WIDGET(active2_name), "active_name");
    gtk_widget_set_halign(active2_name, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(active2), active2_name, FALSE, FALSE, 5); 
    //
    //
    GtkWidget *active3_box = gtk_event_box_new();
    gtk_event_box_set_above_child (GTK_EVENT_BOX(active3_box), TRUE);
    gtk_widget_set_name(GTK_WIDGET(active3_box), "active");
    GtkWidget *active3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
    gtk_widget_set_size_request(GTK_WIDGET(active3), ACTIVE_PERSON_W, ACTIVE_PERSON_H);
    gtk_widget_set_halign(active3, GTK_ALIGN_START);
    gtk_container_add(GTK_CONTAINER(active3_box), active3);
    gtk_box_pack_start(GTK_BOX(activity_block), active3_box, FALSE, FALSE, 3);
    GtkWidget *avatar_container3 = gtk_fixed_new();
    gtk_widget_set_halign(avatar_container3, GTK_ALIGN_START);
    GtkWidget *avatar3 = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar3), 35, 35);
    g_signal_connect(G_OBJECT(avatar3), "draw", G_CALLBACK(draw_event_avatar), (int*)35);
    gtk_box_pack_start(GTK_BOX(active3), avatar_container3, FALSE, FALSE, 0);          
    gtk_fixed_put(GTK_FIXED(avatar_container3), avatar3, 3, 2);
    GtkWidget *active3_name = gtk_label_new("Overwolf94");              // Получить имя
    gtk_widget_set_name(GTK_WIDGET(active3_name), "active_name");
    gtk_widget_set_halign(active3_name, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(active3), active3_name, FALSE, FALSE, 5);
    //
    GtkWidget *active4_box = gtk_event_box_new();
    gtk_event_box_set_above_child (GTK_EVENT_BOX(active4_box), TRUE);
    gtk_widget_set_name(GTK_WIDGET(active4_box), "active");
    GtkWidget *active4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
    gtk_widget_set_size_request(GTK_WIDGET(active4), ACTIVE_PERSON_W, ACTIVE_PERSON_H);
    gtk_widget_set_halign(active4, GTK_ALIGN_START);
    gtk_container_add(GTK_CONTAINER(active4_box), active4);
    gtk_box_pack_start(GTK_BOX(activity_block), active4_box, FALSE, FALSE, 3);
    GtkWidget *avatar_container4 = gtk_fixed_new();
    gtk_widget_set_halign(avatar_container4, GTK_ALIGN_START);
    GtkWidget *avatar4 = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar4), 35, 35);
    g_signal_connect(G_OBJECT(avatar4), "draw", G_CALLBACK(draw_event_avatar), (int*)35);
    gtk_box_pack_start(GTK_BOX(active4), avatar_container4, FALSE, FALSE, 0);          
    gtk_fixed_put(GTK_FIXED(avatar_container4), avatar4, 3, 2);
    GtkWidget *active4_name = gtk_label_new("dashbug");              // Получить имя
    gtk_widget_set_name(GTK_WIDGET(active4_name), "active_name");
    gtk_widget_set_halign(active4_name, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(active4), active4_name, FALSE, FALSE, 5); 
    //
    GtkWidget *active5_box = gtk_event_box_new();
    gtk_event_box_set_above_child (GTK_EVENT_BOX(active5_box), TRUE);
    gtk_widget_set_name(GTK_WIDGET(active5_box), "active");
    GtkWidget *active5 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
    gtk_widget_set_size_request(GTK_WIDGET(active5), ACTIVE_PERSON_W, ACTIVE_PERSON_H);
    gtk_widget_set_halign(active5, GTK_ALIGN_START);
    gtk_container_add(GTK_CONTAINER(active5_box), active5);
    gtk_box_pack_start(GTK_BOX(activity_block), active5_box, FALSE, FALSE, 3);
    GtkWidget *avatar_container5 = gtk_fixed_new();
    gtk_widget_set_halign(avatar_container5, GTK_ALIGN_START);
    GtkWidget *avatar5 = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar5), 35, 35);
    g_signal_connect(G_OBJECT(avatar5), "draw", G_CALLBACK(draw_event_avatar), (int*)35);
    gtk_box_pack_start(GTK_BOX(active5), avatar_container5, FALSE, FALSE, 0);          
    gtk_fixed_put(GTK_FIXED(avatar_container5), avatar5, 3, 2);
    GtkWidget *active5_name = gtk_label_new("Neulen");              // Получить имя
    gtk_widget_set_name(GTK_WIDGET(active5_name), "active_name");
    gtk_widget_set_halign(active5_name, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(active5), active5_name, FALSE, FALSE, 5); 
    //

    // ACTIVITY EVENTS
    g_signal_connect(G_OBJECT(active1_box), "enter-notify-event",
        G_CALLBACK(active1_enter_notify), NULL);
    g_signal_connect(G_OBJECT(active1_box), "leave-notify-event",
        G_CALLBACK(active1_leave_notify), NULL);
    g_signal_connect(G_OBJECT(active1_box), "button_press_event",
        G_CALLBACK(active1_click), NULL);

    g_signal_connect(G_OBJECT(active2_box), "enter-notify-event",
        G_CALLBACK(active2_enter_notify), NULL);
    g_signal_connect(G_OBJECT(active2_box), "leave-notify-event",
        G_CALLBACK(active2_leave_notify), NULL);
    g_signal_connect(G_OBJECT(active2_box), "button_press_event",
        G_CALLBACK(active2_click), NULL);

    g_signal_connect(G_OBJECT(active3_box), "enter-notify-event",
        G_CALLBACK(active3_enter_notify), NULL);
    g_signal_connect(G_OBJECT(active3_box), "leave-notify-event",
        G_CALLBACK(active3_leave_notify), NULL);
    g_signal_connect(G_OBJECT(active3_box), "button_press_event",
        G_CALLBACK(active3_click), NULL);

    g_signal_connect(G_OBJECT(active4_box), "enter-notify-event",
        G_CALLBACK(active4_enter_notify), NULL);
    g_signal_connect(G_OBJECT(active4_box), "leave-notify-event",
        G_CALLBACK(active4_leave_notify), NULL);
    g_signal_connect(G_OBJECT(active4_box), "button_press_event",
        G_CALLBACK(active4_click), NULL);

    g_signal_connect(G_OBJECT(active5_box), "enter-notify-event",
        G_CALLBACK(active5_enter_notify), NULL);
    g_signal_connect(G_OBJECT(active5_box), "leave-notify-event",
        G_CALLBACK(active5_leave_notify), NULL);
    g_signal_connect(G_OBJECT(active5_box), "button_press_event",
        G_CALLBACK(active5_click), NULL);
}

static void build_fact(GtkWidget *main)
{
    // Creating block for "FACT BANNER"
    GtkWidget *fact_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_widget_set_name(GTK_WIDGET(fact_block), "fact");
    gtk_widget_set_size_request(GTK_WIDGET(fact_block), FACT_W, FACT_H);
    gtk_fixed_put(GTK_FIXED(main), fact_block, FACT_X, FACT_Y);
    // Label for header
    GtkWidget *fact_text = gtk_label_new("──── HERE'S A FACT! ────");
    gtk_widget_set_name(GTK_WIDGET(fact_text), "fact_text");                // Имя
    gtk_widget_set_halign(fact_text, GTK_ALIGN_CENTER);                     // Позиция текста
    gtk_box_pack_start(GTK_BOX(fact_block), fact_text, FALSE, FALSE, 0);
    //  Дописать генерацию картинки и текста к ней
    GtkWidget *pokemon = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(pokemon), POKEMON_SIZE, POKEMON_SIZE);
    gtk_widget_set_halign(pokemon, GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(pokemon), "draw", G_CALLBACK(draw_event_pokemon), (int*)POKEMON_SIZE);
    gtk_box_pack_start(GTK_BOX(fact_block), pokemon, FALSE, FALSE, 0);
    pokemon_text = gtk_label_new(mx_file_to_str(pokemon_fact_text));
    gtk_label_set_line_wrap(GTK_LABEL(pokemon_text), TRUE);
    gtk_label_set_max_width_chars(GTK_LABEL(pokemon_text), 100);
    gtk_label_set_line_wrap_mode(GTK_LABEL(pokemon_text), PANGO_WRAP_WORD);
    gtk_widget_set_name(GTK_WIDGET(pokemon_text), "pokemon-text");                // Имя
    gtk_widget_set_halign(pokemon_text, GTK_ALIGN_START);                     // Позиция текста
    gtk_box_pack_start(GTK_BOX(fact_block), pokemon_text, FALSE, FALSE, 0);

    GtkWidget *pokemon_trigger = gtk_event_box_new();
    gtk_widget_set_size_request(GTK_WIDGET(pokemon_trigger), FACT_W, FACT_H);           // Размер
    gtk_fixed_put(GTK_FIXED(main), pokemon_trigger, FACT_X, FACT_Y);
    g_signal_connect(G_OBJECT(pokemon_trigger), "button_press_event",
        G_CALLBACK(play_audio), NULL);
} 

static void build_welcome(GtkWidget *main)
{
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
        // WELCOME BANNER EVENTS
    g_signal_connect(G_OBJECT(tomsg), "enter-notify-event",
        G_CALLBACK(tomsg_enter_notify), NULL);
    g_signal_connect(G_OBJECT(tomsg), "leave-notify-event",
        G_CALLBACK(tomsg_leave_notify), NULL);
    g_signal_connect(G_OBJECT(tomsg), "button_press_event",
        G_CALLBACK(messages_click), NULL);

    g_signal_connect(G_OBJECT(togroup), "enter-notify-event",
        G_CALLBACK(togroup_enter_notify), NULL);
    g_signal_connect(G_OBJECT(togroup), "leave-notify-event",
        G_CALLBACK(togroup_leave_notify), NULL);

    g_signal_connect(G_OBJECT(tosettings), "enter-notify-event",
        G_CALLBACK(tosettings_enter_notify), NULL);
    g_signal_connect(G_OBJECT(tosettings), "leave-notify-event",
        G_CALLBACK(tosettings_leave_notify), NULL);
}

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

    build_activity(main);
    build_fact(main);
    build_welcome(main);
}
