#include "../inc/client.h"

static bool check_date()
{
    return FALSE;
}

void new_outgoing_message(GtkWidget *messages_block)
{
    // check_date();   // Проверка на совпадение текущей даты с датой последнего сообщения. Если совпадает - не показывать и наоборот
    if(!check_date() && temp == 0) // temp - переменная чтобы дату показало лишь раз при первой отправке
    {
        GtkWidget *date = gtk_label_new(mx_str_getdate());
        gtk_widget_set_name(GTK_WIDGET(date), "date");
        gtk_widget_set_halign(GTK_WIDGET(date), GTK_ALIGN_CENTER);
        gtk_box_pack_start(GTK_BOX(messages_block), date, FALSE, FALSE, 10);
        gtk_widget_show_all(GTK_WIDGET(date));
        temp++;
    }

    GtkWidget *message_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_name(GTK_WIDGET(message_body), "messages_body");
    gtk_box_pack_start(GTK_BOX(messages_block), message_body, FALSE, FALSE, 0);

    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 35, 35);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar_account), (int*)35);
    gtk_box_pack_end(GTK_BOX(message_body), avatar, FALSE, FALSE, 0);

    GtkWidget *name_message_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_box_pack_end(GTK_BOX(message_body), name_message_block, FALSE, FALSE, 0);
    GtkWidget *nickname = gtk_label_new(t_account.username);
    gtk_widget_set_name(GTK_WIDGET(nickname), "msg_name");
    gtk_widget_set_halign(GTK_WIDGET(nickname), GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(name_message_block), nickname, FALSE, FALSE, 0);
    
    GtkWidget *message = gtk_label_new(msg_data.content);
    gtk_widget_set_name(GTK_WIDGET(message), "message");
    gtk_label_set_line_wrap(GTK_LABEL(message), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(message), PANGO_WRAP_WORD_CHAR);
    gtk_label_set_max_width_chars(GTK_LABEL(message), 50);
    gtk_box_pack_end(GTK_BOX(name_message_block), message, FALSE, FALSE, 0);

    GtkWidget *time_label = gtk_label_new(mx_str_gettime());
    gtk_widget_set_name(GTK_WIDGET(time_label), "name_time");
    gtk_widget_set_valign(GTK_WIDGET(time_label), GTK_ALIGN_CENTER);
    gtk_box_pack_end(GTK_BOX(message_body), time_label, FALSE, FALSE, 0);

    gtk_container_set_focus_vadjustment(GTK_CONTAINER(message_body), NULL);
    gtk_widget_show_all(GTK_WIDGET(message_body));
}

void new_incoming_message(GtkWidget *messages_block)
{
    GtkWidget *message_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_name(GTK_WIDGET(message_body), "messages_body");
    gtk_box_pack_start(GTK_BOX(messages_block), message_body, FALSE, FALSE, 0);

    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 35, 35);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar), (int*)35);
    gtk_box_pack_start(GTK_BOX(message_body), avatar, FALSE, FALSE, 0);

    GtkWidget *name_message_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_box_pack_start(GTK_BOX(message_body), name_message_block, FALSE, FALSE, 0);
    GtkWidget *nickname = gtk_label_new("PAXANDDOS");
    gtk_widget_set_name(GTK_WIDGET(nickname), "msg_name");
    gtk_widget_set_halign(GTK_WIDGET(nickname), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(name_message_block), nickname, FALSE, FALSE, 0);

    GtkWidget *message = gtk_label_new(msg_data.content);
    gtk_widget_set_name(GTK_WIDGET(message), "message");
    gtk_label_set_line_wrap(GTK_LABEL(message), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(message), PANGO_WRAP_WORD_CHAR);
    gtk_label_set_max_width_chars(GTK_LABEL(message), 50);
    gtk_box_pack_start(GTK_BOX(name_message_block), message, FALSE, FALSE, 0);

    GtkWidget *time_label = gtk_label_new(mx_str_gettime());
    gtk_widget_set_name(GTK_WIDGET(time_label), "name_time");
    gtk_widget_set_valign(GTK_WIDGET(time_label), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(message_body), time_label, FALSE, FALSE, 0);

    gtk_widget_show_all(GTK_WIDGET(message_body));
}

