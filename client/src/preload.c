#include "../inc/client.h"

void preload_images() 
{
    home_img.active = true;
    home_img.basic = "client/data/images/home.png";
    home_img.hovered = "client/data/images/home-hovered.png";
    home_img.standard = gtk_image_new_from_file(home_img.hovered);

    messages_img.active = false;
    messages_img.basic = "client/data/images/messanger.png";
    messages_img.hovered = "client/data/images/messanger-hovered.png";
    messages_img.standard = gtk_image_new_from_file(messages_img.basic);

    group_img.active = false;
    group_img.basic = "client/data/images/group-inactive.png";
    group_img.hovered = NULL; //"client/data/images/group-hovered.png";
    group_img.standard = gtk_image_new_from_file(group_img.basic);

    events_img.active = false;
    events_img.basic = "client/data/images/events-inactive.png";
    events_img.hovered = NULL; //"client/data/images/events-hovered.png";
    events_img.standard = gtk_image_new_from_file(events_img.basic);

    settings_img.active = false;
    settings_img.basic = "client/data/images/settings.png";
    settings_img.hovered = "client/data/images/settings-hovered.png";
    settings_img.standard = gtk_image_new_from_file(settings_img.basic);

    t_active = &home_img;

    t_img_event_box.home_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(t_img_event_box.home_box), home_img.standard);

    t_img_event_box.messages_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(t_img_event_box.messages_box), messages_img.standard);

    t_img_event_box.group_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(t_img_event_box.group_box), group_img.standard);

    t_img_event_box.events_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(t_img_event_box.events_box), events_img.standard);

    t_img_event_box.settings_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(t_img_event_box.settings_box), settings_img.standard);
}
