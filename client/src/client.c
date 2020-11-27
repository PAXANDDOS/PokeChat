#include "../inc/client.h"

static GdkPixbuf *create_pixbuf(const gchar * filename) {
    
   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);
   
   if (!pixbuf) {
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}

void build_main_area(GtkWidget **main_area, GtkWidget **background, GtkWidget **window) {
    *main_area = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(*window), *main_area);
    gtk_widget_set_size_request(GTK_WIDGET(*main_area), CUR_WIDTH, CUR_HEIGHT);

    *background = gtk_drawing_area_new();

    gtk_fixed_put(GTK_FIXED(*main_area), *background, 0, 0);
    gtk_widget_set_size_request(GTK_WIDGET(*background), CUR_WIDTH, CUR_HEIGHT);
    g_signal_connect(G_OBJECT(*background), "draw",
                     G_CALLBACK(mx_draw_event_background), NULL);
    
    GtkWidget *label = gtk_label_new("Select a chat to start conversation...");
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_fixed_put(GTK_FIXED(*main_area), label, CUR_WIDTH - CUR_WIDTH / 2.5, CUR_HEIGHT / 2);
}

int main(int argc, char *argv[]) {
    GtkWidget *window = NULL;
    GdkPixbuf *icon = NULL;
    GtkWidget *main_area = NULL;
    GtkWidget *left_bar = NULL;
    //GtkWidget *entry_search = NULL;
    GtkWidget *background = NULL;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "PokeChat");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    icon = create_pixbuf("client/data/images/logo.png");  
    gtk_window_set_icon(GTK_WINDOW(window), icon);

    preload_images();
    build_main_area(&main_area, &background, &window);
    build_left_bar(&left_bar, &main_area);

    gtk_widget_show_all (window);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);  
    gtk_main();
    g_object_unref(icon);

    return 0;
}