void new_outgoing_sticker(GtkWidget *messages_block, int sticker_num)
{
    char *path = "client/data/stickers/";
    path = mx_strjoin(path, mx_itoa(sticker_num));
    path = mx_strjoin(path, ".png");

    GtkWidget *sticker_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_name(GTK_WIDGET(sticker_body), "sticker_body");
    gtk_box_pack_start(GTK_BOX(messages_block), sticker_body, FALSE, FALSE, 0);

    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 35, 35);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar_account), (int*)35);
    gtk_box_pack_end(GTK_BOX(sticker_body), avatar, FALSE, FALSE, 0);

    GtkWidget *sticker = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(sticker), 200, 200);
    g_signal_connect(G_OBJECT(sticker), "draw", G_CALLBACK(draw_event_sticker), (char*)path);
    gtk_box_pack_end(GTK_BOX(sticker_body), sticker, FALSE, FALSE, 0);

    GtkWidget *name_time_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    GtkWidget *time_label = gtk_label_new(mx_str_gettime());
    GtkWidget *nickname = gtk_label_new(t_account.username);
    gtk_widget_set_name(GTK_WIDGET(time_label), "name_time");
    gtk_widget_set_name(GTK_WIDGET(nickname), "name_time");
    gtk_box_pack_start(GTK_BOX(name_time_block), time_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(name_time_block), nickname, FALSE, FALSE, 0);
    gtk_widget_set_valign(GTK_WIDGET(name_time_block), GTK_ALIGN_CENTER);
    gtk_box_pack_end(GTK_BOX(sticker_body), name_time_block, FALSE, FALSE, 0);

    gtk_container_set_focus_vadjustment(GTK_CONTAINER(sticker_body), NULL);
    gtk_widget_show_all(GTK_WIDGET(sticker_body));
}

void new_incoming_sticker(GtkWidget *messages_block, int sticker_num)
{
    char *path = "client/data/stickers/";
    path = mx_strjoin(path, mx_itoa(sticker_num));
    path = mx_strjoin(path, ".png");

    GtkWidget *sticker_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_name(GTK_WIDGET(sticker_body), "sticker_body");
    gtk_box_pack_start(GTK_BOX(messages_block), sticker_body, FALSE, FALSE, 0);

    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 35, 35);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar), (int*)35);
    gtk_box_pack_start(GTK_BOX(sticker_body), avatar, FALSE, FALSE, 0);

    GtkWidget *sticker = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(sticker), 200, 200);
    g_signal_connect(G_OBJECT(sticker), "draw", G_CALLBACK(draw_event_sticker), (char*)path);
    gtk_box_pack_start(GTK_BOX(sticker_body), sticker, FALSE, FALSE, 0);

    GtkWidget *name_time_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    GtkWidget *time_label = gtk_label_new(mx_str_gettime());
    GtkWidget *nickname = gtk_label_new("Gazaris");
    gtk_widget_set_name(GTK_WIDGET(time_label), "name_time");
    gtk_widget_set_name(GTK_WIDGET(nickname), "name_time");
    gtk_box_pack_start(GTK_BOX(name_time_block), time_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(name_time_block), nickname, FALSE, FALSE, 0);
    gtk_widget_set_valign(GTK_WIDGET(name_time_block), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(sticker_body), name_time_block, FALSE, FALSE, 0);

    gtk_container_set_focus_vadjustment(GTK_CONTAINER(sticker_body), NULL);
    gtk_widget_show_all(GTK_WIDGET(sticker_body));
}

