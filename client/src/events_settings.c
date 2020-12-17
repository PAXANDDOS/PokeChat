#include "../inc/client.h"

void exit_button_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void exit_button_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void exit_button_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
}

//

void add_button_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void add_button_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void add_button_click_click(GtkWidget *widget, GdkEventButton *event) {
    if(widget) {}
    if(event) {}
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(t_main.window), action,  "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        printf("Got: %s\n", filename);
        //t_account.avatar = filename;
        free(filename);
    }

    gtk_widget_destroy (dialog);
}

void gallery_button_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE);
}

void gallery_button_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void gallery_button_click_click(GtkWidget *widget, GdkEventButton *event, GtkWidget *main) {
    if(widget) {}
    if(event) {}
    create_gallery(main);
}

//

void username_field_change_event(GtkWidget *widget) {
    if(strlen(gtk_entry_get_text(GTK_ENTRY(widget))) > 0)
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK);
    else 
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);

    t_account_temp.username = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget)));
}

void firstaname_field_change_event(GtkWidget *widget) {
    if(strlen(gtk_entry_get_text(GTK_ENTRY(widget))) > 0)
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK);
    else 
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);

    t_account_temp.name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget)));
}

void code_field_change_event(GtkWidget *widget) {
    if(strlen(gtk_entry_get_text(GTK_ENTRY(widget))) > 0)
        gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK);
    else 
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);

    t_account_temp.code = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget)));
}

void apply_butt_click(GtkWidget *widget){
    if(widget) {}
    if(t_account_temp.username == NULL || !strcmp(t_account_temp.username, "") || t_account_temp.name == NULL || !strcmp(t_account_temp.name, ""))
        return;
    t_account.username = t_account_temp.username;
    t_account.name = t_account_temp.name;
    t_account.code = t_account_temp.code;
    gtk_label_set_text(GTK_LABEL(t_settings_labels.username), t_account.username);
    gtk_label_set_text(GTK_LABEL(t_settings_labels.name), t_account.name);
}

//

void team_mystic_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, FALSE);
}

void team_mystic_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void team_mystic_click_click(GtkWidget *widget, GdkEventButton *event) {
    if(t_account.team == 1) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_unset_state_flags(GTK_WIDGET(t_teams.team_instinct), GTK_STATE_FLAG_LINK);
        gtk_widget_unset_state_flags(GTK_WIDGET(t_teams.team_valor), GTK_STATE_FLAG_LINK);
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account.team = 1;
    }
    printf("Team: %i\n", t_account.team);
}


void team_instinct_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, FALSE);
}

void team_instinct_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void team_instinct_click_click(GtkWidget *widget, GdkEventButton *event) {
    if(t_account.team == 2) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_unset_state_flags(GTK_WIDGET(t_teams.team_mystic), GTK_STATE_FLAG_LINK);
        gtk_widget_unset_state_flags(GTK_WIDGET(t_teams.team_valor), GTK_STATE_FLAG_LINK);
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account.team = 2;
    }
    printf("Team: %i\n", t_account.team);
}


void team_valor_enter_notify(GtkWidget *widget) {
    gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, FALSE);
}

void team_valor_leave_notify(GtkWidget *widget) {
    gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
}

void team_valor_click_click(GtkWidget *widget, GdkEventButton *event) {
    if(t_account.team == 3) return;
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_unset_state_flags(GTK_WIDGET(t_teams.team_instinct), GTK_STATE_FLAG_LINK);
        gtk_widget_unset_state_flags(GTK_WIDGET(t_teams.team_mystic), GTK_STATE_FLAG_LINK);
        gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_LINK, TRUE);
        t_account.team = 3;
    }
    printf("Team: %i\n", t_account.team);
}
