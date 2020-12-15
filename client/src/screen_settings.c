#include "../inc/client.h"

static void build_account_menu(GtkWidget *menu_block)
{
    GtkWidget *title1 = gtk_label_new("MY ACCOUNT");
    gtk_widget_set_name(GTK_WIDGET(title1), "title1");                // Имя
    gtk_widget_set_halign(title1, GTK_ALIGN_START);                     // Позиция текста
    gtk_box_pack_start(GTK_BOX(menu_block), title1, FALSE, FALSE, 0);
    //--//
    GtkWidget *account_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(account_block), "account_block");
    gtk_box_pack_start(GTK_BOX(menu_block), account_block, FALSE, FALSE, 0);
    //--//
    GtkWidget *user_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(account_block), user_box, FALSE, FALSE, 20);
    GtkWidget *avatar_container = gtk_fixed_new();
    gtk_widget_set_valign(GTK_WIDGET(avatar_container), GTK_ALIGN_CENTER);
    GtkWidget *avatar = gtk_drawing_area_new();
    GtkWidget *add_button = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(add_button), "add_button");
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 100, 100);
    gtk_widget_set_size_request(GTK_WIDGET(add_button), 32, 32);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar), (int*)100);
    gtk_fixed_put(GTK_FIXED(avatar_container), avatar, 0, 0);
    gtk_fixed_put(GTK_FIXED(avatar_container), add_button, 70, 0);
    gtk_box_pack_start(GTK_BOX(user_box), avatar_container, FALSE, FALSE, 0);
    GtkWidget *names_account = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_valign(GTK_WIDGET(names_account), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(user_box), names_account, FALSE, FALSE, 20);
    t_settings_labels.username = gtk_label_new(t_account.username);                                                                        // Получить ник пользователя
    gtk_widget_set_name(GTK_WIDGET(t_settings_labels.username), "nickname-s");                // Имя
    gtk_widget_set_halign(GTK_WIDGET(t_settings_labels.username), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(names_account), t_settings_labels.username, FALSE, FALSE, 0);
    t_settings_labels.name = gtk_label_new(t_account.name);                            
    gtk_widget_set_name(GTK_WIDGET(t_settings_labels.name), "nickname-n");                // Имя
    gtk_widget_set_halign(GTK_WIDGET(t_settings_labels.name), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(names_account), t_settings_labels.name, FALSE, FALSE, 10);
    GtkWidget *exit_button = gtk_event_box_new();
    gtk_widget_set_size_request(GTK_WIDGET(exit_button), 50, 50);
    gtk_widget_set_name(GTK_WIDGET(exit_button), "exit_button");
    gtk_widget_set_valign(GTK_WIDGET(exit_button), GTK_ALIGN_CENTER);
    gtk_box_pack_end(GTK_BOX(user_box), exit_button, FALSE, FALSE, 0);
    //
    GtkWidget *info_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(info_box), "info_box");
    gtk_box_pack_start(GTK_BOX(account_block), info_box, FALSE, FALSE, 0);
    GtkWidget *username_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(username_field), "settings_fields");
    g_signal_connect(G_OBJECT(username_field), "changed", G_CALLBACK(username_field_change_event), NULL);
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_field), "Username");
    gtk_entry_set_max_length(GTK_ENTRY(username_field), 10);
    gtk_entry_set_text(GTK_ENTRY(username_field), t_account.username);
    gtk_box_pack_start(GTK_BOX(info_box), username_field, TRUE, TRUE, 10); 
    GtkWidget *firstaname_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(firstaname_field), "settings_fields");
    g_signal_connect(G_OBJECT(firstaname_field), "changed", G_CALLBACK(firstaname_field_change_event), NULL);
    gtk_entry_set_placeholder_text(GTK_ENTRY(firstaname_field), "Name");
    gtk_entry_set_max_length(GTK_ENTRY(firstaname_field), 10);
    gtk_entry_set_text(GTK_ENTRY(firstaname_field), t_account.name);
    gtk_box_pack_start(GTK_BOX(info_box), firstaname_field, TRUE, TRUE, 10);
    GtkWidget *code_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(code_field), "settings_fields");
    g_signal_connect(G_OBJECT(code_field), "changed", G_CALLBACK(code_field_change_event), NULL);
    gtk_entry_set_placeholder_text(GTK_ENTRY(code_field), "Trainer code");
    gtk_entry_set_max_length(GTK_ENTRY(code_field), 12);
    gtk_entry_set_text(GTK_ENTRY(code_field), t_account.code);
    gtk_box_pack_start(GTK_BOX(info_box), code_field, TRUE, TRUE, 10);
    GtkWidget *password_field = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_field), FALSE);
    // g_signal_connect(G_OBJECT(password_field), "changed", G_CALLBACK(password_field_change_event), NULL);
    gtk_widget_set_name(GTK_WIDGET(password_field), "settings_fields");
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_field), "Password");
    gtk_entry_set_max_length(GTK_ENTRY(password_field), 16);
    gtk_box_pack_start(GTK_BOX(info_box), password_field, TRUE, TRUE, 10);
    GtkWidget *repassword_field = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(repassword_field), FALSE);
    // g_signal_connect(G_OBJECT(repassword_field), "changed", G_CALLBACK(repassword_field_change_event), NULL);
    gtk_widget_set_name(GTK_WIDGET(repassword_field), "settings_fields");
    gtk_entry_set_placeholder_text(GTK_ENTRY(repassword_field), "Repeat password");
    gtk_entry_set_max_length(GTK_ENTRY(repassword_field), 16);
    gtk_box_pack_start(GTK_BOX(info_box), repassword_field, TRUE, TRUE, 10);
    GtkWidget *apply_butt = gtk_button_new_with_label("Apply");
    gtk_widget_set_name(GTK_WIDGET(apply_butt), "apply_button");
    gtk_button_set_relief(GTK_BUTTON(apply_butt), GTK_RELIEF_NONE);
    gtk_widget_set_size_request(GTK_WIDGET(apply_butt), 100, 10);
    gtk_box_pack_start(GTK_BOX(info_box), apply_butt, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(apply_butt), "clicked", G_CALLBACK(apply_butt_click), NULL);
    
    g_signal_connect(G_OBJECT(exit_button), "enter-notify-event",
        G_CALLBACK(exit_button_enter_notify), NULL);
    g_signal_connect(G_OBJECT(exit_button), "leave-notify-event",
        G_CALLBACK(exit_button_leave_notify), NULL);
    g_signal_connect(G_OBJECT(exit_button), "button_press_event",
        G_CALLBACK(exit_button_click), NULL);

    g_signal_connect(G_OBJECT(add_button), "enter-notify-event",
        G_CALLBACK(add_button_enter_notify), NULL);
    g_signal_connect(G_OBJECT(add_button), "leave-notify-event",
        G_CALLBACK(add_button_leave_notify), NULL);
    g_signal_connect(G_OBJECT(add_button), "button_press_event",
        G_CALLBACK(add_button_click_click), NULL);
}

