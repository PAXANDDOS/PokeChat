#include "../inc/client.h"

void build_messanger_screen(GtkWidget **content_selection_area, GtkWidget **main_area) 
{
    // Loading CSS file
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/data/css/theme.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    //
    // Connecting leftbar widget to CSS
    GtkWidget *msg_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);                   // Создаем виджет
    gtk_widget_set_name(GTK_WIDGET(msg_box), "messanger");                             // Присваиваем ему имя для связи с CSS
    gtk_widget_set_size_request(GTK_WIDGET(msg_box), CUR_WIDTH-LEFTBAR_W, CUR_HEIGHT); // Настройка размера виджета
    gtk_fixed_put(GTK_FIXED(*main_area), msg_box, LEFTBAR_W, 0);                       // Настройка позиции виджета
    //
    // Creating selection area
    *content_selection_area = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_fixed_put(GTK_FIXED(*main_area), *content_selection_area, 0, 0);
    gtk_container_set_border_width(GTK_CONTAINER(*content_selection_area), 0);
    gtk_widget_set_size_request(GTK_WIDGET(*content_selection_area), CUR_WIDTH-100, 0);
    //
}
