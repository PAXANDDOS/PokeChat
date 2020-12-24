#include "../inc/client.h"

static void s_click(GtkWidget *widget) {
    gtk_widget_destroy(GTK_WIDGET(widget));
}

static void s2_click(GtkWidget *widget) {
    if(widget) {}
}

static void onsticker_click(GtkWidget *widget) {
    GList *parent = gtk_container_get_children(GTK_CONTAINER(widget));
    GList *children = gtk_container_get_children(GTK_CONTAINER(parent->data));
    char* chosen = (char*)gtk_label_get_text(GTK_LABEL(children->data));
    // chosen - > send sticker
    printf("Sticker: %s\n", chosen);
    if(chosen) {}
    gtk_widget_destroy(GTK_WIDGET(t_chat.stickers));
    if(widget) {}
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
    t_chat.stickers = gtk_event_box_new();
    gtk_widget_set_size_request(GTK_WIDGET(t_chat.stickers), WINDOW_WIDTH-90, WINDOW_HEIGHT-ENTRY_H);
    g_signal_connect(G_OBJECT(t_chat.stickers), "button_press_event", G_CALLBACK(s_click), NULL);
    gtk_fixed_put(GTK_FIXED(main), t_chat.stickers, 0, 0);

    GtkWidget *clickable = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(clickable), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(clickable), GTK_ALIGN_END);
    g_signal_connect(G_OBJECT(clickable), "button_press_event", G_CALLBACK(s2_click), NULL);
    gtk_container_add(GTK_CONTAINER(t_chat.stickers), clickable);

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
        if(sticker_num > 42) break;
    }
    gtk_container_add(GTK_CONTAINER(scrollable), stickers);

    gtk_widget_show_all(GTK_WIDGET(t_chat.stickers));
}
