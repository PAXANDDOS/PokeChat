#include "../inc/client.h"

// static void remove_person(GtkWidget *widget, GdkEventButton *event, gpointer user_id) {
//     if(event->type == GDK_BUTTON_PRESS && event->button == 1) {
//         gtk_widget_destroy(GTK_WIDGET(widget));
//         new_group->count = new_group->count - 1;
//         int *temp = malloc(sizeof(int*) * new_group->count);
//         for (int i = 0, j = 0; i < new_group->count + 1; i++)
//             if (new_group->users_id[i] != (int)(intptr_t)user_id)
//                 temp[j++] = new_group->users_id[i];
//         free(new_group->users_id);
//         new_group->users_id = malloc(sizeof(int*) * new_group->count);
//         for (int i = 0; i < new_group->count; i++)
//             new_group->users_id[i] = temp[i];
//         free(temp);
//         create_notification(t_application.messanger, "User deleted", 0, 461, 110, 420, 10);
//     }
// }

// static GtkWidget *create_single_person(char *name, int avatar_id) {
//     GtkWidget *single_event = gtk_event_box_new();
//     gtk_widget_set_name(GTK_WIDGET(single_event), "crlist_person");
//     gtk_event_box_set_above_child(GTK_EVENT_BOX(single_event), TRUE);

//     GtkWidget *single = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
//     gtk_widget_set_name(GTK_WIDGET(single), "crlist_person_h");
//     gtk_container_add(GTK_CONTAINER(single_event), single);

//     GtkWidget *avatar = gtk_drawing_area_new();
//     gtk_widget_set_size_request(GTK_WIDGET(avatar), 34, 34);
//     g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar), (gpointer)(intptr_t)avatar_id);
//     gtk_widget_set_halign(avatar, GTK_ALIGN_START);
//     gtk_widget_set_valign(avatar, GTK_ALIGN_CENTER);
//     gtk_box_pack_start(GTK_BOX(single), avatar, FALSE, FALSE, 6);

//     GtkWidget *nickname = gtk_label_new(name);
//     gtk_widget_set_name(GTK_WIDGET(nickname), "nickname");
//     gtk_box_pack_start(GTK_BOX(single), nickname, FALSE, FALSE, 5);

//     return single_event;
// }

// static void add_person(GtkWidget *widget, GdkEventButton *event) {
//     if(widget) {}
//     if(event->type == GDK_BUTTON_PRESS && event->button == 1) {
//         char *name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY((GtkWidget*)new_group->search_field)));
//         if(name != NULL)
//             name = mx_del_extra_spaces(name);
//         if(!strcmp(name, "") || !strcmp(name, " "))
//             return;

//         GList *parent = gtk_container_get_children(GTK_CONTAINER(t_msg.crlist));
//         while(parent != NULL) {
//             GList *children = gtk_container_get_children(GTK_CONTAINER(parent->data));
//             GList *children2 = gtk_container_get_children(GTK_CONTAINER(children->data));
//             children2 = children2->next;
//             char* copy = (char*)gtk_label_get_text(GTK_LABEL(children2->data));

//             g_list_free(g_steal_pointer(&children2));
//             g_list_free(g_steal_pointer(&children));
//             if(!strcmp(copy, name))
//                 return;
//             parent = parent->next;
//         }
//         g_list_free(g_steal_pointer(&parent));

//         int avatar = 0, user_id = 0;
//         if (!add_user_to_group(name, &user_id, &avatar)) {
//             create_notification(t_application.messanger, "Invalid username!", 1, 461, 110, 420, 10);
//             return;
//         }

//         gtk_entry_set_text(GTK_ENTRY(new_group->search_field), "");
//         GtkWidget *single = create_single_person(name, avatar);
//         gtk_box_pack_start(GTK_BOX(t_msg.crlist), single, FALSE, FALSE, 0);
//         gtk_widget_show_all(GTK_WIDGET(t_msg.crlist));
//         create_notification(t_application.messanger, mx_strjoin(name, " added!"), 0, 461, 110, 420, 10);

//         g_signal_connect(G_OBJECT(single), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
//         g_signal_connect(G_OBJECT(single), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
//         g_signal_connect(G_OBJECT(single), "button_press_event", G_CALLBACK(remove_person), (gpointer)(intptr_t)user_id);
//         tooltip("Remove",single);
//     }
// }

