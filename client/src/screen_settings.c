#include "../inc/client.h"

static void build_account_menu(GtkWidget *menu_block, GtkWidget *main)
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
    gtk_box_pack_start(GTK_BOX(user_box), avatar_container, FALSE, FALSE, 0);

    GtkWidget *avatar = gtk_drawing_area_new();
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar_account), (int*)100);
    gtk_fixed_put(GTK_FIXED(avatar_container), avatar, 0, 0);

    GtkWidget *add_button = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(add_button), "add_button");
    tooltip("Upload picture",add_button);
    gtk_fixed_put(GTK_FIXED(avatar_container), add_button, 70, 0);

    GtkWidget *gallery_button = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(gallery_button), "gallery_button");
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 100, 100);
    gtk_widget_set_size_request(GTK_WIDGET(add_button), 32, 32);
    gtk_widget_set_size_request(GTK_WIDGET(gallery_button), 32, 32);
    tooltip("Choose picture",gallery_button);
    gtk_fixed_put(GTK_FIXED(avatar_container), gallery_button, 84, 32);

    GtkWidget *names_account = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_valign(GTK_WIDGET(names_account), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(user_box), names_account, FALSE, FALSE, 20);

    t_settings.username = gtk_label_new(t_account.username);
    gtk_widget_set_name(GTK_WIDGET(t_settings.username), "nickname-s");
    gtk_widget_set_halign(GTK_WIDGET(t_settings.username), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(names_account), t_settings.username, FALSE, FALSE, 0);
    t_settings.name = gtk_label_new(t_account.name);
    gtk_widget_set_name(GTK_WIDGET(t_settings.name), "nickname-n");
    gtk_widget_set_halign(GTK_WIDGET(t_settings.name), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(names_account), t_settings.name, FALSE, FALSE, 10);

    GtkWidget *exit_button = gtk_event_box_new();
    gtk_widget_set_size_request(GTK_WIDGET(exit_button), 50, 50);
    gtk_widget_set_name(GTK_WIDGET(exit_button), "exit_button");
    gtk_widget_set_valign(GTK_WIDGET(exit_button), GTK_ALIGN_CENTER);
    gtk_box_pack_end(GTK_BOX(user_box), exit_button, FALSE, FALSE, 0);
    tooltip("Exit",exit_button);
    //
    GtkWidget *info_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(info_box), "info_box");
    gtk_box_pack_start(GTK_BOX(account_block), info_box, FALSE, FALSE, 0);

    GtkWidget *username_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(username_field), "settings_fields");
    g_signal_connect(G_OBJECT(username_field), "insert-text", G_CALLBACK(all_input_event), NULL);
    g_signal_connect(G_OBJECT(username_field), "changed", G_CALLBACK(username_field_change_event), NULL);
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_field), "Username");
    gtk_entry_set_max_length(GTK_ENTRY(username_field), MAX_USERNAME);
    gtk_entry_set_text(GTK_ENTRY(username_field), t_account.username);
    gtk_box_pack_start(GTK_BOX(info_box), username_field, TRUE, TRUE, 10);

    GtkWidget *firstname_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(firstname_field), "settings_fields");
    g_signal_connect(G_OBJECT(firstname_field), "insert-text", G_CALLBACK(firstname_input_event), NULL);
    g_signal_connect(G_OBJECT(firstname_field), "changed", G_CALLBACK(firstname_field_change_event), NULL);
    gtk_entry_set_placeholder_text(GTK_ENTRY(firstname_field), "Name");
    gtk_entry_set_max_length(GTK_ENTRY(firstname_field), MAX_NAME);
    gtk_entry_set_text(GTK_ENTRY(firstname_field), t_account.name);
    gtk_box_pack_start(GTK_BOX(info_box), firstname_field, TRUE, TRUE, 10);

    GtkWidget *code_field = gtk_entry_new();
    gtk_entry_set_input_purpose(GTK_ENTRY(code_field), GTK_INPUT_PURPOSE_DIGITS);
    gtk_widget_set_name(GTK_WIDGET(code_field), "settings_fields");
    g_signal_connect(G_OBJECT(code_field), "insert-text", G_CALLBACK(code_input_event), NULL);
    g_signal_connect(G_OBJECT(code_field), "changed", G_CALLBACK(code_field_change_event), NULL);
    gtk_entry_set_placeholder_text(GTK_ENTRY(code_field), "Trainer code");
    gtk_entry_set_max_length(GTK_ENTRY(code_field), MAX_CODE);
    gtk_entry_set_text(GTK_ENTRY(code_field), t_account.code);
    gtk_box_pack_start(GTK_BOX(info_box), code_field, TRUE, TRUE, 10);

    GtkWidget *password_field = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_field), FALSE);
    g_signal_connect(G_OBJECT(password_field), "insert-text", G_CALLBACK(all_input_event), NULL);
    g_signal_connect(G_OBJECT(password_field), "changed", G_CALLBACK(pass_field_change_event), NULL);
    gtk_widget_set_name(GTK_WIDGET(password_field), "settings_fields");
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_field), "Password");
    gtk_entry_set_max_length(GTK_ENTRY(password_field), MAX_PASS);
    gtk_box_pack_start(GTK_BOX(info_box), password_field, TRUE, TRUE, 10);

    GtkWidget *repassword_field = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(repassword_field), FALSE);
    g_signal_connect(G_OBJECT(repassword_field), "insert-text", G_CALLBACK(all_input_event), NULL);
    g_signal_connect(G_OBJECT(repassword_field), "changed", G_CALLBACK(repass_field_change_event), NULL);
    gtk_widget_set_name(GTK_WIDGET(repassword_field), "settings_fields");
    gtk_entry_set_placeholder_text(GTK_ENTRY(repassword_field), "Repeat password");
    gtk_entry_set_max_length(GTK_ENTRY(repassword_field), MAX_PASS);
    gtk_box_pack_start(GTK_BOX(info_box), repassword_field, TRUE, TRUE, 10);

    GtkWidget *apply_butt = gtk_button_new_with_label("Apply");
    gtk_widget_set_name(GTK_WIDGET(apply_butt), "apply_button");
    gtk_button_set_relief(GTK_BUTTON(apply_butt), GTK_RELIEF_NONE);
    gtk_widget_set_size_request(GTK_WIDGET(apply_butt), 100, 10);
    gtk_box_pack_start(GTK_BOX(info_box), apply_butt, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(apply_butt), "clicked", G_CALLBACK(apply_butt_click), NULL);

    g_signal_connect(G_OBJECT(exit_button), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(exit_button), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(exit_button), "button_press_event", G_CALLBACK(exit_button_click), NULL);

    g_signal_connect(G_OBJECT(add_button), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(add_button), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(add_button), "button_press_event", G_CALLBACK(add_button_click), NULL);

    g_signal_connect(G_OBJECT(gallery_button), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(gallery_button), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(gallery_button), "button_press_event", G_CALLBACK(gallery_button_click), main);
}

