#include "../inc/client.h"

void build_settings_menu(GtkWidget **stgscreen)
{
    // Loading CSS file
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/data/css/settings_scr.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    //
    // Creating workspace
    settings_scr = gtk_grid_new();
    gtk_widget_set_name(GTK_WIDGET(settings_scr), "settings_scr");                            
    gtk_widget_set_size_request(GTK_WIDGET(settings_scr), CUR_WIDTH-LEFTBAR_W, CUR_HEIGHT); 
    gtk_fixed_put(GTK_FIXED(*stgscreen), settings_scr, LEFTBAR_W, 0);                       
    GtkWidget *main = gtk_fixed_new();
    gtk_grid_attach(GTK_GRID(settings_scr), main, 0, 0, CUR_WIDTH-LEFTBAR_W, CUR_HEIGHT);
    //
}
