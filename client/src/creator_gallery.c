#include "../inc/client.h"

void update_user_avatar(int num) {
    cJSON *json = cJSON_CreateObject();
    cJSON *json_fields = cJSON_CreateObject();
    cJSON_AddNumberToObject(json_fields, "user_id", t_account.id);
    cJSON_AddNumberToObject(json_fields, "avatar", num);
    cJSON_AddItemToObject(json, "update_user_avatar", json_fields);
    char *json_string = cJSON_PrintUnformatted(json);
    char *result = NULL;
    ssl_client(json_string, &result);
    mx_strdel(&result);
    cJSON_Delete(json);
}

static void avatar_click(GtkWidget *widget) {
    GList *parent = gtk_container_get_children(GTK_CONTAINER(widget));
    GList *children = gtk_container_get_children(GTK_CONTAINER(parent->data));
    int chosen = atoi((char*)gtk_label_get_text(GTK_LABEL(children->data)));
    t_account.avatar = get_avatar_by_number(chosen);
    gtk_widget_destroy(GTK_WIDGET(t_settings.background));
    update_user_avatar(chosen);
    g_list_free(g_steal_pointer(&children));
    g_list_free(g_steal_pointer(&parent));
}

static GtkWidget *create_avatar_list(int avatar_num)
{
    char *path = "client/data/avatars/";
    path = mx_strjoin(path, mx_itoa(avatar_num));
    path = mx_strjoin(path, ".png");
    GtkWidget *single = gtk_event_box_new();
    GtkWidget *fixed = gtk_fixed_new();

    GtkWidget *key = gtk_label_new(mx_itoa(avatar_num));
    gtk_fixed_put(GTK_FIXED(fixed), key, 0, 0);

    GtkWidget *drawing = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(drawing), 80, 80);
    g_signal_connect(G_OBJECT(drawing), "draw", G_CALLBACK(draw_event_avatar_list), (char*)path);
    gtk_fixed_put(GTK_FIXED(fixed), drawing, 0, 0);

    gtk_container_add(GTK_CONTAINER(single), fixed);

    return single;
}

void create_gallery(GtkWidget *main)
{
    t_settings.background = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_settings.background), "sgallery");
    gtk_widget_set_size_request(GTK_WIDGET(t_settings.background), WINDOW_WIDTH-67, WINDOW_HEIGHT);
    g_signal_connect(G_OBJECT(t_settings.background), "button_press_event", G_CALLBACK(gtk_widget_destroy), NULL);
    gtk_fixed_put(GTK_FIXED(main), t_settings.background, 0, 0);

    GtkWidget *clickable = gtk_event_box_new();
    gtk_widget_set_halign(GTK_WIDGET(clickable), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(clickable), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(clickable), "button_press_event", G_CALLBACK(gtk_widget_show), NULL);
    gtk_container_add(GTK_CONTAINER(t_settings.background), clickable);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(box), "sgallery_box");
    gtk_container_add(GTK_CONTAINER(clickable), box);

    GtkWidget *title = gtk_label_new("SELECT AVATAR");
    gtk_widget_set_name(GTK_WIDGET(title), "sgallery_title");                // Имя
    gtk_widget_set_halign(title, GTK_ALIGN_START);                     // Позиция текста
    gtk_box_pack_start(GTK_BOX(box), title, FALSE, FALSE, 0);

    GtkWidget *scrollable = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(GTK_WIDGET(scrollable), 416, 500);
    gtk_box_pack_start(GTK_BOX(box), scrollable, FALSE, FALSE, 0);

    GtkWidget *avatars = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(avatars), 4);
    gtk_grid_set_column_spacing(GTK_GRID(avatars), 4);
    int avatar_num = 1;
    int i = 0;
    int j = 0;
    GtkWidget *single;
    for(i = 1; i <= 20; i++)    // Columns
    {
        for(j = 1; j <= 5; j++) // Rows
        {
            single = create_avatar_list(avatar_num);
            gtk_widget_set_size_request(GTK_WIDGET(single), 80, 80);
            gtk_grid_attach(GTK_GRID(avatars), single, j, i, 1, 1);
            gtk_widget_set_name(GTK_WIDGET(single), "avatars");
            g_signal_connect(G_OBJECT(single), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
            g_signal_connect(G_OBJECT(single), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
            g_signal_connect(G_OBJECT(single), "button_press_event", G_CALLBACK(avatar_click), NULL);
            avatar_num++;
        }
    }
    gtk_container_add(GTK_CONTAINER(scrollable), avatars);

    gtk_widget_show_all(GTK_WIDGET(t_settings.background));
}
