#include "../inc/client.h"

GtkWidget *create_bg_preview(int bg_num)
{
    char *path = "client/data/bg-preview/";
    path = mx_strjoin(path, mx_itoa(bg_num));
    path = mx_strjoin(path, ".png");
    GtkWidget *single = gtk_event_box_new();
    GtkWidget *drawing = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(drawing), BGPREVIEW_W, BGPREVIEW_H);
    g_signal_connect(G_OBJECT(drawing), "draw", G_CALLBACK(draw_event_bg_preview), (char*)path);
    gtk_container_add(GTK_CONTAINER(single), drawing);

    return single;
}
