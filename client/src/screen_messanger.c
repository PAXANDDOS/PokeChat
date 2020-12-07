#include "../inc/client.h"

static void build_list(GtkWidget *main)
{
    GtkWidget *list_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    gtk_widget_set_name(GTK_WIDGET(list_block), "list");                       // Имя
    gtk_widget_set_size_request(GTK_WIDGET(list_block), LIST_W, LIST_H);   // Размер
    gtk_fixed_put(GTK_FIXED(main), list_block, 0, 0);            // Позиция
    //
    GtkWidget *search_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_size_request(GTK_WIDGET(search_block), LIST_W, 40);
    gtk_box_pack_start(GTK_BOX(list_block), search_block, FALSE, FALSE, 15); 
    GtkWidget *search_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(search_field), "search_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(search_field), "Search for people");
    gtk_box_pack_start(GTK_BOX(search_block), search_field, FALSE, FALSE, 8); 
}

// static void build_chat(GtkWidget *main)
// {

// }

void build_messanger_screen(GtkWidget **msgscreen) 
{
    // Loading CSS file
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/data/css/msg_screen.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    //
    // Creating workspace
    msg_scr = gtk_grid_new();   // Эта падла меня задрала. Создал grid чтобы можно было применить CSS ибо в fixed нельзя.
    gtk_widget_set_name(GTK_WIDGET(msg_scr), "messanger");                            
    gtk_widget_set_size_request(GTK_WIDGET(msg_scr), CUR_WIDTH-LEFTBAR_W, CUR_HEIGHT); 
    gtk_fixed_put(GTK_FIXED(*msgscreen), msg_scr, LEFTBAR_W, 0);                       
    GtkWidget *main = gtk_fixed_new();
    gtk_grid_attach(GTK_GRID(msg_scr), main, 0, 0, CUR_WIDTH-LEFTBAR_W, CUR_HEIGHT); // Запихиваю новый fixed в первую ячейку грида, для того чтобы можно было нормально размещать элементы.
    //
    //
    build_list(main);
    //build_chat(main);
}