static void build_teams_menu(GtkWidget *menu_block)
{
    GtkWidget *title2 = gtk_label_new("SELECT TEAM");
    gtk_widget_set_name(GTK_WIDGET(title2), "title2");                  // Имя
    gtk_widget_set_halign(title2, GTK_ALIGN_START);                     // Позиция текста
    gtk_box_pack_start(GTK_BOX(menu_block), title2, FALSE, FALSE, 0);
    //--//
    GtkWidget *teams_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(teams_block), "teams_block");
    gtk_box_pack_start(GTK_BOX(menu_block), teams_block, FALSE, FALSE, 0);
    //--//
    GtkWidget *team_mystic = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(team_mystic), "mystic");
    gtk_widget_set_size_request(GTK_WIDGET(team_mystic), TEAM_W, TEAM_H);
    gtk_box_pack_start(GTK_BOX(teams_block), team_mystic, TRUE, FALSE, 0);
    tooltip("Choose Mystic", team_mystic);
    GtkWidget *team_instinct = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(team_instinct), "instinct");
    gtk_widget_set_size_request(GTK_WIDGET(team_instinct), TEAM_W, TEAM_H);
    gtk_box_pack_start(GTK_BOX(teams_block), team_instinct, TRUE, FALSE, 0);
    tooltip("Choose Instinct", team_instinct);
    GtkWidget *team_valor = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(team_valor), "valor");
    gtk_widget_set_size_request(GTK_WIDGET(team_valor), TEAM_W, TEAM_H);
    gtk_box_pack_start(GTK_BOX(teams_block), team_valor, TRUE, FALSE, 0);
    tooltip("Choose Valor", team_valor);

    if(t_account.team == 1)
        gtk_widget_set_state_flags(GTK_WIDGET(team_mystic), GTK_STATE_FLAG_LINK, TRUE);
    else if(t_account.team == 2)
        gtk_widget_set_state_flags(GTK_WIDGET(team_instinct), GTK_STATE_FLAG_LINK, TRUE);
    else if(t_account.team == 3)
        gtk_widget_set_state_flags(GTK_WIDGET(team_valor), GTK_STATE_FLAG_LINK, TRUE);

    g_signal_connect(G_OBJECT(team_mystic), "enter-notify-event",G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(team_mystic), "leave-notify-event",G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(team_mystic), "button_press_event",G_CALLBACK(team_mystic_click), teams_block);

    g_signal_connect(G_OBJECT(team_instinct), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(team_instinct), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(team_instinct), "button_press_event", G_CALLBACK(team_instinct_click), teams_block);

    g_signal_connect(G_OBJECT(team_valor), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(team_valor), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(team_valor), "button_press_event", G_CALLBACK(team_valor_click), teams_block);
}

