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

    // // ACTIVE PEOPLE
    // GtkWidget *active_box = gtk_event_box_new();
    // gtk_event_box_set_above_child(GTK_EVENT_BOX(active_box), TRUE);
    // gtk_widget_set_name(GTK_WIDGET(active_box), "active");
    // gtk_box_pack_start(GTK_BOX(activity_block), active_box, FALSE, FALSE, 0);

    // GtkWidget *active = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    // gtk_widget_set_size_request(GTK_WIDGET(active), ACTIVE_PERSON_W, ACTIVE_PERSON_H);
    // gtk_widget_set_halign(active, GTK_ALIGN_START);
    // gtk_container_add(GTK_CONTAINER(active_box), active);

    // GtkWidget *avatar = gtk_drawing_area_new();
    // gtk_widget_set_size_request(GTK_WIDGET(avatar), 35, 35);
    // gtk_widget_set_halign(avatar, GTK_ALIGN_START);
    // gtk_widget_set_valign(avatar, GTK_ALIGN_START);
    // g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar), (int*)35);
    // gtk_box_pack_start(GTK_BOX(active), avatar, FALSE, FALSE, 0);

    // GtkWidget *active_name = gtk_label_new("Gazaris");              // Получить имя
    // gtk_widget_set_name(GTK_WIDGET(active_name), "active_name");
    // gtk_widget_set_halign(active_name, GTK_ALIGN_START);
    // gtk_box_pack_start(GTK_BOX(active), active_name, FALSE, FALSE, 0);

    // g_signal_connect(G_OBJECT(active_box), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    // g_signal_connect(G_OBJECT(active_box), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    // g_signal_connect(G_OBJECT(active_box), "button_press_event", G_CALLBACK(active_click), NULL);
}

static void build_fact(GtkWidget *main)
{
    // Creating block for "FACT BANNER"
    GtkWidget *fact_block = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(fact_block), "fact");
    gtk_event_box_set_above_child(GTK_EVENT_BOX(fact_block), TRUE);
    gtk_widget_set_size_request(GTK_WIDGET(fact_block), FACT_W, FACT_H);
    gtk_fixed_put(GTK_FIXED(main), fact_block, FACT_X, FACT_Y);
    tooltip("Play sound",fact_block);

    GtkWidget *fact_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_widget_set_name(GTK_WIDGET(fact_box), "fact_box");
    gtk_widget_set_size_request(GTK_WIDGET(fact_box), FACT_W, FACT_H);
    gtk_container_add(GTK_CONTAINER(fact_block), fact_box);
    
    GtkWidget *fact_text = gtk_label_new("───── DID YOU KNOW? ─────");      // Label for header
    gtk_widget_set_name(GTK_WIDGET(fact_text), "fact_text");                // Имя
    gtk_widget_set_halign(fact_text, GTK_ALIGN_CENTER);                     // Позиция текста
    gtk_box_pack_start(GTK_BOX(fact_box), fact_text, FALSE, FALSE, 0);

    GtkWidget *pokemon = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(pokemon), POKEMON_SIZE, POKEMON_SIZE);
    gtk_widget_set_halign(pokemon, GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(pokemon), "draw", G_CALLBACK(draw_event_pokemon), (int*)POKEMON_SIZE);
    gtk_box_pack_start(GTK_BOX(fact_box), pokemon, FALSE, FALSE, 0);
    t_pokefact.pokemon_text = gtk_label_new(mx_file_to_str(t_pokefact.pokemon_fact_text));
    gtk_label_set_line_wrap(GTK_LABEL(t_pokefact.pokemon_text), TRUE);
    gtk_label_set_max_width_chars(GTK_LABEL(t_pokefact.pokemon_text), 100);
    gtk_label_set_line_wrap_mode(GTK_LABEL(t_pokefact.pokemon_text), PANGO_WRAP_WORD);
    gtk_widget_set_name(GTK_WIDGET(t_pokefact.pokemon_text), "pokemon-text");
    gtk_widget_set_halign(t_pokefact.pokemon_text, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(fact_box), t_pokefact.pokemon_text, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(fact_block), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(fact_block), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(fact_block), "button_press_event", G_CALLBACK(event_play_audio), (gpointer)(intptr_t)SOUND_POKEMON);
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
    GtkWidget *tomsg_inner = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(tomsg_inner), "tomsg_inner");
    gtk_container_add(GTK_CONTAINER(tomsg), tomsg_inner);
    gtk_fixed_put(GTK_FIXED(welcome_container), tomsg, WELCOME_LINK_MSG_X, WELCOME_LINK_Y); // Позиция
    // Placing linker block to group chat
    GtkWidget *togroup = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(togroup), "togroup");                                        // Имя
    gtk_widget_set_size_request(GTK_WIDGET(togroup), WELCOME_LINK_W, WELCOME_LINK_H);           // Размер
    GtkWidget *togroup_inner = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(togroup_inner), "togroup_inner");
    gtk_container_add(GTK_CONTAINER(togroup), togroup_inner);
    gtk_fixed_put(GTK_FIXED(welcome_container), togroup, WELCOME_LINK_GROUP_X, WELCOME_LINK_Y); // Позиция
    // Placing linker block to settings
    GtkWidget *tosettings = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(tosettings), "tosettings");                                          // Имя
    gtk_widget_set_size_request(GTK_WIDGET(tosettings), WELCOME_LINK_W, WELCOME_LINK_H);                // Размер
    GtkWidget *tosettings_inner = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(tosettings_inner), "tosettings_inner");
    gtk_container_add(GTK_CONTAINER(tosettings), tosettings_inner);
    gtk_fixed_put(GTK_FIXED(welcome_container), tosettings, WELCOME_LINK_SETTINGS_X, WELCOME_LINK_Y);   // Позиция
    //
    // Events
    g_signal_connect(G_OBJECT(tomsg), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(tomsg), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(tomsg_inner), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(tomsg_inner), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(tomsg), "button_press_event", G_CALLBACK(messages_click), NULL);

    g_signal_connect(G_OBJECT(togroup), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(togroup), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(togroup_inner), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(togroup_inner), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(togroup), "button_press_event", G_CALLBACK(group_click), NULL);

    g_signal_connect(G_OBJECT(tosettings), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(tosettings), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(tosettings_inner), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(tosettings_inner), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(tosettings), "button_press_event", G_CALLBACK(settings_click), NULL);
}

void build_home_screen(GtkWidget **homescreen)
{
    // Creating workspace
    t_screen.home_scr = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_screen.home_scr), "homescreen");
    gtk_widget_set_size_request(GTK_WIDGET(t_screen.home_scr), WINDOW_WIDTH-LEFTBAR_W, WINDOW_HEIGHT);
    gtk_fixed_put(GTK_FIXED(*homescreen), t_screen.home_scr, LEFTBAR_W, 0);
    GtkWidget *main = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(t_screen.home_scr), main);
    //

    build_activity(main);
    build_fact(main);
    build_welcome(main);
}
