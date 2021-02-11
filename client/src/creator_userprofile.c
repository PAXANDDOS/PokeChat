#include "../inc/client.h"

static void userprofile_send_click(GtkWidget *widget, gpointer chat_id) {
    if(widget) {}
    if(!upd_data.busy) {
        upd_data.suspend = true;
        gtk_widget_destroy(t_msg.background);
        for (int i = 0; i < upd_data.count; i++)
            if (upd_data.chats_id[i] == msg_data.chat_id) {
                upd_data.messages_id[i] = 0;
                break;
            }
        msg_data.chat_id = (int)(intptr_t)chat_id;
        upd_data.suspend = false;
    }
}

void userprofile_remove_click(GtkWidget *widget, GdkEventButton *event, gpointer chat_id) {
    if(widget) {}
    if(event->button == 1 && !upd_data.busy) {
        upd_data.suspend = true;
        gtk_widget_destroy(t_msg.background);
        gtk_widget_destroy(t_msg.chat_screen);
        if (msg_data.chat_id == (int)(intptr_t)chat_id)
            msg_data.chat_id = 0;

        cJSON *json = cJSON_CreateObject();
        cJSON *json_remove_chat = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_remove_chat, "sender_id", t_account.id);
        cJSON_AddNumberToObject(json_remove_chat, "chat_id", (int)(intptr_t)chat_id);
        cJSON_AddItemToObject(json, "remove_chat", json_remove_chat);
        char *json_string = cJSON_PrintUnformatted(json);
        char *result = NULL;
        ssl_client(json_string, &result);
        mx_strdel(&result);
        mx_strdel(&json_string);
        cJSON_Delete(json);
        upd_data.suspend = false;
    }
}

