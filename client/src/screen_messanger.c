#include "../inc/client.h"

static void build_list(GtkWidget *main)
{
    GtkWidget *list_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(list_block), "list");                       // Имя
    gtk_widget_set_size_request(GTK_WIDGET(list_block), LIST_W, LIST_H);   // Размер
    gtk_fixed_put(GTK_FIXED(main), list_block, 0, 0);            // Позиция
    //
    GtkWidget *search_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_name(GTK_WIDGET(search_block), "search_block");
    gtk_widget_set_size_request(GTK_WIDGET(search_block), 350, 40);
    gtk_box_pack_start(GTK_BOX(list_block), search_block, FALSE, TRUE, 15); 
    GtkWidget *search_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(search_field), "search_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(search_field), "Search for people");
    gtk_entry_set_max_length(GTK_ENTRY(search_field), 35);
    gtk_box_pack_start(GTK_BOX(search_block), search_field, TRUE, TRUE, 0); 
    GtkWidget *adduser = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(adduser), "adduser");
    gtk_widget_set_size_request(GTK_WIDGET(adduser), 22, 22);
    gtk_box_pack_start(GTK_BOX(search_block), adduser, FALSE, FALSE, 10);
    gtk_widget_set_halign(GTK_WIDGET(adduser), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(adduser), GTK_ALIGN_CENTER);
    //
    GtkWidget *dm_text = gtk_label_new("DIRECT MESSAGES");
    gtk_widget_set_name(GTK_WIDGET(dm_text), "dm_text");                // Имя
    gtk_widget_set_halign(dm_text, GTK_ALIGN_START);                     // Позиция текста
    gtk_box_pack_start(GTK_BOX(list_block), dm_text, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(adduser), "enter-notify-event",
        G_CALLBACK(adduser_enter_notify), NULL);
    g_signal_connect(G_OBJECT(adduser), "leave-notify-event",
        G_CALLBACK(adduser_leave_notify), NULL);
    g_signal_connect(G_OBJECT(adduser), "button_press_event",
        G_CALLBACK(adduser_click), NULL);
}

static void build_entryfield(GtkWidget *main)
{
    GtkWidget *entry_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_name(GTK_WIDGET(entry_block), "entry_block");
    gtk_widget_set_size_request(GTK_WIDGET(entry_block), ENTRY_W, ENTRY_H);
    gtk_fixed_put(GTK_FIXED(main),entry_block, LIST_W, WINDOW_HEIGHT-ENTRY_H);

    GtkWidget *attach = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(attach), "attach");
    gtk_widget_set_size_request(GTK_WIDGET(attach), 26, 26);
    gtk_box_pack_start(GTK_BOX(entry_block), attach, FALSE, FALSE, 15);
    gtk_widget_set_halign(GTK_WIDGET(attach), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(attach), GTK_ALIGN_CENTER);

    GtkWidget *entry_text = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(entry_text), "entry_text");
    char* entry_placeholder_text = mx_strjoin("Message ", current_user_dm);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_text), entry_placeholder_text);
    gtk_entry_set_max_length(GTK_ENTRY(entry_text), 35);
    gtk_box_pack_start(GTK_BOX(entry_block), entry_text, TRUE, TRUE, 0);

    GtkWidget *send = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(send), "send");
    gtk_widget_set_size_request(GTK_WIDGET(send), 26, 26);
    gtk_box_pack_end(GTK_BOX(entry_block), send, FALSE, FALSE, 15);
    gtk_widget_set_halign(GTK_WIDGET(send), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(send), GTK_ALIGN_CENTER);

    GtkWidget *sticker = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(sticker), "sticker");
    gtk_widget_set_size_request(GTK_WIDGET(sticker), 26, 26);
    gtk_box_pack_end(GTK_BOX(entry_block), sticker, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(sticker), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(sticker), GTK_ALIGN_CENTER);

    g_signal_connect(G_OBJECT(attach), "enter-notify-event",
        G_CALLBACK(attach_enter_notify), NULL);
    g_signal_connect(G_OBJECT(attach), "leave-notify-event",
        G_CALLBACK(attach_leave_notify), NULL);
    g_signal_connect(G_OBJECT(attach), "button_press_event",
        G_CALLBACK(attach_click), NULL);

    g_signal_connect(G_OBJECT(send), "enter-notify-event",
        G_CALLBACK(send_enter_notify), NULL);
    g_signal_connect(G_OBJECT(send), "leave-notify-event",
        G_CALLBACK(send_leave_notify), NULL);
    g_signal_connect(G_OBJECT(send), "button_press_event",
        G_CALLBACK(send_click), NULL);

    g_signal_connect(G_OBJECT(sticker), "enter-notify-event",
        G_CALLBACK(sticker_enter_notify), NULL);
    g_signal_connect(G_OBJECT(sticker), "leave-notify-event",
        G_CALLBACK(sticker_leave_notify), NULL);
    g_signal_connect(G_OBJECT(sticker), "button_press_event",
        G_CALLBACK(sticker_click), NULL);
}

