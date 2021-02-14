#include "../inc/client.h"

static t_chat_list *chat_create_node(t_chat_data *chat) {
    t_chat_list *new_node = NULL;
    new_node = malloc(sizeof(t_chat_list));
    new_node->chat_id = chat->chat_id;
    new_node->username = strdup(chat->title);
    if (chat->user->id) {
        new_node->avatar = chat->user->avatar;
        new_node->status = chat->user->online;
        new_node->user_id = chat->user->id;
    }
    else {
        new_node->user_id = 0;
        new_node->avatar = 999;
        new_node->members = chat->members;
    }
    new_node->next = NULL;
    return new_node;
}

void chat_push_back(t_chat_list **list, t_chat_data *chat) {
    t_chat_list *back_list = chat_create_node(chat);
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

void chat_clear_list(t_chat_list **list) {
    t_chat_list *p;
    while (*list) {
        p = NULL;
        if (list) {
            p = (*list)->next;
            free(*list);
            *list = p;
        }
    }
}

static void arrow_move_enter_event(GtkWidget *widget) {
    GtkStateFlags flags = gtk_widget_get_state_flags(GTK_WIDGET(widget));
    if (!(flags & GTK_STATE_FLAG_LINK))
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
    gtk_fixed_move(GTK_FIXED(t_msg.main), GTK_WIDGET(widget), WINDOW_WIDTH-LEFTBAR_W-40, WINDOW_HEIGHT-ENTRY_H-40);
    gtk_widget_set_size_request(GTK_WIDGET(widget), 40, 40);
}

static void arrow_move_leave_event(GtkWidget *widget) {
    GtkStateFlags flags = gtk_widget_get_state_flags(GTK_WIDGET(widget));
    if (!(flags & GTK_STATE_FLAG_LINK)) 
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
    gtk_fixed_move(GTK_FIXED(t_msg.main), GTK_WIDGET(widget), WINDOW_WIDTH-LEFTBAR_W-16, WINDOW_HEIGHT-ENTRY_H-40);
    gtk_widget_set_size_request(GTK_WIDGET(widget), 16, 40);
}

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
    gtk_box_pack_start(GTK_BOX(list_block), search_block, FALSE, FALSE, 15);
    GtkWidget *search_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(search_field), "search_field");
    g_signal_connect(G_OBJECT(search_field), "insert-text", G_CALLBACK(all_input_event), NULL);
    gtk_entry_set_placeholder_text(GTK_ENTRY(search_field), "Search for people");
    gtk_entry_set_max_length(GTK_ENTRY(search_field), MAX_USERNAME);
    gtk_box_pack_start(GTK_BOX(search_block), search_field, TRUE, TRUE, 0);
    GtkWidget *adduser = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(adduser), "adduser");
    gtk_widget_set_size_request(GTK_WIDGET(adduser), 30, 30);
    gtk_box_pack_end(GTK_BOX(search_block), adduser, FALSE, FALSE, 10);
    gtk_widget_set_halign(GTK_WIDGET(adduser), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(adduser), GTK_ALIGN_CENTER);
    tooltip("Add",adduser);
    //
    GtkWidget *dm_text = gtk_label_new("DIRECT MESSAGES");
    gtk_widget_set_name(GTK_WIDGET(dm_text), "dm_text");                 // Имя
    gtk_widget_set_halign(dm_text, GTK_ALIGN_START);                     // Позиция текста
    gtk_box_pack_start(GTK_BOX(list_block), dm_text, FALSE, FALSE, 0);
    //

    GtkWidget *group = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(group), "msggroup");
    gtk_widget_set_size_request(GTK_WIDGET(group), 40, 40);
    gtk_fixed_put(GTK_FIXED(main), group, LIST_W-50, LIST_H-50);
    tooltip("Create group",group);

    //GtkAdjustment *vadjustment = gtk_adjustment_new(0, 0, LIST_H-100, 100, 100, LIST_H-100);    // Параметры скролла
    GtkWidget *scrollable = gtk_scrolled_window_new(NULL, NULL);                 // Зона, доступная для бесконечного скролла
    gtk_widget_set_size_request(scrollable, LIST_W, LIST_H-104);
    gtk_widget_set_name(GTK_WIDGET(scrollable), "chatlist");

    t_msg.chatlist = create_chatlist();

    gtk_container_add(GTK_CONTAINER(scrollable), t_msg.chatlist);
    gtk_box_pack_start(GTK_BOX(list_block), scrollable, FALSE, FALSE, 0);              // Кладем скролл зону на главный экран
    gtk_widget_hide(gtk_scrolled_window_get_vscrollbar(GTK_SCROLLED_WINDOW(scrollable)));

    g_signal_connect(G_OBJECT(adduser), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(adduser), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(adduser), "button_press_event", G_CALLBACK(adduser_click), search_field);
    g_signal_connect(G_OBJECT(search_field), "activate", G_CALLBACK(adduser_click), search_field);

    g_signal_connect(G_OBJECT(group), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(group), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(group), "button_press_event", G_CALLBACK(msggroup_click), main);
}

