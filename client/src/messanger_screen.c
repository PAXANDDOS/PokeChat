#include "../inc/client.h"

void build_messanger_screen(GtkWidget **main_area) 
{
    // Loading CSS file
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/data/css/msg_screen.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    //
    msg_scr = gtk_grid_new();                                                           // Создаем виджет для страницы чата
    gtk_widget_set_name(GTK_WIDGET(msg_scr), "messanger");                              // Присваиваем ему имя для связи с CSS
    gtk_widget_set_size_request(GTK_WIDGET(msg_scr), CUR_WIDTH-LEFTBAR_W, CUR_HEIGHT);  // Настройка размера виджета
    gtk_fixed_put(GTK_FIXED(*main_area), msg_scr, LEFTBAR_W, 0);                        // Настройка позиции виджета
}