void creator_userprofile(GtkWidget *main, t_user *user, int chat_id)
{
    t_msg.background = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_msg.background), "crgroup");
    gtk_widget_set_size_request(GTK_WIDGET(t_msg.background), WINDOW_WIDTH-LEFTBAR_W, WINDOW_HEIGHT);
    g_signal_connect(G_OBJECT(t_msg.background), "button_press_event", G_CALLBACK(gtk_widget_destroy), NULL);
    gtk_fixed_put(GTK_FIXED(main), t_msg.background, 0, 0);

    GtkWidget *clickable = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(clickable), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(clickable), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(clickable), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);
    gtk_container_add(GTK_CONTAINER(t_msg.background), clickable);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(box), "profile_box");
    gtk_container_add(GTK_CONTAINER(clickable), box);

    //
    GtkWidget *avatarbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(avatarbox), "profile_avatarbox");
    gtk_box_pack_start(GTK_BOX(box), avatarbox, FALSE, TRUE, 15);

    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 90, 90);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar_profile), (gpointer)(intptr_t)user->avatar);   // Получить номер avatar пользователя
    gtk_widget_set_halign(avatar, GTK_ALIGN_START);
    gtk_widget_set_valign(avatar, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(avatarbox), avatar, FALSE, FALSE, 0);

    GtkWidget *infobox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(avatarbox), infobox, FALSE, TRUE, 20);

    GtkWidget *usernamebox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(infobox), usernamebox, FALSE, TRUE, 0);

    GtkWidget *username_label = gtk_label_new(user->username);                                                                     // Получить ник пользователя
    gtk_widget_set_name(GTK_WIDGET(username_label), "username_profile");
    gtk_widget_set_halign(GTK_WIDGET(username_label), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(usernamebox), username_label, FALSE, FALSE, 0);

    if(user->online){
        GtkWidget *status_label = gtk_label_new("Online");
        gtk_widget_set_name(GTK_WIDGET(status_label), "status_profile");
        gtk_widget_set_halign(GTK_WIDGET(status_label), GTK_ALIGN_START);
        gtk_box_pack_start(GTK_BOX(usernamebox), status_label, FALSE, FALSE, 0);
    }

    char *team_char;
    GtkWidget *badge = gtk_event_box_new();
    gtk_widget_set_size_request(GTK_WIDGET(badge), 26, 26);
    switch(user->team) {
        case 1: gtk_widget_set_name(GTK_WIDGET(badge), "teammystic_profile"); team_char = "Mystic"; break;
        case 2: gtk_widget_set_name(GTK_WIDGET(badge), "teaminstinct_profile"); team_char = "Instinct"; break;
        case 3: gtk_widget_set_name(GTK_WIDGET(badge), "teamvalor_profile"); team_char = "Valor"; break;
        default: team_char = "Team badge"; break;
    }
    gtk_widget_set_halign(GTK_WIDGET(badge), GTK_ALIGN_START);
    tooltip(team_char, badge);
    gtk_box_pack_start(GTK_BOX(infobox), badge, FALSE, FALSE, 6);

    GtkWidget *interactions = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_end(GTK_BOX(avatarbox), interactions, FALSE, TRUE, 15);

    GtkWidget *send_button = gtk_button_new_with_label("Send message");
    gtk_widget_set_name(GTK_WIDGET(send_button), "sendmessage_profile");
    gtk_button_set_relief(GTK_BUTTON(send_button), GTK_RELIEF_NONE);
    gtk_widget_set_size_request(GTK_WIDGET(send_button), 100, 10);
    gtk_box_pack_start(GTK_BOX(interactions), send_button, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(send_button), "clicked", G_CALLBACK(userprofile_send_click), (gpointer)(intptr_t)chat_id);

    GtkWidget *remove = gtk_event_box_new();
    gtk_widget_set_size_request(GTK_WIDGET(remove), 30, 30);
    gtk_widget_set_name(GTK_WIDGET(remove), "remove_user");
    tooltip("Remove user", remove);
    gtk_box_pack_start(GTK_BOX(interactions), remove, FALSE, FALSE, 10);
    g_signal_connect(G_OBJECT(remove), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(remove), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(remove), "button_press_event", G_CALLBACK(userprofile_remove_click), (gpointer)(intptr_t)chat_id);

    GtkWidget *bg = gtk_event_box_new();
    switch(user->team) {
        case 1: gtk_widget_set_name(GTK_WIDGET(bg), "bg_mystic_profile"); break;
        case 2: gtk_widget_set_name(GTK_WIDGET(bg), "bg_instinct_profile"); break;
        case 3: gtk_widget_set_name(GTK_WIDGET(bg), "bg_valor_profile"); break;
    }
    gtk_box_pack_start(GTK_BOX(box), bg, FALSE, TRUE, 0);

    GtkWidget *databox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(databox), "databox_profile");
    gtk_container_add(GTK_CONTAINER(bg), databox);

    GtkWidget *namebox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(databox), namebox, TRUE, TRUE, 10);
    GtkWidget *name_label = gtk_label_new("Name:");
    gtk_widget_set_name(GTK_WIDGET(name_label), "infolabel_profile");
    gtk_widget_set_halign(name_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(namebox), name_label, FALSE, FALSE, 0);
    GtkWidget *realname = gtk_label_new(user->name);                        // Получить настоящее имя
    gtk_widget_set_name(GTK_WIDGET(realname), "realdata_profile");
    gtk_widget_set_halign(realname, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(namebox), realname, FALSE, FALSE, 0);

    GtkWidget *codebox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(databox), codebox, TRUE, TRUE, 10);
    GtkWidget *code_label = gtk_label_new("Trainer code:");
    gtk_widget_set_name(GTK_WIDGET(code_label), "infolabel_profile");
    gtk_widget_set_halign(code_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(codebox), code_label, FALSE, FALSE, 0);
    GtkWidget *realcode = gtk_label_new(user->code);                // Получить тренерский код
    gtk_widget_set_name(GTK_WIDGET(realcode), "realdata_profile");
    gtk_widget_set_halign(realcode, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(codebox), realcode, FALSE, FALSE, 0);

    gtk_widget_show_all(GTK_WIDGET(t_msg.background));
}
