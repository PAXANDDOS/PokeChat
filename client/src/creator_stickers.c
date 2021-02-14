#include "../inc/client.h"

static void onsticker_click(GtkWidget *widget) {
    GList *parent = gtk_container_get_children(GTK_CONTAINER(widget));
    GList *children = gtk_container_get_children(GTK_CONTAINER(parent->data));
    int sticker_id = atoi((char*)gtk_label_get_text(GTK_LABEL(children->data)));
    new_outgoing_sticker(t_msg.chat_screen, sticker_id);
    gtk_widget_destroy(GTK_WIDGET(t_msg.stickers));
    if(widget) {}
    sticker_data.chat_id = msg_data.chat_id;
    sticker_data.sticker_id = sticker_id;
    pthread_t thread = NULL;
    pthread_create(&thread, NULL, send_sticker, NULL);
    g_list_free(g_steal_pointer(&children));
    g_list_free(g_steal_pointer(&parent));
}

static GtkWidget *create_list(int sticker_num)
{
    char *path = "client/data/stickers/";
    path = mx_strjoin(path, mx_itoa(sticker_num));
    path = mx_strjoin(path, ".png");
    GtkWidget *single = gtk_event_box_new();
    GtkWidget *fixed = gtk_fixed_new();

    GtkWidget *key = gtk_label_new(mx_itoa(sticker_num));
    gtk_fixed_put(GTK_FIXED(fixed), key, 0, 0);
    gtk_widget_set_name(GTK_WIDGET(key), "hidden");

    GtkWidget *drawing = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(drawing), 70, 70);
    g_signal_connect(G_OBJECT(drawing), "draw", G_CALLBACK(draw_event_sticker_list), (char*)path);
    gtk_fixed_put(GTK_FIXED(fixed), drawing, 0, 0);

    gtk_container_add(GTK_CONTAINER(single), fixed);

    return single;
}

void create_stickerlist(GtkWidget *main)
{
    t_msg.stickers = gtk_event_box_new();
    gtk_widget_set_size_request(GTK_WIDGET(t_msg.stickers), WINDOW_WIDTH-LEFTBAR_W, WINDOW_HEIGHT);
    g_signal_connect(G_OBJECT(t_msg.stickers), "button_press_event", G_CALLBACK(gtk_widget_destroy), NULL);
    gtk_fixed_put(GTK_FIXED(main), t_msg.stickers, 0, 0);

    GtkWidget *positionable = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(t_msg.stickers), positionable);

    GtkWidget *clickable = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(clickable), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(clickable), GTK_ALIGN_END);
    g_signal_connect(G_OBJECT(clickable), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);
    gtk_fixed_put(GTK_FIXED(positionable), clickable, WINDOW_WIDTH-380, WINDOW_HEIGHT-ENTRY_H-360);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(box), "stickerlist");
    gtk_container_add(GTK_CONTAINER(clickable), box);

    GtkWidget *scrollable = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(scrollable), 280, 350);
    gtk_box_pack_start(GTK_BOX(box), scrollable, FALSE, FALSE, 0);

    GtkWidget *stickers = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(stickers), 0);
    gtk_grid_set_column_spacing(GTK_GRID(stickers), 0);
    int sticker_num = 1;
    int i = 0;
    int j = 0;
    GtkWidget *single;
    for(i = 1; i <= 11; i++)    // Columns
    {
        for(j = 1; j <= 4; j++) // Rows
        {
            single = create_list(sticker_num);
            gtk_widget_set_size_request(GTK_WIDGET(single), 70, 70);
            gtk_grid_attach(GTK_GRID(stickers), single, j, i, 1, 1);
            gtk_widget_set_name(GTK_WIDGET(single), "stickers");
            g_signal_connect(G_OBJECT(single), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
            g_signal_connect(G_OBJECT(single), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
            g_signal_connect(G_OBJECT(single), "button_press_event", G_CALLBACK(onsticker_click), NULL);
            sticker_num++;
            if(sticker_num > 42) break;
        }
    }
    gtk_container_add(GTK_CONTAINER(scrollable), stickers);

    gtk_widget_show_all(GTK_WIDGET(t_msg.stickers));
}
