#include "../inc/client.h"

static void focus_switch(GtkWidget *widget, GtkWidget *target) {
    if(widget){
        gtk_widget_set_can_focus(GTK_WIDGET(target), TRUE);
        gtk_widget_grab_focus(GTK_WIDGET(target));
    }
}

void build_registration(GtkWidget **main_area)
{
    t_auth.registration_menu = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_auth.registration_menu), "auth_screen");
    gtk_widget_set_size_request(GTK_WIDGET(t_auth.registration_menu), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_fixed_put(GTK_FIXED(*main_area),t_auth.registration_menu, 0, 0);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(box), "login_menu");
    gtk_widget_set_size_request(GTK_WIDGET(box), 430, 0);
    gtk_widget_set_halign(GTK_WIDGET(box), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(box), GTK_ALIGN_CENTER);
    gtk_container_add(GTK_CONTAINER(t_auth.registration_menu), box);
    gtk_widget_set_can_focus(GTK_WIDGET(box), TRUE);
    gtk_widget_grab_focus(GTK_WIDGET(box));

    GtkWidget *title1 = gtk_label_new("Create an account");
    gtk_widget_set_name(GTK_WIDGET(title1), "login_title1");
    gtk_widget_set_halign(title1, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(box), title1, FALSE, FALSE, 0);

    GtkWidget *username_label = gtk_label_new("USERNAME");
    gtk_widget_set_name(GTK_WIDGET(username_label), "login_label");
    gtk_widget_set_halign(username_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(box), username_label, FALSE, FALSE, 4);
    GtkWidget *username_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(username_field), "login_fields");
    g_signal_connect(G_OBJECT(username_field), "insert-text", G_CALLBACK(all_input_event), NULL);
    g_signal_connect(G_OBJECT(username_field), "changed", G_CALLBACK(username_field_change_event), NULL);
    gtk_entry_set_max_length(GTK_ENTRY(username_field), MAX_USERNAME);
    gtk_box_pack_start(GTK_BOX(box), username_field, TRUE, TRUE, 0);

    GtkWidget *name_label = gtk_label_new("NAME");
    gtk_widget_set_name(GTK_WIDGET(name_label), "login_label");
    gtk_widget_set_halign(name_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(box), name_label, FALSE, FALSE, 4);
    GtkWidget *name_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(name_field), "login_fields");
    g_signal_connect(G_OBJECT(name_field), "insert-text", G_CALLBACK(firstname_input_event), NULL);
    g_signal_connect(G_OBJECT(name_field), "changed", G_CALLBACK(firstname_field_change_event), NULL);
    g_signal_connect(G_OBJECT(username_field), "activate", G_CALLBACK(focus_switch), name_field);
    gtk_entry_set_max_length(GTK_ENTRY(name_field), MAX_NAME);
    gtk_box_pack_start(GTK_BOX(box), name_field, TRUE, TRUE, 0);

    GtkWidget *pass_label = gtk_label_new("PASSWORD");
    gtk_widget_set_name(GTK_WIDGET(pass_label), "login_label");
    gtk_widget_set_halign(pass_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(box), pass_label, FALSE, FALSE, 4);
    GtkWidget *pass_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(pass_field), "login_fields");
    gtk_entry_set_visibility(GTK_ENTRY(pass_field), FALSE);
    g_signal_connect(G_OBJECT(pass_field), "insert-text", G_CALLBACK(all_input_event), NULL);
    g_signal_connect(G_OBJECT(pass_field), "changed", G_CALLBACK(pass_field_change_event), NULL);
    g_signal_connect(G_OBJECT(name_field), "activate", G_CALLBACK(focus_switch), pass_field);
    gtk_entry_set_max_length(GTK_ENTRY(pass_field), MAX_PASS);
    gtk_box_pack_start(GTK_BOX(box), pass_field, TRUE, TRUE, 0);

    GtkWidget *repass_label = gtk_label_new("REPEAT PASSWORD");
    gtk_widget_set_name(GTK_WIDGET(repass_label), "login_label");
    gtk_widget_set_halign(repass_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(box), repass_label, FALSE, FALSE, 4);
    GtkWidget *repass_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(repass_field), "login_fields");
    gtk_entry_set_visibility(GTK_ENTRY(repass_field), FALSE);
    g_signal_connect(G_OBJECT(repass_field), "insert-text", G_CALLBACK(all_input_event), NULL);
    g_signal_connect(G_OBJECT(repass_field), "changed", G_CALLBACK(repass_field_change_event), NULL);
    g_signal_connect(G_OBJECT(pass_field), "activate", G_CALLBACK(focus_switch), repass_field);
    gtk_entry_set_max_length(GTK_ENTRY(repass_field), MAX_PASS);
    gtk_box_pack_start(GTK_BOX(box), repass_field, TRUE, TRUE, 0);

    GtkWidget *code_label = gtk_label_new("TRAINER CODE");
    gtk_widget_set_name(GTK_WIDGET(code_label), "login_label");
    gtk_widget_set_halign(code_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(box), code_label, FALSE, FALSE, 4);
    GtkWidget *code_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(code_field), "login_fields");
    gtk_entry_set_max_length(GTK_ENTRY(code_field), MAX_CODE);
    g_signal_connect(G_OBJECT(code_field), "insert-text", G_CALLBACK(code_input_event), NULL);
    g_signal_connect(G_OBJECT(code_field), "changed", G_CALLBACK(code_field_change_event), NULL);
    g_signal_connect(G_OBJECT(repass_field), "activate", G_CALLBACK(focus_switch), code_field);
    gtk_entry_set_placeholder_text(GTK_ENTRY(code_field), "(optional)");
    gtk_box_pack_start(GTK_BOX(box), code_field, TRUE, TRUE, 0);

    GtkWidget *team_label = gtk_label_new("SELECT TEAM");
    gtk_widget_set_name(GTK_WIDGET(team_label), "login_label");
    gtk_widget_set_halign(team_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(box), team_label, FALSE, FALSE, 4);
    GtkWidget *team_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(box), team_buttons, FALSE, FALSE, 0);

    GtkWidget *mystic_event = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(mystic_event), "mystic_event");
    GtkWidget *team_mystic = gtk_label_new("Mystic");
    gtk_widget_set_name(GTK_WIDGET(team_mystic), "team_mystic_selection");
    gtk_container_add(GTK_CONTAINER(mystic_event), team_mystic);
    gtk_box_pack_start(GTK_BOX(team_buttons), mystic_event, TRUE, FALSE, 0);

    GtkWidget *instinct_event = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(instinct_event), "instinct_event");
    GtkWidget *team_instinct = gtk_label_new("Instinct");
    gtk_widget_set_name(GTK_WIDGET(team_instinct), "team_instinct_selection");
    gtk_container_add(GTK_CONTAINER(instinct_event), team_instinct);
    gtk_box_pack_start(GTK_BOX(team_buttons), instinct_event, TRUE, FALSE, 0);

    GtkWidget *valor_event = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(valor_event), "valor_event");
    GtkWidget *team_valor = gtk_label_new("Valor");
    gtk_widget_set_name(GTK_WIDGET(team_valor), "team_valor_selection");
    gtk_container_add(GTK_CONTAINER(valor_event), team_valor);
    gtk_box_pack_start(GTK_BOX(team_buttons), valor_event, TRUE, FALSE, 0);

    GtkWidget *reg_button = gtk_button_new_with_label("Create an account");
    gtk_widget_set_name(GTK_WIDGET(reg_button), "login_button");
    gtk_button_set_relief(GTK_BUTTON(reg_button), GTK_RELIEF_NONE);
    gtk_widget_set_size_request(GTK_WIDGET(reg_button), 100, 20);
    gtk_box_pack_start(GTK_BOX(box), reg_button, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(reg_button), "clicked", G_CALLBACK(reg_butt_click), NULL);

    GtkWidget *event_login = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(event_login), "event_register");
    GtkWidget *log_label = gtk_label_new("Already have an account?");
    gtk_widget_set_name(GTK_WIDGET(log_label), "reg_label");
    gtk_container_add(GTK_CONTAINER(event_login), log_label);
    gtk_widget_set_halign(event_login, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(box), event_login, FALSE, FALSE, 4);

    gtk_widget_show_all(GTK_WIDGET(t_auth.registration_menu));

    g_signal_connect(G_OBJECT(event_login), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(event_login), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(event_login), "button_press_event", G_CALLBACK(login_button_click), main_area);

    g_signal_connect(G_OBJECT(mystic_event), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(mystic_event), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(mystic_event), "button_press_event", G_CALLBACK(mystic_event_button_click), team_buttons);

    g_signal_connect(G_OBJECT(instinct_event), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(instinct_event), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(instinct_event), "button_press_event", G_CALLBACK(instinct_event_button_click), team_buttons);

    g_signal_connect(G_OBJECT(valor_event), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(valor_event), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(valor_event), "button_press_event", G_CALLBACK(valor_event_button_click), team_buttons);
}