static void new_outgoing_message(GtkWidget *messages_block)
{
    GtkWidget *messages_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    //gtk_widget_set_size_request(messages_body, CHAT_W, 100);
    gtk_widget_set_name(GTK_WIDGET(messages_body), "messages_body");

    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 35, 35);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar), (int*)35);
    gtk_box_pack_end(GTK_BOX(messages_body), avatar, FALSE, FALSE, 0);
    GtkWidget *message = gtk_label_new(mx_file_to_str(pokemon_fact_text));
    gtk_widget_set_name(GTK_WIDGET(message), "message");
    gtk_label_set_line_wrap(GTK_LABEL(message), TRUE);
    //gtk_label_set_line_wrap_mode(GTK_LABEL(message), PANGO_WRAP_WORD);
    gtk_label_set_max_width_chars(GTK_LABEL(message), 50);
    //GtkWidget *nickname = gtk_frame_new("PAXANDDOS");
    //gtk_frame_set_label_widget (GTK_FRAME(nickname), message);

    gtk_box_pack_end(GTK_BOX(messages_body), message, FALSE, FALSE, 0);

    gtk_box_pack_end(GTK_BOX(messages_block), messages_body, FALSE, FALSE, 0);
}

static void build_chat(GtkWidget *main)
{
    GtkWidget *scrollable = gtk_layout_new(NULL, NULL);                     // Зона, доступная для бесконечного скролла
    gtk_widget_set_name(GTK_WIDGET(scrollable), "scrollable_msg");          // Имя 1
    gtk_layout_set_size(GTK_LAYOUT(scrollable), CHAT_W, CHAT_H);            // Размер скроллабельной зоны
    gtk_widget_set_size_request(scrollable, CHAT_W, CHAT_H);                // То же самое, но надо

    GtkWidget *messages_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);   // Главный блок с сообщениями - вертикальный, все сообщения - горизонтальные
    gtk_widget_set_size_request(messages_block, CHAT_W, CHAT_H);            // 
    gtk_widget_set_name(GTK_WIDGET(messages_block), "messages_block");      // Имя 2

    new_outgoing_message(messages_block);                                   // Передавать как параметры: имя, фото, текст сообщения

    gtk_layout_put(GTK_LAYOUT(scrollable), messages_block, 0, 0);           // Кладем блок с сообщениями в скролл зону
    gtk_fixed_put(GTK_FIXED(main),scrollable, LIST_W, 0);                   // Кладем скролл зону на главный экран
}

void build_messanger_screen(GtkWidget **msgscreen) 
{
    // Loading CSS file
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/data/css/msg_screen.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    //
    // Creating workspace
    msg_scr = gtk_grid_new();
    gtk_widget_set_name(GTK_WIDGET(msg_scr), "messanger");                            
    gtk_widget_set_size_request(GTK_WIDGET(msg_scr), CUR_WIDTH-LEFTBAR_W, CUR_HEIGHT); 
    gtk_fixed_put(GTK_FIXED(*msgscreen), msg_scr, LEFTBAR_W, 0);                       
    GtkWidget *main = gtk_fixed_new();
    gtk_grid_attach(GTK_GRID(msg_scr), main, 0, 0, CUR_WIDTH-LEFTBAR_W, CUR_HEIGHT);
    //
    //
    build_list(main);
    build_entryfield(main);
    build_chat(main);
}