static void build_teams_menu(GtkWidget *menu_block)
{
    GtkWidget *title2 = gtk_label_new("SELECT TEAM");
    gtk_widget_set_name(GTK_WIDGET(title2), "title2");                // Имя
    gtk_widget_set_halign(title2, GTK_ALIGN_START);                     // Позиция текста
    gtk_box_pack_start(GTK_BOX(menu_block), title2, FALSE, FALSE, 0);
    //--//
    GtkWidget *teams_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(teams_block), "teams_block");
    gtk_box_pack_start(GTK_BOX(menu_block), teams_block, FALSE, FALSE, 0);
    //--//
    t_teams.team_mystic = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_teams.team_mystic), "mystic");
    gtk_widget_set_size_request(GTK_WIDGET(t_teams.team_mystic), TEAM_W, TEAM_H);
    gtk_box_pack_start(GTK_BOX(teams_block), t_teams.team_mystic, TRUE, FALSE, 0);
    t_teams.team_instinct = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_teams.team_instinct), "instinct");
    gtk_widget_set_size_request(GTK_WIDGET(t_teams.team_instinct), TEAM_W, TEAM_H);
    gtk_box_pack_start(GTK_BOX(teams_block), t_teams.team_instinct, TRUE, FALSE, 0);
    t_teams.team_valor = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_teams.team_valor), "valor");
    gtk_widget_set_size_request(GTK_WIDGET(t_teams.team_valor), TEAM_W, TEAM_H);
    gtk_box_pack_start(GTK_BOX(teams_block), t_teams.team_valor, TRUE, FALSE, 0);

    if(t_account.team == 1) 
        gtk_widget_set_state_flags(GTK_WIDGET(t_teams.team_mystic), GTK_STATE_FLAG_LINK, TRUE);
    else if(t_account.team == 2) 
        gtk_widget_set_state_flags(GTK_WIDGET(t_teams.team_instinct), GTK_STATE_FLAG_LINK, TRUE);
    else if(t_account.team == 3) 
        gtk_widget_set_state_flags(GTK_WIDGET(t_teams.team_valor), GTK_STATE_FLAG_LINK, TRUE);

    g_signal_connect(G_OBJECT(t_teams.team_mystic), "enter-notify-event",
        G_CALLBACK(team_mystic_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_teams.team_mystic), "leave-notify-event",
        G_CALLBACK(team_mystic_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_teams.team_mystic), "button_press_event",
        G_CALLBACK(team_mystic_click_click), NULL);
        
    g_signal_connect(G_OBJECT(t_teams.team_instinct), "enter-notify-event",
        G_CALLBACK(team_instinct_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_teams.team_instinct), "leave-notify-event",
        G_CALLBACK(team_instinct_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_teams.team_instinct), "button_press_event",
        G_CALLBACK(team_instinct_click_click), NULL);

    g_signal_connect(G_OBJECT(t_teams.team_valor), "enter-notify-event",
        G_CALLBACK(team_valor_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_teams.team_valor), "leave-notify-event",
        G_CALLBACK(team_valor_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_teams.team_valor), "button_press_event",
        G_CALLBACK(team_valor_click_click), NULL);
}

