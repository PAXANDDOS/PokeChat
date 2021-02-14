#include "../inc/client.h"

void tooltip(char *str, void *data) {
    gtk_widget_set_tooltip_text(data, str);
}

void free_uchat() {
    // free(tm_struct);        // Freeing time&date struct
    mx_strdel(&t_account.username);
    mx_strdel(&t_account.password);
    mx_strdel(&msg_data.date_prev);
    mx_strdel(&msg_data.date);
    mx_strdel(&msg_data.time);
    mx_strdel(&msg_data.username);
}

static void before_exit_jobs() {
    upd_data.suspend = true;// Forbid to getting updates

    cJSON *json_offline = cJSON_CreateObject();
    cJSON *json_user_id = cJSON_CreateObject();
    cJSON_AddNumberToObject(json_user_id, "user_id", t_account.id);
    cJSON_AddItemToObject(json_offline, "update_user_offline", json_user_id);
    char *json_offline_string = cJSON_PrintUnformatted(json_offline);
    // printf("%s\n", json_offline_string);
    char *result = NULL;
    ssl_client(json_offline_string, &result);
    mx_strdel(&json_offline_string);
    mx_strdel(&result);
    cJSON_Delete(json_offline);

    // g_object_unref(t_application.icon);   // Destroying icon
    Mix_CloseAudio();       // Closing SDL Mixer
    SDL_Quit();             // Closing SDL

    free_uchat();
    unsetenv("UCHAT_HOST");
    unsetenv("UCHAT_PORT");
}

static void init_server_connection(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage : ./uchat [ip] [port]\n");
        exit(EXIT_FAILURE);
    }
    setenv("UCHAT_HOST", argv[1], true);
    setenv("UCHAT_PORT", argv[2], true);
}

int main(int argc, char *argv[]) {
    init_server_connection(argc, argv);
    gtk_init(&argc, &argv);                             // Initializing GTK
    SDL_Init(SDL_INIT_AUDIO);                           // Initializing SDL
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);  // Initializing SDL Mixer
    srand(time(NULL));

    t_application.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);                                 // Creating main window
    gtk_window_set_title(GTK_WINDOW(t_application.window), "PokeChat");                         // Setting window title
    gtk_window_set_default_size(GTK_WINDOW(t_application.window), WINDOW_WIDTH, WINDOW_HEIGHT); // Setting window size
    gtk_window_set_position(GTK_WINDOW(t_application.window), GTK_WIN_POS_CENTER);              // Setting window start position
    gtk_window_set_resizable(GTK_WINDOW(t_application.window), FALSE);                          // Disabling window resize

    gtk_window_set_icon_from_file(GTK_WINDOW(t_application.window), "client/data/images/logo.png", NULL);// Setting icon to window
    gtk_window_set_icon_name(GTK_WINDOW(t_application.window), "PokeChat");

    load_providers();   // Loading chosen CSS providers
    GtkWidget *main_area = gtk_fixed_new();                                         // Creating main area
    gtk_container_add(GTK_CONTAINER(t_application.window), main_area);              // Applying main area to current window
    gtk_widget_set_size_request(GTK_WIDGET(main_area), WINDOW_WIDTH, WINDOW_HEIGHT);// Setting size

    t_application.auth = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(main_area), t_application.auth, 0, 0);
    gtk_widget_set_size_request(GTK_WIDGET(t_application.auth), WINDOW_WIDTH, WINDOW_HEIGHT);

    t_application.messanger = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(main_area), t_application.messanger, 0, 0);
    gtk_widget_set_size_request(GTK_WIDGET(t_application.messanger), WINDOW_WIDTH, WINDOW_HEIGHT);

    test_autofill();    // Заполнение данных аккаунта // Оставь это
    build_authorization(&t_application.auth); // Закомментируй это и разкомментируй все ниже, чтобы получить доступ к непосредственно к чату
    msg_data.date_prev = strdup("");
    msg_data.date = NULL;
    msg_data.chat_id = 0;
    upd_data.suspend = false;
    upd_data.busy = false;
    upd_data.filling_init = false;

    gtk_widget_show_all(t_application.window);          // Showing window

    g_signal_connect(t_application.window, "destroy", G_CALLBACK(gtk_main_quit), NULL); // When window is closed - exit program

    // comment 2 lines below if wanna run without getting updates from server
    pthread_t thread = NULL;
    pthread_create(&thread, NULL, updater, NULL);

    gtk_main();             // Looping program
    before_exit_jobs();

    return 0;
}
