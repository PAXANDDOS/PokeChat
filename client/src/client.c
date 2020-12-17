#include "../inc/client.h"

static void build_main_area(GtkWidget **main_area, GtkWidget **window) {
    *main_area = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(*window), *main_area);
    gtk_widget_set_size_request(GTK_WIDGET(*main_area), CUR_WIDTH, CUR_HEIGHT);
}

int main(int argc, char *argv[]) {
    t_main.window = NULL;
    GdkPixbuf *icon = NULL;
    GtkWidget *main_area = NULL;
    GtkWidget *left_bar = NULL;

    fill_pokemon();
    test_autofill();

    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    gtk_init(&argc, &argv);
    CUR_WIDTH = 1280;
    CUR_HEIGHT = 720;

    t_main.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(t_main.window), "PokeChat");
    gtk_window_set_default_size(GTK_WINDOW(t_main.window), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_position(GTK_WINDOW(t_main.window), GTK_WIN_POS_CENTER);
    icon = create_pixbuf("client/data/images/logo.png");  
    gtk_window_set_icon(GTK_WINDOW(t_main.window), icon);
    gtk_window_set_resizable(GTK_WINDOW(t_main.window), FALSE);

    preload_images();
    
    build_main_area(&main_area, &t_main.window);
    build_all(&left_bar, &main_area);

    gtk_widget_show_all(t_main.window);
    gtk_widget_hide(GTK_WIDGET(t_main_scr.msg_scr));
    gtk_widget_hide(GTK_WIDGET(t_main_scr.settings_scr));

    g_signal_connect(t_main.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);  
    gtk_main();
    g_object_unref(icon);
    Mix_CloseAudio();
    SDL_Quit();
    free(tm_struct);

    return 0;
}