static void build_chat_menu(GtkWidget *menu_block)
{
    GtkWidget *title3 = gtk_label_new("CUSTOMIZE CHAT");
    gtk_widget_set_name(GTK_WIDGET(title3), "title2");                // Имя
    gtk_widget_set_halign(title3, GTK_ALIGN_START);                     // Позиция текста
    gtk_box_pack_start(GTK_BOX(menu_block), title3, FALSE, FALSE, 0);
    //--//
    
}

void build_settings_menu(GtkWidget **stgscreen)
{
    // Loading CSS file
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "client/data/css/settings_scr.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    //
    // Creating workspace
    //GtkAdjustment *vadjustment = gtk_adjustment_new(0, 0, CUR_WIDTH-LEFTBAR_W, 200, 200, CUR_HEIGHT);    // Параметры скролла
    t_main_scr.settings_scr = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_name(GTK_WIDGET(t_main_scr.settings_scr), "settings_scr");
    gtk_widget_set_size_request(GTK_WIDGET(t_main_scr.settings_scr), CUR_WIDTH-LEFTBAR_W, CUR_HEIGHT);
    gtk_fixed_put(GTK_FIXED(*stgscreen), t_main_scr.settings_scr, LEFTBAR_W, 0);
    GtkWidget *main = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(t_main_scr.settings_scr), main);
    //--//--//
    GtkWidget *menu_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(menu_block), CUR_WIDTH-LEFTBAR_W, 0);
    gtk_widget_set_name(GTK_WIDGET(menu_block), "menu_block");
    gtk_fixed_put(GTK_FIXED(main),menu_block, 0, 0);
    //--//--//
    build_account_menu(menu_block);
    build_teams_menu(menu_block);
    build_chat_menu(menu_block);
}
