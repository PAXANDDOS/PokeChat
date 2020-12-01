#include "../inc/client.h"

void build_home_screen(GtkWidget **homescreen) 
{
    // Loading CSS file
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/data/css/home_screen.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    //

    // Creating workspace
    home_scr = gtk_grid_new();   // Эта падла меня задрала. Создал grid чтобы можно было применить CSS ибо в fixed нельзя.
    gtk_widget_set_name(GTK_WIDGET(home_scr), "homescreen");                            
    gtk_widget_set_size_request(GTK_WIDGET(home_scr), CUR_WIDTH-LEFTBAR_W, CUR_HEIGHT); 
    gtk_fixed_put(GTK_FIXED(*homescreen), home_scr, LEFTBAR_W, 0);                       
    GtkWidget *main = gtk_fixed_new();
    gtk_grid_attach(GTK_GRID(home_scr), main, 0, 0, CUR_WIDTH-LEFTBAR_W, CUR_HEIGHT); // Запихиваю новый fixed в первую ячейку грида, для того чтобы можно было нормально размещать элементы.
    //

    // Creating block for "ACTIVITY BANNER"
    GtkWidget *activity_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_widget_set_name(GTK_WIDGET(activity_block), "activity");            // Имя
    gtk_widget_set_size_request(GTK_WIDGET(activity_block), 347, 271);      // Размер
    gtk_fixed_put(GTK_FIXED(main), activity_block, 13, 11);                 // Позиция
    // Label for header
    GtkWidget *active_text = gtk_label_new("ACTIVE NOW");
    gtk_widget_set_name(GTK_WIDGET(active_text), "active_text");            // Имя
    gtk_widget_set_halign(active_text, GTK_ALIGN_START);                    // Позиция текста
    gtk_box_pack_start(GTK_BOX(activity_block), active_text, FALSE, FALSE, 0); 
    // Дописать также челиков

    // Creating block for "FACT BANNER"
    GtkWidget *fact_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_widget_set_name(GTK_WIDGET(fact_block), "fact");
    gtk_widget_set_size_request(GTK_WIDGET(fact_block), 347, 407);
    gtk_fixed_put(GTK_FIXED(main), fact_block, 13, 301);
    // Label for header
    GtkWidget *fact_text = gtk_label_new("HERE'S A FACT!");
    gtk_widget_set_name(GTK_WIDGET(fact_text), "fact_text");                // Имя
    gtk_widget_set_halign(fact_text, GTK_ALIGN_CENTER);                     // Позиция текста
    gtk_box_pack_start(GTK_BOX(fact_block), fact_text, FALSE, FALSE, 0);
    //  Дописать генерацию картинки и текста к ней

    // Creating block for "WELCOMING BANNER". The latest and the hardest
    GtkWidget *welcome_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    gtk_widget_set_name(GTK_WIDGET(welcome_block), "welcome");              // Имя
    gtk_widget_set_size_request(GTK_WIDGET(welcome_block), 827, 698);       // Размер
    gtk_fixed_put(GTK_FIXED(main), welcome_block, 374, 11);                 // Позиция
    //
}