// static void apply_group_button_click(GtkWidget *widget) {
//     if(widget) {}
// }

void creator_groupsettings(GtkWidget *main, char *name, bool admin)
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
    gtk_widget_set_name(GTK_WIDGET(box), "crgroup_box");
    gtk_container_add(GTK_CONTAINER(clickable), box);

    GtkWidget *title = gtk_label_new("GROUP SETTINGS");
    gtk_widget_set_name(GTK_WIDGET(title), "creategroup_title");
    gtk_widget_set_halign(title, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(box), title, FALSE, FALSE, 0);
    //
    GtkWidget *infobox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(box), infobox, FALSE, TRUE, 15);

    GtkWidget* avatar = gtk_event_box_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 80, 80);
    gtk_widget_set_name(GTK_WIDGET(avatar), "group_people");
    gtk_box_pack_start(GTK_BOX(infobox), avatar, FALSE, FALSE, 0);

    GtkWidget *group_name = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(group_name), name);
    gtk_widget_set_name(GTK_WIDGET(group_name), "crgroup_name_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(group_name), "Group name");
    g_signal_connect(G_OBJECT(group_name), "insert-text", G_CALLBACK(all_input_event), NULL);
    gtk_entry_set_max_length(GTK_ENTRY(group_name), MAX_USERNAME);
    gtk_box_pack_start(GTK_BOX(infobox), group_name, TRUE, TRUE, 10);

    if(admin) {
        GtkWidget* delete_group = gtk_event_box_new();
        gtk_widget_set_size_request(GTK_WIDGET(delete_group), 40, 40);
        gtk_widget_set_name(GTK_WIDGET(delete_group), "trash_delete");
        gtk_box_pack_start(GTK_BOX(infobox), delete_group, FALSE, FALSE, 0);
        g_signal_connect(G_OBJECT(delete_group), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
        g_signal_connect(G_OBJECT(delete_group), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
        //g_signal_connect(G_OBJECT(delete_group), "button_press_event", G_CALLBACK(add_person), NULL);
        tooltip("Delete group",delete_group);
    }
    //

    if(admin) {
        GtkWidget *search_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
        gtk_widget_set_name(GTK_WIDGET(search_block), "crgroup_search_block");
        gtk_widget_set_size_request(GTK_WIDGET(search_block), 350, 40);
        gtk_box_pack_start(GTK_BOX(box), search_block, FALSE, TRUE, 0);
        GtkWidget *search_field = gtk_entry_new();
        gtk_widget_set_name(GTK_WIDGET(search_field), "crgroup_search_field");
        gtk_entry_set_placeholder_text(GTK_ENTRY(search_field), "Add some people...");
        g_signal_connect(G_OBJECT(search_field), "insert-text", G_CALLBACK(all_input_event), NULL);
        gtk_entry_set_max_length(GTK_ENTRY(search_field), MAX_USERNAME);
        gtk_box_pack_start(GTK_BOX(search_block), search_field, TRUE, TRUE, 0);
        GtkWidget *adduser = gtk_event_box_new();
        gtk_widget_set_name(GTK_WIDGET(adduser), "adduser");
        gtk_widget_set_size_request(GTK_WIDGET(adduser), 22, 22);
        gtk_box_pack_start(GTK_BOX(search_block), adduser, FALSE, FALSE, 10);
        gtk_widget_set_halign(GTK_WIDGET(adduser), GTK_ALIGN_END);
        gtk_widget_set_valign(GTK_WIDGET(adduser), GTK_ALIGN_CENTER);

        g_signal_connect(G_OBJECT(adduser), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
        g_signal_connect(G_OBJECT(adduser), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
        //g_signal_connect(G_OBJECT(adduser), "button_press_event", G_CALLBACK(add_person), NULL);
        tooltip("Add",adduser);
    }

    GtkWidget *scrollable = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(scrollable), 400, 200);
    gtk_box_pack_start(GTK_BOX(box), scrollable, FALSE, FALSE, 0);

    t_msg.crlist = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    gtk_widget_set_name(GTK_WIDGET(t_msg.crlist), "crlist");
    gtk_container_add(GTK_CONTAINER(scrollable), t_msg.crlist);

    // GtkWidget *single = create_single_person(name, avatar);
    // gtk_box_pack_start(GTK_BOX(t_msg.crlist), single, FALSE, FALSE, 0);
    // gtk_widget_show_all(GTK_WIDGET(t_msg.crlist));

    GtkWidget *apply_group_button = gtk_button_new_with_label("Apply changes");
    gtk_widget_set_name(GTK_WIDGET(apply_group_button), "crgroup_button");
    gtk_button_set_relief(GTK_BUTTON(apply_group_button), GTK_RELIEF_NONE);
    gtk_widget_set_size_request(GTK_WIDGET(apply_group_button), 100, 10);
    gtk_box_pack_start(GTK_BOX(box), apply_group_button, FALSE, FALSE, 0);
    //g_signal_connect(G_OBJECT(apply_group_button), "clicked", G_CALLBACK(apply_group_button_click), group_name);

    gtk_widget_show_all(GTK_WIDGET(t_msg.background));
}

// #include "../inc/client.h"

// static void apply_group_button_click(GtkWidget *widget, gpointer p_chat_data) {
//     if(widget) {}
//     if(!upd_data.busy) {
//         upd_data.suspend = true;
//         t_chat_data *chat_data = (t_chat_data*)p_chat_data;
//         cJSON *json = cJSON_CreateObject();
//         cJSON *json_rename_group = cJSON_CreateObject();
//         cJSON_AddNumberToObject(json_rename_group, "sender_id", t_account.id);
//         cJSON_AddNumberToObject(json_rename_group, "chat_id", chat_data->chat_id);
//         cJSON_AddStringToObject(json_rename_group, "title", chat_data->title);
//         cJSON_AddItemToObject(json, "rename_group", json_rename_group);
//         char *json_string = cJSON_PrintUnformatted(json);
//         char *result = NULL;
//         ssl_client(json_string, &result);
//         mx_strdel(&result);
//         mx_strdel(&json_string);
//         cJSON_Delete(json);
//         free(chat_data);
//         gtk_widget_destroy(t_msg.background);
//         upd_data.suspend = false;
//     }
// }

// void creator_groupsettings(GtkWidget *main, char *name, int chat_id)
// {
//     t_msg.background = gtk_event_box_new();
//     gtk_widget_set_name(GTK_WIDGET(t_msg.background), "crgroup");
//     gtk_widget_set_size_request(GTK_WIDGET(t_msg.background), WINDOW_WIDTH-LEFTBAR_W, WINDOW_HEIGHT);
//     g_signal_connect(G_OBJECT(t_msg.background), "button_press_event", G_CALLBACK(gtk_widget_destroy), NULL);
//     gtk_fixed_put(GTK_FIXED(main), t_msg.background, 0, 0);

//     GtkWidget *clickable = gtk_event_box_new();
//     gtk_widget_set_halign(GTK_WIDGET(clickable), GTK_ALIGN_CENTER);
//     gtk_widget_set_valign(GTK_WIDGET(clickable), GTK_ALIGN_CENTER);
//     g_signal_connect(G_OBJECT(clickable), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);
//     gtk_container_add(GTK_CONTAINER(t_msg.background), clickable);

//     GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
//     gtk_widget_set_name(GTK_WIDGET(box), "crgroup_box");
//     gtk_container_add(GTK_CONTAINER(clickable), box);

//     GtkWidget *title = gtk_label_new("GROUP SETTINGS");
//     gtk_widget_set_name(GTK_WIDGET(title), "creategroup_title");
//     gtk_widget_set_halign(title, GTK_ALIGN_START);
//     gtk_box_pack_start(GTK_BOX(box), title, FALSE, FALSE, 0);
//     //
//     GtkWidget *infobox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
//     gtk_box_pack_start(GTK_BOX(box), infobox, FALSE, TRUE, 15);

//     GtkWidget* avatar = gtk_event_box_new();
//     gtk_widget_set_size_request(GTK_WIDGET(avatar), 80, 80);
//     gtk_widget_set_name(GTK_WIDGET(avatar), "group_people");
//     gtk_box_pack_start(GTK_BOX(infobox), avatar, FALSE, FALSE, 0);

//     GtkWidget *group_name = gtk_entry_new();
//     gtk_entry_set_text(GTK_ENTRY(group_name), name);
//     gtk_widget_set_name(GTK_WIDGET(group_name), "crgroup_name_field");
//     gtk_entry_set_placeholder_text(GTK_ENTRY(group_name), "Group name");
//     g_signal_connect(G_OBJECT(group_name), "insert-text", G_CALLBACK(all_input_event), NULL);
//     gtk_entry_set_max_length(GTK_ENTRY(group_name), MAX_USERNAME);
//     gtk_box_pack_start(GTK_BOX(infobox), group_name, TRUE, TRUE, 10);

//     GtkWidget* delete_group = gtk_event_box_new();
//     gtk_widget_set_size_request(GTK_WIDGET(delete_group), 40, 40);
//     gtk_widget_set_name(GTK_WIDGET(delete_group), "trash_delete");
//     gtk_box_pack_start(GTK_BOX(infobox), delete_group, FALSE, FALSE, 0);
//     g_signal_connect(G_OBJECT(delete_group), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
//     g_signal_connect(G_OBJECT(delete_group), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
//     g_signal_connect(G_OBJECT(delete_group), "button_press_event", G_CALLBACK(userprofile_remove_click), (gpointer)(intptr_t)chat_id);
//     tooltip("Delete group",delete_group);

//     GtkWidget *search_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
//     gtk_widget_set_name(GTK_WIDGET(search_block), "crgroup_search_block");
//     gtk_widget_set_size_request(GTK_WIDGET(search_block), 350, 40);
//     gtk_box_pack_start(GTK_BOX(box), search_block, FALSE, TRUE, 0);
//     GtkWidget *search_field = gtk_entry_new();
//     gtk_widget_set_name(GTK_WIDGET(search_field), "crgroup_search_field");
//     gtk_entry_set_placeholder_text(GTK_ENTRY(search_field), "Add some people...");
//     g_signal_connect(G_OBJECT(search_field), "insert-text", G_CALLBACK(all_input_event), NULL);
//     gtk_entry_set_max_length(GTK_ENTRY(search_field), MAX_USERNAME);
//     gtk_box_pack_start(GTK_BOX(search_block), search_field, TRUE, TRUE, 0);
//     GtkWidget *adduser = gtk_event_box_new();
//     gtk_widget_set_name(GTK_WIDGET(adduser), "adduser");
//     gtk_widget_set_size_request(GTK_WIDGET(adduser), 22, 22);
//     gtk_box_pack_start(GTK_BOX(search_block), adduser, FALSE, FALSE, 10);
//     gtk_widget_set_halign(GTK_WIDGET(adduser), GTK_ALIGN_END);
//     gtk_widget_set_valign(GTK_WIDGET(adduser), GTK_ALIGN_CENTER);

//     g_signal_connect(G_OBJECT(adduser), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
//     g_signal_connect(G_OBJECT(adduser), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
//     // g_signal_connect(G_OBJECT(adduser), "button_press_event", G_CALLBACK(add_person), NULL);  // TODO or not TODO...
//     tooltip("Add",adduser);


//     GtkWidget *scrollable = gtk_scrolled_window_new(NULL, NULL);
//     gtk_widget_set_size_request(GTK_WIDGET(scrollable), 400, 200);
//     gtk_box_pack_start(GTK_BOX(box), scrollable, FALSE, FALSE, 0);

//     t_msg.crlist = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
//     gtk_widget_set_name(GTK_WIDGET(t_msg.crlist), "crlist");
//     gtk_container_add(GTK_CONTAINER(scrollable), t_msg.crlist);

//     t_chat_data *chat_data = malloc(sizeof(t_chat_data));
//     chat_data->chat_id = chat_id;
//     chat_data->title = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(group_name)));

//     GtkWidget *apply_group_button = gtk_button_new_with_label("Apply changes");
//     gtk_widget_set_name(GTK_WIDGET(apply_group_button), "crgroup_button");
//     gtk_button_set_relief(GTK_BUTTON(apply_group_button), GTK_RELIEF_NONE);
//     gtk_widget_set_size_request(GTK_WIDGET(apply_group_button), 100, 10);
//     gtk_box_pack_start(GTK_BOX(box), apply_group_button, FALSE, FALSE, 0);
//     g_signal_connect(G_OBJECT(apply_group_button), "clicked", G_CALLBACK(apply_group_button_click), (gpointer)chat_data);

//     gtk_widget_show_all(GTK_WIDGET(t_msg.background));
// }
