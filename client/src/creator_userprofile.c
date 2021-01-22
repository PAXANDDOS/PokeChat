#include "../inc/client.h"

static void s_click(GtkWidget *widget) {
    gtk_widget_destroy(GTK_WIDGET(widget));
}

static void s2_click(GtkWidget *widget) {
    if(widget) {}
}

void creator_userprofile(GtkWidget *main, char *username, bool status)
{
    t_msg.background = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_msg.background), "crgroup");
    gtk_widget_set_size_request(GTK_WIDGET(t_msg.background), WINDOW_WIDTH-67, WINDOW_HEIGHT);
    g_signal_connect(G_OBJECT(t_msg.background), "button_press_event", G_CALLBACK(s_click), NULL);
    gtk_fixed_put(GTK_FIXED(main), t_msg.background, 0, 0);

    GtkWidget *clickable = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(clickable), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(clickable), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(clickable), "button_press_event", G_CALLBACK(s2_click), NULL);
    gtk_container_add(GTK_CONTAINER(t_msg.background), clickable);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(box), "crgroup_box");
    gtk_container_add(GTK_CONTAINER(clickable), box);

    //
    GtkWidget *avatarbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(box), avatarbox, FALSE, TRUE, 15);

    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 90, 90);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar_profile), (gpointer)(intptr_t)54);   // Получить номер avatar пользователя
    gtk_widget_set_halign(avatar, GTK_ALIGN_START);
    gtk_widget_set_valign(avatar, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(avatarbox), avatar, FALSE, FALSE, 0);

    GtkWidget *infobox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(avatarbox), infobox, FALSE, TRUE, 20);

    GtkWidget *usernamebox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(infobox), usernamebox, FALSE, TRUE, 0);

    GtkWidget *username_label = gtk_label_new(username);                                                                     // Получить ник пользователя
    gtk_widget_set_name(GTK_WIDGET(username_label), "username_profile");
    gtk_widget_set_halign(GTK_WIDGET(username_label), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(usernamebox), username_label, FALSE, FALSE, 0);

    if(status){
        GtkWidget *status_label = gtk_label_new("Online");
        gtk_widget_set_name(GTK_WIDGET(status_label), "status_profile");
        gtk_widget_set_halign(GTK_WIDGET(status_label), GTK_ALIGN_START);
        gtk_box_pack_start(GTK_BOX(usernamebox), status_label, FALSE, FALSE, 0);
    }

    short team = 1; // Получить команду (1-3)
    char *team_char;

    GtkWidget *badge = gtk_event_box_new();
    gtk_widget_set_size_request(GTK_WIDGET(badge), 26, 26);
    switch(team) {
        case 1: gtk_widget_set_name(GTK_WIDGET(badge), "teammystic_profile"); team_char = "Mystic"; break;
        case 2: gtk_widget_set_name(GTK_WIDGET(badge), "teaminstinct_profile"); team_char = "Instinct"; break;
        case 3: gtk_widget_set_name(GTK_WIDGET(badge), "teamvalor_profile"); team_char = "Valor"; break;
        default: team_char = "Team badge"; break;
    }
    gtk_widget_set_halign(GTK_WIDGET(badge), GTK_ALIGN_START);
    tooltip(team_char, badge);
    gtk_box_pack_start(GTK_BOX(infobox), badge, FALSE, FALSE, 6);
    //

    GtkWidget *interactions = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_end(GTK_BOX(avatarbox), interactions, FALSE, TRUE, 15);

    GtkWidget *send_button = gtk_button_new_with_label("Send message");
    gtk_widget_set_name(GTK_WIDGET(send_button), "sendmessage_profile");
    gtk_button_set_relief(GTK_BUTTON(send_button), GTK_RELIEF_NONE);
    gtk_widget_set_size_request(GTK_WIDGET(send_button), 100, 10);
    gtk_box_pack_end(GTK_BOX(interactions), send_button, FALSE, FALSE, 0);
    //g_signal_connect(G_OBJECT(send_button), "clicked", G_CALLBACK(create_group_button_click), group_name);

    gtk_widget_show_all(GTK_WIDGET(t_msg.background));
}