static void build_appearance_menu(GtkWidget *menu_block)
{
    GtkWidget *title4 = gtk_label_new("CHANGE APPEARANCE");
    gtk_widget_set_name(GTK_WIDGET(title4), "title4");                // Имя
    gtk_widget_set_halign(title4, GTK_ALIGN_START);                     // Позиция текста
    gtk_box_pack_start(GTK_BOX(menu_block), title4, FALSE, FALSE, 0);
    //--//
    GtkWidget *appearance_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(appearance_block), "appearance_block");
    gtk_box_pack_start(GTK_BOX(menu_block), appearance_block, FALSE, FALSE, 0);

    GtkWidget *title5 = gtk_label_new("CHANGE THEME");
    gtk_widget_set_name(GTK_WIDGET(title5), "title5");                // Имя
    gtk_widget_set_halign(title5, GTK_ALIGN_START);                   // Позиция текста
    gtk_widget_set_halign(GTK_WIDGET(title5), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(appearance_block), title5, FALSE, FALSE, 0);
    //--//
    GtkWidget *appearance_menu = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(appearance_menu), "chat_bgs_box");
    gtk_box_pack_start(GTK_BOX(appearance_block), appearance_menu, FALSE, FALSE, 0);

    GtkWidget *theme_light = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(theme_light), "theme_bgs");
    gtk_widget_set_size_request(GTK_WIDGET(theme_light), 260, 50);
    GtkWidget *light_label = gtk_label_new("LIGHT");
    gtk_widget_set_name(GTK_WIDGET(light_label), "theme_label");
    gtk_widget_set_halign(GTK_WIDGET(light_label), GTK_ALIGN_CENTER);
    gtk_container_add(GTK_CONTAINER(theme_light), light_label);
    gtk_box_pack_start(GTK_BOX(appearance_menu), theme_light, TRUE, FALSE, 0);

    GtkWidget *theme_default = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(theme_default), "theme_bgs");
    gtk_widget_set_size_request(GTK_WIDGET(theme_default), 260, 50);
    GtkWidget *default_label = gtk_label_new("DEFAULT");
    gtk_widget_set_name(GTK_WIDGET(default_label), "theme_label");
    gtk_widget_set_halign(GTK_WIDGET(default_label), GTK_ALIGN_CENTER);
    gtk_container_add(GTK_CONTAINER(theme_default), default_label);
    gtk_box_pack_start(GTK_BOX(appearance_menu), theme_default, TRUE, FALSE, 0);

    GtkWidget *theme_dark = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(theme_dark), "theme_bgs");
    gtk_widget_set_size_request(GTK_WIDGET(theme_dark), 260, 50);
    GtkWidget *dark_label = gtk_label_new("DARK");
    gtk_widget_set_name(GTK_WIDGET(dark_label), "theme_label");
    gtk_widget_set_halign(GTK_WIDGET(dark_label), GTK_ALIGN_CENTER);
    gtk_container_add(GTK_CONTAINER(theme_dark ), dark_label);
    gtk_box_pack_start(GTK_BOX(appearance_menu), theme_dark, TRUE, FALSE, 0);

    if(t_account.theme == 1)
        gtk_widget_set_state_flags(GTK_WIDGET(theme_light), GTK_STATE_FLAG_LINK, TRUE);
    else if(t_account.theme == 2)
        gtk_widget_set_state_flags(GTK_WIDGET(theme_default), GTK_STATE_FLAG_LINK, TRUE);
    else if(t_account.theme == 3)
        gtk_widget_set_state_flags(GTK_WIDGET(theme_dark), GTK_STATE_FLAG_LINK, TRUE);

    g_signal_connect(G_OBJECT(theme_light), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(theme_light), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(theme_light), "button_press_event", G_CALLBACK(theme_light_click), appearance_menu);

    g_signal_connect(G_OBJECT(theme_default), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(theme_default), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(theme_default), "button_press_event", G_CALLBACK(theme_default_click), appearance_menu);

    g_signal_connect(G_OBJECT(theme_dark), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(theme_dark), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(theme_dark), "button_press_event", G_CALLBACK(theme_dark_click), appearance_menu);

    //

    GtkWidget *title3 = gtk_label_new("CUSTOMIZE CHAT");
    gtk_widget_set_name(GTK_WIDGET(title3), "title3");                // Имя
    gtk_widget_set_halign(title3, GTK_ALIGN_START);                     // Позиция текста
    gtk_widget_set_halign(GTK_WIDGET(title3), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(appearance_block), title3, FALSE, FALSE, 0);
    //--//
    GtkWidget *previews_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(previews_box), "chat_bgs_box");
    gtk_box_pack_start(GTK_BOX(appearance_block), previews_box, FALSE, FALSE, 0);
    GtkWidget *bg1 = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(bg1), "chat_bg1");
    gtk_widget_set_size_request(GTK_WIDGET(bg1), 200, 300);
    gtk_box_pack_start(GTK_BOX(previews_box), bg1, TRUE, FALSE, 0);
    GtkWidget *bg2 = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(bg2), "chat_bg2");
    gtk_widget_set_size_request(GTK_WIDGET(bg2), 200, 300);
    gtk_box_pack_start(GTK_BOX(previews_box), bg2, TRUE, FALSE, 0);
    GtkWidget *bg3 = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(bg3), "chat_bg3");
    gtk_widget_set_size_request(GTK_WIDGET(bg3), 200, 300);
    gtk_box_pack_start(GTK_BOX(previews_box), bg3, TRUE, FALSE, 0);
    GtkWidget *bg4 = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(bg4), "chat_bg4");
    gtk_widget_set_size_request(GTK_WIDGET(bg4), 200, 300);
    gtk_box_pack_start(GTK_BOX(previews_box), bg4, TRUE, FALSE, 0);

    if(t_account.background == 1)
        gtk_widget_set_state_flags(GTK_WIDGET(bg1), GTK_STATE_FLAG_LINK, TRUE);
    else if(t_account.background == 2)
        gtk_widget_set_state_flags(GTK_WIDGET(bg2), GTK_STATE_FLAG_LINK, TRUE);
    else if(t_account.background == 3)
        gtk_widget_set_state_flags(GTK_WIDGET(bg3), GTK_STATE_FLAG_LINK, TRUE);
    else if(t_account.background == 4)
        gtk_widget_set_state_flags(GTK_WIDGET(bg4), GTK_STATE_FLAG_LINK, TRUE);

    g_signal_connect(G_OBJECT(bg1), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(bg1), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(bg1), "button_press_event", G_CALLBACK(bg1_preview_click), previews_box);

    g_signal_connect(G_OBJECT(bg2), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(bg2), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(bg2), "button_press_event", G_CALLBACK(bg2_preview_click), previews_box);

    g_signal_connect(G_OBJECT(bg3), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(bg3), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(bg3), "button_press_event", G_CALLBACK(bg3_preview_click), previews_box);

    g_signal_connect(G_OBJECT(bg4), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(bg4), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(bg4), "button_press_event", G_CALLBACK(bg4_preview_click), previews_box);
}

