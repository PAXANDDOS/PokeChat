#include "../inc/client.h"

static bool check_date()
{
    return FALSE;
}

void new_outgoing_message(GtkWidget *messages_block)
{
    // check_date();   // Проверка на совпадение текущей даты с датой последнего сообщения. Если совпадает - не показывать и наоборот
    if(!check_date() && temp == 0)
    {
        GtkWidget *date = gtk_label_new(mx_str_getdate());
        gtk_widget_set_name(GTK_WIDGET(date), "date");
        gtk_widget_set_halign(GTK_WIDGET(date), GTK_ALIGN_CENTER);
        gtk_box_pack_start(GTK_BOX(messages_block), date, FALSE, FALSE, 10);
        gtk_widget_show_all(GTK_WIDGET(date));
        temp++;
    }

    GtkWidget *message_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    //gtk_widget_set_size_request(messages_body, CHAT_W, 100);
    gtk_widget_set_name(GTK_WIDGET(message_body), "messages_body");

    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 35, 35);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar), (int*)35);
    gtk_box_pack_end(GTK_BOX(message_body), avatar, FALSE, FALSE, 0);
    GtkWidget *message = gtk_label_new(msg_data.content);
    gtk_widget_set_name(GTK_WIDGET(message), "message");
    gtk_label_set_line_wrap(GTK_LABEL(message), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(message), PANGO_WRAP_WORD_CHAR);
    gtk_label_set_max_width_chars(GTK_LABEL(message), 50);
    // GtkWidget *nickname = gtk_frame_new("PAXANDDOS");
    // gtk_frame_set_label_widget (GTK_FRAME(nickname), message);   Не работает
    GtkWidget *name_time_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    GtkWidget *time_label = gtk_label_new(mx_str_gettime());
    GtkWidget *nickname = gtk_label_new("PAXANDDOS");
    gtk_widget_set_name(GTK_WIDGET(time_label), "name_time");
    gtk_widget_set_name(GTK_WIDGET(nickname), "name_time");
    gtk_box_pack_start(GTK_BOX(name_time_block), time_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(name_time_block), nickname, FALSE, FALSE, 0);
    gtk_widget_set_valign(GTK_WIDGET(name_time_block), GTK_ALIGN_CENTER);

    gtk_box_pack_end(GTK_BOX(message_body), message, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(message_body), name_time_block, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(messages_block), message_body, FALSE, FALSE, 0);
    gtk_container_set_focus_vadjustment(GTK_CONTAINER(message_body), NULL);
    gtk_widget_show_all(GTK_WIDGET(message_body));
}

void new_incoming_message(GtkWidget *messages_block)
{
    GtkWidget *message_body = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    //gtk_widget_set_size_request(messages_body, CHAT_W, 100);
    gtk_widget_set_name(GTK_WIDGET(message_body), "messages_body");

    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 35, 35);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar), (int*)35);
    GtkWidget *message = gtk_label_new(msg_data.content);
    gtk_widget_set_name(GTK_WIDGET(message), "message");
    gtk_label_set_line_wrap(GTK_LABEL(message), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(message), PANGO_WRAP_WORD_CHAR);
    gtk_label_set_max_width_chars(GTK_LABEL(message), 50);
    // GtkWidget *nickname = gtk_frame_new("PAXANDDOS");
    // gtk_frame_set_label_widget (GTK_FRAME(nickname), message);   Не работает
    GtkWidget *name_time_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    GtkWidget *time_label = gtk_label_new(mx_str_gettime());
    GtkWidget *nickname = gtk_label_new("PAXANDDOS");
    gtk_widget_set_name(GTK_WIDGET(time_label), "name_time");
    gtk_widget_set_name(GTK_WIDGET(nickname), "name_time");
    gtk_box_pack_start(GTK_BOX(name_time_block), time_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(name_time_block), nickname, FALSE, FALSE, 0);
    gtk_widget_set_valign(GTK_WIDGET(name_time_block), GTK_ALIGN_CENTER);

    gtk_box_pack_start(GTK_BOX(message_body), avatar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(message_body), message, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(message_body), name_time_block, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(messages_block), message_body, FALSE, FALSE, 0);
    gtk_widget_show_all(GTK_WIDGET(message_body));
}