void new_outgoing_embedded(GtkWidget *messages_block, char* path)
{
    GtkWidget *embedded_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_name(GTK_WIDGET(embedded_body), "embedded_body");
    gtk_box_pack_start(GTK_BOX(messages_block), embedded_body, FALSE, FALSE, 0);

    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 35, 35);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar_account), (int*)35);
    gtk_box_pack_end(GTK_BOX(embedded_body), avatar, FALSE, FALSE, 0);

    const GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(path, NULL);
    int a = gdk_pixbuf_get_width(pixbuf), b = gdk_pixbuf_get_height(pixbuf);
    g_object_unref(G_OBJECT(pixbuf));
    printf("File: %i x %i\n", a, b);
    int old_b = b;
    if(b > 200) b = 200;
    a = b * a / old_b;
    printf("Resized: %i x %i\n", a, b);

    GtkWidget *embedded = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(embedded), a, b);
    g_signal_connect(G_OBJECT(embedded), "draw", G_CALLBACK(draw_event_embedded), (char*)path);
    //gtk_box_pack_end(GTK_BOX(embedded_body), embedded, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(embedded_body), embedded, FALSE, FALSE, 0);

    GtkWidget *name_time_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    GtkWidget *time_label = gtk_label_new(mx_str_gettime());
    GtkWidget *nickname = gtk_label_new(t_account.username);
    gtk_widget_set_name(GTK_WIDGET(time_label), "name_time");
    gtk_widget_set_name(GTK_WIDGET(nickname), "name_time");
    gtk_box_pack_start(GTK_BOX(name_time_block), time_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(name_time_block), nickname, FALSE, FALSE, 0);
    gtk_widget_set_valign(GTK_WIDGET(name_time_block), GTK_ALIGN_CENTER);
    gtk_box_pack_end(GTK_BOX(embedded_body), name_time_block, FALSE, FALSE, 0);

    gtk_container_set_focus_vadjustment(GTK_CONTAINER(embedded_body), NULL);
    gtk_widget_show_all(GTK_WIDGET(embedded_body));
}

void new_incoming_embedded(GtkWidget *messages_block, char* path)
{
    GtkWidget *embedded_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_name(GTK_WIDGET(embedded_body), "embedded_body");
    gtk_box_pack_start(GTK_BOX(messages_block), embedded_body, FALSE, FALSE, 0);

    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 35, 35);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar_account), (int*)35);
    gtk_box_pack_start(GTK_BOX(embedded_body), avatar, FALSE, FALSE, 0);

    const GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(path, NULL);
    int a = gdk_pixbuf_get_width(pixbuf), b = gdk_pixbuf_get_height(pixbuf);
    g_object_unref(G_OBJECT(pixbuf));
    printf("File: %i x %i\n", a, b);
    int old_b = b;
    if(b > 200) b = 200;
    a = b * a / old_b;
    printf("Resized: %i x %i\n", a, b);

    GtkWidget *embedded = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(embedded), a, b);
    g_signal_connect(G_OBJECT(embedded), "draw", G_CALLBACK(draw_event_embedded), (char*)path);
    //gtk_box_pack_end(GTK_BOX(embedded_body), embedded, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(embedded_body), embedded, FALSE, FALSE, 0);

    GtkWidget *name_time_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    GtkWidget *time_label = gtk_label_new(mx_str_gettime());
    GtkWidget *nickname = gtk_label_new(t_account.username);
    gtk_widget_set_name(GTK_WIDGET(time_label), "name_time");
    gtk_widget_set_name(GTK_WIDGET(nickname), "name_time");
    gtk_box_pack_start(GTK_BOX(name_time_block), time_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(name_time_block), nickname, FALSE, FALSE, 0);
    gtk_widget_set_valign(GTK_WIDGET(name_time_block), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(embedded_body), name_time_block, FALSE, FALSE, 0);

    gtk_container_set_focus_vadjustment(GTK_CONTAINER(embedded_body), NULL);
    gtk_widget_show_all(GTK_WIDGET(embedded_body));
}
