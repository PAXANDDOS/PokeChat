#include "../inc/client.h"

void login_button_click(GtkWidget *widget, GdkEventButton *event, gpointer main_area)
{
    if(widget){}
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_destroy(GTK_WIDGET(t_auth.mystic_event));
        gtk_widget_destroy(GTK_WIDGET(t_auth.instinct_event));
        gtk_widget_destroy(GTK_WIDGET(t_auth.valor_event));
        gtk_widget_destroy(GTK_WIDGET(t_auth.registration_menu));
        build_authorization((GtkWidget**)main_area);
    }
}

void register_button_click(GtkWidget *widget, GdkEventButton *event, gpointer main_area)
{
    if(widget){}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_destroy(GTK_WIDGET(t_auth.login_menu));
        build_registration((GtkWidget**)main_area);
    }
}

void mystic_event_button_click(GtkWidget *widget, GdkEventButton *event)
{
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) 
    {
        gtk_widget_unset_state_flags(GTK_WIDGET(t_auth.instinct_event), GTK_STATE_FLAG_LINK);
        gtk_widget_unset_state_flags(GTK_WIDGET(t_auth.valor_event), GTK_STATE_FLAG_LINK);
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account_temp.team = 1;
    }
}

void instinct_event_button_click(GtkWidget *widget, GdkEventButton *event)
{
    if(widget){}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) 
    {
        gtk_widget_unset_state_flags(GTK_WIDGET(t_auth.mystic_event), GTK_STATE_FLAG_LINK);
        gtk_widget_unset_state_flags(GTK_WIDGET(t_auth.valor_event), GTK_STATE_FLAG_LINK);
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account_temp.team = 2;
    }
}

void valor_event_button_click(GtkWidget *widget, GdkEventButton *event)
{
    if(widget){}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1) 
    {
        gtk_widget_unset_state_flags(GTK_WIDGET(t_auth.mystic_event), GTK_STATE_FLAG_LINK);
        gtk_widget_unset_state_flags(GTK_WIDGET(t_auth.instinct_event), GTK_STATE_FLAG_LINK);
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account_temp.team = 3;
    }
}

void login_butt_click(GtkWidget *widget){
    if(widget) {}

    // check with database

}

void reg_butt_click(GtkWidget *widget){
    if(widget) {}

    t_account_temp.username = mx_del_extra_spaces(t_account_temp.username);
    t_account_temp.name = mx_del_extra_spaces(t_account_temp.name);
    
    if(t_account_temp.username == NULL \
    || !strcmp(t_account_temp.username, "") \
    || t_account_temp.name == NULL \
    || !strcmp(t_account_temp.name, "")
    || t_account_temp.password == NULL \
    || !strcmp(t_account_temp.password, "")
    || t_account_temp.repass == NULL \
    || !strcmp(t_account_temp.repass, "")
    || strlen(t_account_temp.password) < 5 \
    || strcmp(t_account_temp.repass, t_account_temp.password) != 0)
        return;
    
    t_account.avatar = t_avatar.avatar_generated;
    t_account.username = t_account_temp.username;
    t_account.name = t_account_temp.name;
    if(t_account_temp.code == NULL || !strcmp(t_account_temp.code, "")) t_account.code = "000000000000";
    else t_account.code = mx_strjoin(t_account_temp.code, "\0");
    t_account.team = t_account_temp.team;
    t_account.password = t_account_temp.password;
    t_account.theme = 2;
    t_account.background = 1;
    
    printf("REGISTERED:\nUser = %s\n", t_account.username);
    printf("Name = %s\n", t_account.name);
    printf("Code = %s\n", t_account.code);
    printf("Pass = %s\n", t_account.password);
    printf("Team = %hd\n", t_account.team);

    fill_pokemon();     // Filling random data on home tab
    t_leftbar.active = 1;   // Active button in leftbar
    gtk_widget_destroy(GTK_WIDGET(t_application.auth));
    load_providers();
    build_all(&t_application.messanger);  // Main builder function
    gtk_widget_show_all(t_application.messanger);          // Showing window
    gtk_widget_hide(GTK_WIDGET(t_leftbar.msg_scr));     // Hiding messanger tab
    gtk_widget_hide(GTK_WIDGET(t_leftbar.settings_scr));// Hiding settings tab
}
