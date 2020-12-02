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

static void build_main_area(GtkWidget **main_area, GtkWidget **window) {
    *main_area = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(*window), *main_area);
    gtk_widget_set_size_request(GTK_WIDGET(*main_area), CUR_WIDTH, CUR_HEIGHT);
}

int main(int argc, char *argv[]) {
    GtkWidget *window = NULL;
    GdkPixbuf *icon = NULL;
    GtkWidget *main_area = NULL;
    GtkWidget *left_bar = NULL;

    gtk_init(&argc, &argv);
    CUR_WIDTH = 1280;
    CUR_HEIGHT = 720;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "PokeChat");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    icon = create_pixbuf("client/data/images/logo.png");  
    gtk_window_set_icon(GTK_WINDOW(window), icon);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    preload_images();
    avatar_generated = avatar_random();
    build_main_area(&main_area, &window);
    build_all(&left_bar, &main_area);

    gtk_widget_show_all(window);
    gtk_widget_hide(GTK_WIDGET(msg_scr));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);  
    gtk_main();
    g_object_unref(icon);

    return 0;
}