void build_authorization(GtkWidget **main_area)
{
    t_auth.login_menu = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_auth.login_menu), "auth_screen");
    gtk_widget_set_size_request(GTK_WIDGET(t_auth.login_menu), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_fixed_put(GTK_FIXED(*main_area), t_auth.login_menu, 0, 0);
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(box), "login_menu");
    gtk_widget_set_size_request(GTK_WIDGET(box), 430, 0);
    gtk_widget_set_halign(GTK_WIDGET(box), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(box), GTK_ALIGN_CENTER);
    gtk_container_add(GTK_CONTAINER(t_auth.login_menu), box);

    GtkWidget *title1 = gtk_label_new("Welcome back!");
    gtk_widget_set_name(GTK_WIDGET(title1), "login_title1");
    gtk_widget_set_halign(title1, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(box), title1, FALSE, FALSE, 0);

    int i = 0;
    char *phrase = ";";
    while(i == 0)
    {
        phrase = random_phrase();
        i++;
    }
    GtkWidget *title2 = gtk_label_new(phrase);
    gtk_label_set_line_wrap(GTK_LABEL(title2), TRUE);
    gtk_label_set_max_width_chars(GTK_LABEL(title2), 58);
    gtk_label_set_line_wrap_mode(GTK_LABEL(title2), PANGO_WRAP_WORD_CHAR);
    gtk_widget_set_name(GTK_WIDGET(title2), "login_title2");
    gtk_widget_set_halign(title2, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(box), title2, FALSE, FALSE, 0);

    GtkWidget *login_label = gtk_label_new("USERNAME");
    gtk_widget_set_name(GTK_WIDGET(login_label), "login_label");
    gtk_widget_set_halign(login_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(box), login_label, FALSE, FALSE, 4);
    GtkWidget *username_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(username_field), "login_fields");
    g_signal_connect(G_OBJECT(username_field), "insert-text", G_CALLBACK(all_input_event), NULL);
    g_signal_connect(G_OBJECT(username_field), "changed", G_CALLBACK(username_field_change_event), NULL);
    gtk_widget_set_can_focus(GTK_WIDGET(username_field), TRUE);
    gtk_widget_grab_focus(GTK_WIDGET(username_field));
    gtk_entry_set_max_length(GTK_ENTRY(username_field), MAX_USERNAME);
    gtk_box_pack_start(GTK_BOX(box), username_field, TRUE, TRUE, 0);

    GtkWidget *pass_label = gtk_label_new("PASSWORD");
    gtk_widget_set_name(GTK_WIDGET(pass_label), "login_label");
    gtk_widget_set_halign(pass_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(box), pass_label, FALSE, FALSE, 4);
    GtkWidget *pass_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(pass_field), "login_fields");
    g_signal_connect(G_OBJECT(pass_field), "insert-text", G_CALLBACK(all_input_event), NULL);
    g_signal_connect(G_OBJECT(pass_field), "changed", G_CALLBACK(pass_field_change_event), NULL);
    g_signal_connect(G_OBJECT(username_field), "activate", G_CALLBACK(focus_switch), pass_field);
    gtk_entry_set_max_length(GTK_ENTRY(pass_field), MAX_PASS);
    gtk_entry_set_visibility(GTK_ENTRY(pass_field), FALSE);
    gtk_box_pack_start(GTK_BOX(box), pass_field, TRUE, TRUE, 0);

    GtkWidget *login_butt = gtk_button_new_with_label("Login");
    gtk_widget_set_name(GTK_WIDGET(login_butt), "login_button");
    gtk_button_set_relief(GTK_BUTTON(login_butt), GTK_RELIEF_NONE);
    gtk_widget_set_size_request(GTK_WIDGET(login_butt), 100, 20);
    gtk_box_pack_start(GTK_BOX(box), login_butt, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(pass_field), "activate", G_CALLBACK(login_butt_click), pass_field);
    g_signal_connect(G_OBJECT(login_butt), "clicked", G_CALLBACK(login_butt_click), pass_field);

    GtkWidget *event_register = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(event_register), "event_register");
    GtkWidget *reg_label = gtk_label_new("Need an account?");
    gtk_widget_set_name(GTK_WIDGET(reg_label), "reg_label");
    gtk_container_add(GTK_CONTAINER(event_register), reg_label);
    gtk_widget_set_halign(event_register, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(box), event_register, FALSE, FALSE, 4);

    gtk_widget_show_all(GTK_WIDGET(t_auth.login_menu));
    g_signal_connect(G_OBJECT(event_register), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(event_register), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(event_register), "button_press_event", G_CALLBACK(register_button_click), main_area);
}