static void build_about_info(GtkWidget *menu_block)
{
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    gtk_widget_set_name(GTK_WIDGET(box), "about_box");
    gtk_box_pack_start(GTK_BOX(menu_block), box, FALSE, FALSE, 0);

    GtkWidget *name = gtk_label_new(t_application.app);
    gtk_widget_set_name(GTK_WIDGET(name), "about_info");
    gtk_widget_set_halign(name, GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(box), name, FALSE, FALSE, 0);

    GtkWidget *user = gtk_label_new(t_application.user);
    gtk_widget_set_name(GTK_WIDGET(user), "about_info");
    gtk_widget_set_halign(user, GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(box), user, FALSE, FALSE, 0);
}

void build_settings_menu(GtkWidget **stgscreen)
{
    // Creating workspace
    //GtkAdjustment *vadjustment = gtk_adjustment_new(0, 0, CUR_WIDTH-LEFTBAR_W, 200, 200, CUR_HEIGHT);    // Параметры скролла
    t_screen.settings_scr = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_name(GTK_WIDGET(t_screen.settings_scr), "settings_scr");
    gtk_widget_set_size_request(GTK_WIDGET(t_screen.settings_scr), WINDOW_WIDTH-LEFTBAR_W, WINDOW_HEIGHT);
    gtk_fixed_put(GTK_FIXED(*stgscreen), t_screen.settings_scr, LEFTBAR_W, 0);
    GtkWidget *main = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(t_screen.settings_scr), main);
    gtk_widget_hide(gtk_scrolled_window_get_vscrollbar(GTK_SCROLLED_WINDOW(t_screen.settings_scr)));
    //--//--//
    GtkWidget *menu_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(menu_block), WINDOW_WIDTH-LEFTBAR_W, 0);
    gtk_widget_set_name(GTK_WIDGET(menu_block), "menu_block");
    gtk_fixed_put(GTK_FIXED(main),menu_block, 0, 0);
    //--//--//
    build_account_menu(menu_block, main);
    build_teams_menu(menu_block);
    build_appearance_menu(menu_block);
    build_about_info(menu_block);
}