static void build_entryfield(GtkWidget *main)
{
    t_msg.arrow = gtk_event_box_new();
    gtk_event_box_set_above_child(GTK_EVENT_BOX(t_msg.arrow), TRUE);
    gtk_widget_set_name(GTK_WIDGET(t_msg.arrow), "arrowdown");
    gtk_widget_set_size_request(GTK_WIDGET(t_msg.arrow), 16, 40);
    tooltip("Jump to present", t_msg.arrow);
    gtk_fixed_put(GTK_FIXED(main), t_msg.arrow, WINDOW_WIDTH-LEFTBAR_W-16, WINDOW_HEIGHT-ENTRY_H-40);

    GtkWidget *entry_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_name(GTK_WIDGET(entry_block), "entry_block");
    gtk_widget_set_size_request(GTK_WIDGET(entry_block), ENTRY_W, ENTRY_H);
    gtk_fixed_put(GTK_FIXED(main),entry_block, LIST_W, WINDOW_HEIGHT-ENTRY_H);

    GtkWidget *attach = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(attach), "attach");
    gtk_widget_set_size_request(GTK_WIDGET(attach), 40, 40);
    gtk_box_pack_start(GTK_BOX(entry_block), attach, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(attach), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(attach), GTK_ALIGN_CENTER);
    tooltip("Attach image",attach);

    t_msg.entry = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(t_msg.entry), "entry_text");
    char* entry_placeholder_text = mx_strjoin("Message ", t_msg.current);
    gtk_entry_set_placeholder_text(GTK_ENTRY(t_msg.entry), entry_placeholder_text);
    g_signal_connect(G_OBJECT(t_msg.entry), "insert-text", G_CALLBACK(all_input_event), NULL);
    gtk_entry_set_max_length(GTK_ENTRY(t_msg.entry), MAX_MESSAGE);
    gtk_box_pack_start(GTK_BOX(entry_block), t_msg.entry, TRUE, TRUE, 0);
    g_signal_connect(G_OBJECT(t_msg.entry), "changed", G_CALLBACK(entry_text_change_event), NULL);

    GtkWidget *send = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(send), "send");
    gtk_widget_set_size_request(GTK_WIDGET(send), 40, 40);
    gtk_box_pack_end(GTK_BOX(entry_block), send, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(send), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(send), GTK_ALIGN_CENTER);
    tooltip("Send",send);

    GtkWidget *sticker = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(sticker), "sticker");
    gtk_widget_set_size_request(GTK_WIDGET(sticker), 40, 40);
    gtk_box_pack_end(GTK_BOX(entry_block), sticker, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(sticker), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(sticker), GTK_ALIGN_CENTER);
    tooltip("Stickers",sticker);

    g_signal_connect(G_OBJECT(attach), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(attach), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(attach), "button_press_event", G_CALLBACK(attach_click), NULL);

    g_signal_connect(G_OBJECT(send), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(send), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(send), "button_press_event", G_CALLBACK(send_click), NULL);
    g_signal_connect(G_OBJECT(t_msg.entry), "activate", G_CALLBACK(send_press), NULL);

    g_signal_connect(G_OBJECT(sticker), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(sticker), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(sticker), "button_press_event", G_CALLBACK(sticker_click), main);

    g_signal_connect(G_OBJECT(t_msg.arrow), "enter-notify-event", G_CALLBACK(arrow_move_enter_event), NULL);
    g_signal_connect(G_OBJECT(t_msg.arrow), "leave-notify-event", G_CALLBACK(arrow_move_leave_event), NULL);
    g_signal_connect(G_OBJECT(t_msg.arrow), "button_press_event", G_CALLBACK(arrow_click), NULL);
}

static void build_chat(GtkWidget *main)
{
    GtkAdjustment *vadjustment = gtk_adjustment_new(0, 0, CHAT_H, 100, 100, CHAT_H); // Параметры скролла
    t_msg.scrolled_message = gtk_scrolled_window_new(NULL, vadjustment);             // Зона, доступная для бесконечного скролла
    gtk_widget_set_name(GTK_WIDGET(t_msg.scrolled_message), "scrollable_msg");                  // Имя 1
    gtk_widget_set_size_request(t_msg.scrolled_message, CHAT_W, CHAT_H);                        // Размер

    // g_signal_connect(G_OBJECT(t_msg.scrolled_message), "scroll_event", G_CALLBACK(scrolled), NULL);

    t_msg.chat_screen = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);                 // Главный блок с сообщениями - вертикальный, все сообщения - горизонтальные
    gtk_widget_set_size_request(t_msg.chat_screen, CHAT_W, CHAT_H);               // Размер
    gtk_widget_set_name(GTK_WIDGET(t_msg.chat_screen), "messages_block");         // Имя 2

    gtk_container_add(GTK_CONTAINER(t_msg.scrolled_message), t_msg.chat_screen);              // Кладем чат в скролл зону
    gtk_fixed_put(GTK_FIXED(main),t_msg.scrolled_message, LIST_W, 0);                           // Кладем скролл зону на главный экран
    gtk_widget_hide(gtk_scrolled_window_get_vscrollbar(GTK_SCROLLED_WINDOW(t_msg.scrolled_message)));
}

void build_messanger_screen(GtkWidget **msgscreen)
{
    // Creating workspace
    t_screen.msg_scr = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_screen.msg_scr), "messanger");
    gtk_widget_set_size_request(GTK_WIDGET(t_screen.msg_scr), WINDOW_WIDTH-LEFTBAR_W, WINDOW_HEIGHT);
    gtk_fixed_put(GTK_FIXED(*msgscreen), t_screen.msg_scr, LEFTBAR_W, 0);
    t_msg.main = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(t_screen.msg_scr), t_msg.main);
    //
    //
    build_list(t_msg.main);
    build_chat(t_msg.main);
    build_entryfield(t_msg.main);
}
