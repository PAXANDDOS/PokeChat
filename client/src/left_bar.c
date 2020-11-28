#include "../inc/client.h"

void build_left_bar(GtkWidget **content_selection_area, GtkWidget **main_area) 
{
    // Loading CSS file
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/data/css/theme.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    //
    // Connecting leftbar widget to CSS
    GtkWidget *left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(left_box), "leftbar");
    gtk_widget_set_size_request(GTK_WIDGET(left_box), 93, CUR_HEIGHT); 
    gtk_fixed_put(GTK_FIXED(*main_area), left_box, 0, 0);
    //
    // Creating selection area
    *content_selection_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_fixed_put(GTK_FIXED(*main_area), *content_selection_area, 0, 0);
    gtk_container_set_border_width(GTK_CONTAINER(*content_selection_area), 0);
    gtk_widget_set_size_request(GTK_WIDGET(*content_selection_area), 100, 0);
    //
    // Creating selection area for settings
    GtkWidget *block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_fixed_put(GTK_FIXED(*main_area), block, 0, 650);
    gtk_container_set_border_width(GTK_CONTAINER(block), 0);
    gtk_widget_set_size_request(GTK_WIDGET(block), 100, 0);
    //
    // Placing icons
    gtk_box_pack_start(GTK_BOX(*content_selection_area),
        t_img_event_box.home_box, TRUE, FALSE, 9);
    gtk_box_pack_start(GTK_BOX(*content_selection_area),
        t_img_event_box.messages_box, TRUE, FALSE, 9);
    gtk_box_pack_start(GTK_BOX(*content_selection_area),
        t_img_event_box.group_box, TRUE, FALSE, 9);
    gtk_box_pack_start(GTK_BOX(*content_selection_area),
        t_img_event_box.events_box, TRUE, FALSE, 9);
    gtk_box_pack_start(GTK_BOX(block),
        t_img_event_box.settings_box, TRUE, FALSE, 9); 
    //
    // Checking for events
    g_signal_connect(G_OBJECT(t_img_event_box.home_box), "enter-notify-event",
        G_CALLBACK(home_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.home_box), "leave-notify-event",
        G_CALLBACK(home_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.home_box), "button_press_event",
        G_CALLBACK(home_click), NULL);

    g_signal_connect(G_OBJECT(t_img_event_box.messages_box), "enter-notify-event",
        G_CALLBACK(messages_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.messages_box), "leave-notify-event",
        G_CALLBACK(messages_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.messages_box), "button_press_event",
        G_CALLBACK(messages_click), NULL);

    g_signal_connect(G_OBJECT(t_img_event_box.settings_box), "enter-notify-event",
        G_CALLBACK(settings_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.settings_box), "leave-notify-event",
        G_CALLBACK(settings_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_img_event_box.settings_box), "button_press_event",
        G_CALLBACK(settings_click), NULL);
    //
}
