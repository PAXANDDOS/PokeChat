#include "../inc/client.h"

static void load_providers()
{
    t_providers.styles = gtk_css_provider_new();
    gtk_css_provider_load_from_path(t_providers.styles, "client/data/css/styles.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.styles), GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    if(t_account.theme == 1) { 
        t_providers.theme = gtk_css_provider_new();
        gtk_css_provider_load_from_path(t_providers.theme, "client/data/css/themes/theme_light.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.theme), GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
    else if(t_account.theme == 2) {
        t_providers.theme = gtk_css_provider_new();
        gtk_css_provider_load_from_path(t_providers.theme, "client/data/css/themes/theme_default.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.theme), GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
    else if(t_account.theme == 3) { 
        t_providers.theme = gtk_css_provider_new();
        gtk_css_provider_load_from_path(t_providers.theme, "client/data/css/themes/theme_dark.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.theme), GTK_STYLE_PROVIDER_PRIORITY_USER);
    }

    if(t_account.theme == 1) { 
        t_providers.chat = gtk_css_provider_new();
        gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_light/chatbg1.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
    else if(t_account.theme == 2) {
        t_providers.chat = gtk_css_provider_new();
        gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg/chatbg1.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
    else if(t_account.theme == 3) { 
        t_providers.chat = gtk_css_provider_new();
        gtk_css_provider_load_from_path(t_providers.chat, "client/data/css/chat_bg_dark/chatbg1.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(t_providers.chat), GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
}

static void build_main_area(GtkWidget **main_area, GtkWidget **window) {
    *main_area = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(*window), *main_area);
    gtk_widget_set_size_request(GTK_WIDGET(*main_area), WINDOW_WIDTH, WINDOW_HEIGHT);
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

    t_main.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(t_main.window), "PokeChat");
    gtk_window_set_default_size(GTK_WINDOW(t_main.window), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_position(GTK_WINDOW(t_main.window), GTK_WIN_POS_CENTER);
    icon = create_pixbuf("client/data/images/logo.png");
    gtk_window_set_icon(GTK_WINDOW(t_main.window), icon);
    gtk_window_set_resizable(GTK_WINDOW(t_main.window), FALSE);

    load_providers();
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
