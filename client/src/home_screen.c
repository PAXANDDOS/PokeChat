#include "../inc/client.h"

void build_home_screen(GtkWidget **content_selection_area, GtkWidget **main_area) 
{
    // Loading CSS file
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/data/css/theme.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    //
    // Connecting leftbar widget to CSS
    GtkWidget *left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(left_box), "homescreen");
    gtk_widget_set_size_request(GTK_WIDGET(left_box), CUR_WIDTH-93, CUR_HEIGHT); 
    gtk_fixed_put(GTK_FIXED(*main_area), left_box, 93, 0);
    //
    // Creating selection area
    *content_selection_area = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_fixed_put(GTK_FIXED(*main_area), *content_selection_area, 0, 0);
    gtk_container_set_border_width(GTK_CONTAINER(*content_selection_area), 0);
    gtk_widget_set_size_request(GTK_WIDGET(*content_selection_area), CUR_WIDTH-100, 0);
    //
}
