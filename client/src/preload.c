#include "../inc/client.h"

void preload_images() {
    t_settings.standard = gtk_image_new_from_file("client/data/images/settings-standard.png");
    t_messages.standard = gtk_image_new_from_file("client/data/images/messages-standard.png");
    t_contacts.standard = gtk_image_new_from_file("client/data/images/contacts-standard.png");

    t_img_event_box.messages_box = gtk_event_box_new();
    gtk_widget_set_size_request(GTK_WIDGET(t_img_event_box.messages_box), 40, 30);
    gtk_container_add(GTK_CONTAINER(t_img_event_box.messages_box), t_messages.standard);
    
    t_img_event_box.contacts_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(t_img_event_box.contacts_box), t_contacts.standard);

    t_img_event_box.settings_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(t_img_event_box.settings_box), t_settings.standard);
}
