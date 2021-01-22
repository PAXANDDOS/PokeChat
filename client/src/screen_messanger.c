#include "../inc/client.h"

static t_chat_list *chat_create_node(char *nickname, int avatar, bool status) {
    t_chat_list *new_node = NULL;
    new_node = malloc(sizeof(t_chat_list));
    new_node->nickname = nickname;
    new_node->avatar = avatar;
    new_node->status = status;
    new_node->next = NULL;
    return new_node;
}

void chat_push_back(t_chat_list **list, char *nickname, int avatar, bool status) {
    t_chat_list *back_list = chat_create_node(nickname, avatar, status);
    t_chat_list *p = NULL;
    if (list == NULL || *list == NULL)
        *list = back_list;
    else {
        p = *list;
        while (p->next != NULL)
            p = p->next;
        p->next = back_list;
    }
}

// static void chat_clear_list(t_chat_list **list) {
//     t_chat_list *p;
//     while (*list) {
//         p = NULL;
//         if (list) {
//             p = (*list)->next;
//             free(*list);
//             *list = p;
//         }
//     }
// }

static void build_list(GtkWidget *main)
{
    GtkWidget *list_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(list_block), "list");                    // Имя
    gtk_widget_set_size_request(GTK_WIDGET(list_block), LIST_W, LIST_H);    // Размер
    gtk_fixed_put(GTK_FIXED(main), list_block, 0, 0);                       // Позиция
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
    gtk_widget_set_name(GTK_WIDGET(dm_text), "dm_text");                 // Имя
    gtk_widget_set_halign(dm_text, GTK_ALIGN_START);                     // Позиция текста
    gtk_box_pack_start(GTK_BOX(list_block), dm_text, FALSE, FALSE, 0);
    //

    GtkWidget *group = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(group), "msggroup");
    gtk_widget_set_size_request(GTK_WIDGET(group), 50, 50);
    gtk_fixed_put(GTK_FIXED(main), group, LIST_W-68, LIST_H-66);

    //GtkAdjustment *vadjustment = gtk_adjustment_new(0, 0, LIST_H-100, 100, 100, LIST_H-100);    // Параметры скролла
    GtkWidget *scrollable = gtk_scrolled_window_new(NULL, NULL);                 // Зона, доступная для бесконечного скролла
    gtk_widget_set_size_request(scrollable, LIST_W, LIST_H-104);
    gtk_widget_set_name(GTK_WIDGET(scrollable), "chatlist");

    chat_push_back(&tchatlist, "Neulen", 25, false);
    chat_push_back(&tchatlist, "Gazaris", 36, true);
    chat_push_back(&tchatlist, "dashbug", 40, true);
    chat_push_back(&tchatlist, "Savolus", 89, false);
    chat_push_back(&tchatlist, "Overwolf", 5, false);
    chat_push_back(&tchatlist, "sp", 99, true);
    chat_push_back(&tchatlist, "if", 65, false);
    t_msg.chatlist = create_chatlist();

    gtk_container_add(GTK_CONTAINER(scrollable), t_msg.chatlist);
    gtk_box_pack_start(GTK_BOX(list_block), scrollable, FALSE, FALSE, 0);              // Кладем скролл зону на главный экран

    g_signal_connect(G_OBJECT(adduser), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(adduser), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(adduser), "button_press_event", G_CALLBACK(adduser_click), search_field);

    g_signal_connect(G_OBJECT(group), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(group), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(group), "button_press_event", G_CALLBACK(msggroup_click), main);
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
    char* entry_placeholder_text = mx_strjoin("Message ", t_msg.current);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_text), entry_placeholder_text);
    gtk_entry_set_max_length(GTK_ENTRY(entry_text), 1000);
    gtk_box_pack_start(GTK_BOX(entry_block), entry_text, TRUE, TRUE, 0);
    g_signal_connect(G_OBJECT(entry_text), "changed", G_CALLBACK(entry_text_change_event), NULL);

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

    GtkWidget *arrow = gtk_event_box_new();
    gtk_event_box_set_above_child(GTK_EVENT_BOX(arrow), TRUE);
    gtk_widget_set_name(GTK_WIDGET(arrow), "arrowdown");
    gtk_widget_set_size_request(GTK_WIDGET(arrow), 44, 44);
    gtk_fixed_put(GTK_FIXED(main), arrow, WINDOW_WIDTH-130, WINDOW_HEIGHT-120);

    g_signal_connect(G_OBJECT(attach), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(attach), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(attach), "button_press_event", G_CALLBACK(attach_click), NULL);

    g_signal_connect(G_OBJECT(send), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(send), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(send), "button_press_event", G_CALLBACK(send_click), entry_text);
    g_signal_connect(G_OBJECT(entry_text), "activate", G_CALLBACK(send_press), NULL);

    g_signal_connect(G_OBJECT(sticker), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(sticker), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(sticker), "button_press_event", G_CALLBACK(sticker_click), main);

    g_signal_connect(G_OBJECT(arrow), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(arrow), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    //g_signal_connect(G_OBJECT(arrow), "button_press_event", G_CALLBACK(attach_click), NULL);
}

static void build_chat(GtkWidget *main)
{
    GtkAdjustment *vadjustment = gtk_adjustment_new(0, 0, CHAT_H, 100, 100, CHAT_H); // Параметры скролла
    scrolled_message = gtk_scrolled_window_new(NULL, vadjustment);             // Зона, доступная для бесконечного скролла
    gtk_widget_set_name(GTK_WIDGET(scrolled_message), "scrollable_msg");                  // Имя 1
    gtk_widget_set_size_request(scrolled_message, CHAT_W, CHAT_H);                        // Размер

    t_chat.chat_screen = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);                 // Главный блок с сообщениями - вертикальный, все сообщения - горизонтальные
    gtk_widget_set_size_request(t_chat.chat_screen, CHAT_W, CHAT_H);               // Размер
    gtk_widget_set_name(GTK_WIDGET(t_chat.chat_screen), "messages_block");         // Имя 2

    gtk_container_add(GTK_CONTAINER(scrolled_message), t_chat.chat_screen);              // Кладем чат в скролл зону
    gtk_fixed_put(GTK_FIXED(main),scrolled_message, LIST_W, 0);                           // Кладем скролл зону на главный экран
}

void build_messanger_screen(GtkWidget **msgscreen)
{
    // Creating workspace
    t_leftbar.msg_scr = gtk_grid_new();
    gtk_widget_set_name(GTK_WIDGET(t_leftbar.msg_scr), "messanger");
    gtk_widget_set_size_request(GTK_WIDGET(t_leftbar.msg_scr), WINDOW_WIDTH-LEFTBAR_W, WINDOW_HEIGHT);
    gtk_fixed_put(GTK_FIXED(*msgscreen), t_leftbar.msg_scr, LEFTBAR_W, 0);
    t_msg.main = gtk_fixed_new();
    gtk_grid_attach(GTK_GRID(t_leftbar.msg_scr), t_msg.main, 0, 0, WINDOW_WIDTH-LEFTBAR_W, WINDOW_HEIGHT);
    //
    //
    build_list(t_msg.main);
    build_chat(t_msg.main);
    build_entryfield(t_msg.main);
}
