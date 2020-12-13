#include "../inc/client.h"

static void build_account_menu(GtkWidget *main)
{
    GtkWidget *menu_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_size_request(GTK_WIDGET(menu_block), CUR_WIDTH-LEFTBAR_W, 0);
    gtk_widget_set_name(GTK_WIDGET(menu_block), "menu_block");
    gtk_fixed_put(GTK_FIXED(main),menu_block, 0, 0);
    int w, h; gtk_widget_get_size_request(GTK_WIDGET(menu_block), &w, &h);
    //
    GtkWidget *menu_setting = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(menu_block), menu_setting, FALSE, FALSE, 0);
    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 200, 200);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar), (int*)200);
    gtk_box_pack_start(GTK_BOX(menu_setting), avatar, FALSE, FALSE, 0);
    GtkWidget *avatar_butt = gtk_button_new_with_label("Select avatar");
    gtk_widget_set_name(GTK_WIDGET(avatar_butt), "edit_button");
    gtk_button_set_relief(GTK_BUTTON(avatar_butt), GTK_RELIEF_NONE);
    gtk_box_pack_start(GTK_BOX(menu_setting), avatar_butt, FALSE, FALSE, 10);
    GtkWidget *info_butt = gtk_button_new_with_label("Change info");
    gtk_widget_set_name(GTK_WIDGET(info_butt), "edit_button");
    gtk_button_set_relief(GTK_BUTTON(info_butt), GTK_RELIEF_NONE);
    gtk_box_pack_start(GTK_BOX(menu_setting), info_butt, FALSE, FALSE, 0);
    GtkWidget *apply_butt = gtk_button_new_with_label("Apply");
    gtk_widget_set_name(GTK_WIDGET(apply_butt), "apply_button");
    gtk_button_set_relief(GTK_BUTTON(apply_butt), GTK_RELIEF_NONE);
    gtk_box_pack_start(GTK_BOX(menu_setting), apply_butt, FALSE, FALSE, 0);
    //
    t_settings_scr.change_info = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(t_settings_scr.change_info), "changing_setting");
    gtk_widget_set_size_request(GTK_WIDGET(t_settings_scr.change_info), w-300, 364);
    gtk_fixed_put(GTK_FIXED(main),t_settings_scr.change_info, 254, 28);
    t_settings_scr.select_avatar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(t_settings_scr.select_avatar), "avatar_selection");
    gtk_widget_set_size_request(GTK_WIDGET(t_settings_scr.select_avatar), w-300, 364);
    gtk_fixed_put(GTK_FIXED(main),t_settings_scr.select_avatar, 254, 28);

    gtk_widget_hide(GTK_WIDGET(t_settings_scr.change_info));
    t_settings_scr.settings_active = t_settings_scr.select_avatar;
    //

    g_signal_connect(G_OBJECT(avatar_butt), "clicked", G_CALLBACK(change_avatar_click), NULL);
    g_signal_connect(G_OBJECT(info_butt), "clicked", G_CALLBACK(change_info_click), NULL);
}

void build_settings_menu(GtkWidget **stgscreen)
{
    // Loading CSS file
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/data/css/settings_scr.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    //
    // Creating workspace
    t_main_scr.settings_scr = gtk_grid_new();
    gtk_widget_set_name(GTK_WIDGET(t_main_scr.settings_scr), "settings_scr");                            
    gtk_widget_set_size_request(GTK_WIDGET(t_main_scr.settings_scr), CUR_WIDTH-LEFTBAR_W, CUR_HEIGHT); 
    gtk_fixed_put(GTK_FIXED(*stgscreen), t_main_scr.settings_scr, LEFTBAR_W, 0);                       
    GtkWidget *main = gtk_fixed_new();
    gtk_grid_attach(GTK_GRID(t_main_scr.settings_scr), main, 0, 0, CUR_WIDTH-LEFTBAR_W, CUR_HEIGHT);
    //

    build_account_menu(main);
    //build_chat(main);
    //build_entryfield(main);
}
