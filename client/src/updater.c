#include "../inc/client.h"

static void generate_notification(char *text, bool sticker, bool photo) {
    gchar *body = strdup(msg_data.username);
    body = mx_strrejoin(body, ": ");
    if (text)
        body = mx_strrejoin(body, text);
    else if (sticker)
        body = mx_strrejoin(body, "Sticker");
    else if (photo)
        body = mx_strrejoin(body, "Photo");
    char *avatar = get_avatar_by_number(msg_data.avatar);
    #if !defined (__APPLE__)
        GNotification *notify = g_notification_new("New message");
        g_notification_set_body(notify, body);
        GFile *file = g_file_new_for_path(avatar);
        GIcon *icon = g_file_icon_new(file);
        g_notification_set_icon(notify, G_ICON(icon));
        g_notification_set_priority(notify, G_NOTIFICATION_PRIORITY_HIGH);
        g_application_send_notification(t_application.application, NULL, notify);
        g_object_unref(icon);
        g_object_unref(file);
        g_object_unref(notify);
    #else
        pid_t pid = fork();
        if (pid == 0) {
            free_uchat();
            execl("local_lib/lib/notifier/Contents/MacOS/notifier", " ",
                  "-title", "PokeChat", "-subtitle", "New message", "-sound", "default",
                  "-message", body, "-activate", t_application.id,
                  "-contentImage", avatar, "-appIcon", "client/data/images/logo.png", NULL);
            exit(EXIT_SUCCESS);
            // Тут происходят утечки памяти переменных avatar, body; Этого избежать невозможно
        }
    #endif
    mx_strdel(&avatar);
    mx_strdel(&body);
}

static void generate_new_message(int user_id, int avatar, char *username, char *time, char *date, char *text, int sticker, char *photo_path) {
    // printf("User: %d\nText: %s\nSticker: %d\nPhoto: %s\n\n", user_id, text, sticker, photo_path);
    if (msg_data.date) {
        mx_strdel(&msg_data.date_prev);
        msg_data.date_prev = strdup(msg_data.date);
    }
    msg_data.avatar = avatar;
    mx_strdel(&msg_data.username);
    msg_data.username = strdup(username);
    mx_strdel(&msg_data.time);
    msg_data.time = strdup(time);
    mx_strdel(&msg_data.date);
    msg_data.date = strdup(date);
    if (user_id == t_account.id) {
        if (text) {
            msg_data.content = text;
            msg_data.content_final = strdup(msg_data.content);
            new_outgoing_message(t_msg.chat_screen);
        }
        else if (sticker)
            new_outgoing_sticker(t_msg.chat_screen, sticker);
        else if (photo_path)
            new_outgoing_embedded(t_msg.chat_screen, photo_path);
    }
    else {
        if (text) {
            msg_data.content = text;
            msg_data.content_final = strdup(msg_data.content);
            new_incoming_message(t_msg.chat_screen);
        }
        else if (sticker)
            new_incoming_sticker(t_msg.chat_screen, sticker);
        else if (photo_path)
            new_incoming_embedded(t_msg.chat_screen, photo_path);
        if (!upd_data.filling_init) {
            play_audio(SOUND_LOW_POP);
            generate_notification(text, sticker ? 1 : 0, photo_path ? 1 : 0);
        }
    }
}

static char *get_bitmap(int photo_id) {
    char *count_str = mx_itoa(photo_id);
    char *filepath = mx_strjoin(MEDIA_DIR, count_str);
    char *filepath1 = mx_strjoin(filepath, ".png");
    char *filepath2 = mx_strjoin(filepath, ".jpg");
    char *filepath3 = mx_strjoin(filepath, ".jpeg");

    bool e1 = false, e2 = false, e3 = false;
    if(!access(filepath1, F_OK))
       e1 = true;
    if(!access(filepath2, F_OK))
       e2 = true;
    if(!access(filepath3, F_OK))
       e3 = true;
    mx_strdel(&filepath1);
    mx_strdel(&filepath2);
    mx_strdel(&filepath3);
    mx_strdel(&count_str);
    if (e1) {
        filepath = mx_strrejoin(filepath, ".png");
        return filepath;
    }
    if (e2) {
        filepath = mx_strrejoin(filepath, ".jpg");
        return filepath;
    }
    if (e3) {
        filepath = mx_strrejoin(filepath, ".jpeg");
        return filepath;
    }
    cJSON *json = cJSON_CreateObject();
    cJSON *json_get_bitmap = cJSON_CreateObject();
    cJSON_AddNumberToObject(json_get_bitmap, "photo_id", photo_id);
    cJSON_AddItemToObject(json, "get_bitmap", json_get_bitmap);
    char *json_string = cJSON_PrintUnformatted(json);
    char *result = NULL;
    ssl_client(json_string, &result);
    mx_strdel(&json_string);
    cJSON_Delete(json);
    cJSON *response = cJSON_Parse(result);
    if (cJSON_IsNull(response)) {
        cJSON_Delete(response);
        mx_strdel(&result);
        mx_strdel(&filepath);
        filepath = strdup("client/data/images/invalid-image.png");
        return filepath;
    }
    char *bitmap64 = cJSON_GetStringValue(cJSON_GetObjectItem(response, "bitmap"));
    char *extension = cJSON_GetStringValue(cJSON_GetObjectItem(response, "extension"));
    filepath = mx_strrejoin(filepath, extension);
    int length = strlen(bitmap64);
    const int img_size = length * 3 / 4;
    u_char *bitmap = malloc(img_size + 1);
    // printf("len: %d\n", img_size);
    EVP_DecodeBlock(bitmap, (const u_char*)bitmap64, length);
    cJSON_Delete(response);
    mx_strdel(&result);

    FILE *file = fopen(filepath, "wb");
    fwrite(bitmap, img_size, 1, file);
    fclose(file);
    if (bitmap)
        free(bitmap);
    return filepath;
}

void *updater() {
    upd_data.chats_id = NULL;
    upd_data.messages_id = NULL;
    upd_data.count = 0;
    upd_data.control_sum = 0;
    while (true) {
        if (!upd_data.suspend) {
            if (upd_data.count > 0) {
                for (int i = 0; i < upd_data.count; i++) {
                    if (upd_data.chats_id[i] != msg_data.chat_id)
                        continue;
                    cJSON *update_request = cJSON_CreateObject();
                    cJSON *updated_chat = cJSON_CreateObject();

                    cJSON_AddNumberToObject(updated_chat, "sender_id", t_account.id);
                    cJSON_AddNumberToObject(updated_chat, "chat_id", upd_data.chats_id[i]);
                    cJSON_AddNumberToObject(updated_chat, "message_id", upd_data.messages_id[i]);
                    cJSON_AddItemToObject(update_request, "update_messages_rest", updated_chat);
                    char *request_string = cJSON_PrintUnformatted(update_request);
                    cJSON_Delete(update_request);
                    char *result = NULL;
                    ssl_client(request_string, &result);
                    mx_strdel(&request_string);

                    cJSON *response = cJSON_Parse(result);
                    mx_strdel(&result);
                    if (!cJSON_IsNull(response)) {
                        upd_data.busy = true;
                        if (upd_data.messages_id[i] == 0)
                            upd_data.filling_init = true;
                        int messages_left = cJSON_GetNumberValue(cJSON_GetObjectItem(response, "messages_rest"));

                        for (int j = 0; j < messages_left; j++) {
                            update_request = cJSON_CreateObject();
                            updated_chat = cJSON_CreateObject();
                            cJSON_AddNumberToObject(updated_chat, "sender_id", t_account.id);
                            cJSON_AddNumberToObject(updated_chat, "chat_id", upd_data.chats_id[i]);
                            cJSON_AddNumberToObject(updated_chat, "message_id", upd_data.messages_id[i]);
                            cJSON_AddItemToObject(update_request, "update_message_id", updated_chat);
                            char *request_string = cJSON_PrintUnformatted(update_request);
                            cJSON_Delete(update_request);
                            char *result = NULL;
                            ssl_client(request_string, &result);
                            mx_strdel(&request_string);
                            cJSON *mes_response = cJSON_Parse(result);
                            mx_strdel(&result);

                            if (!cJSON_IsNull(mes_response)) {
                                upd_data.messages_id[i] = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(mes_response, "message_id"));
                                int user_id = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(mes_response, "user_id"));

                                cJSON *user_request = cJSON_CreateObject();
                                cJSON *get_user = cJSON_CreateObject();
                                cJSON_AddNumberToObject(get_user, "user_id", user_id);
                                cJSON_AddItemToObject(user_request, "get_user", get_user);
                                request_string = cJSON_PrintUnformatted(user_request);
                                cJSON_Delete(user_request);
                                ssl_client(request_string, &result);
                                mx_strdel(&request_string);
                                cJSON *user_response = cJSON_Parse(result);
                                mx_strdel(&result);
                                int avatar = cJSON_GetNumberValue(cJSON_GetObjectItem(user_response, "avatar"));
                                char *username = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(user_response, "username")));
                                cJSON_Delete(user_response);

                                char *time = cJSON_GetStringValue(cJSON_GetObjectItem(mes_response, "time"));
                                char *date = cJSON_GetStringValue(cJSON_GetObjectItem(mes_response, "date"));
                                cJSON *json_text = cJSON_GetObjectItemCaseSensitive(mes_response, "text");
                                cJSON *json_sticker = cJSON_GetObjectItemCaseSensitive(mes_response, "sticker_id");
                                cJSON *json_photo = cJSON_GetObjectItemCaseSensitive(mes_response, "photo_id");
                                char *text = NULL, *photo_path = NULL;
                                int sticker_id = 0, photo_id = 0;
                                if (!cJSON_IsNull(json_text))
                                    text = cJSON_GetStringValue(json_text);
                                if (!cJSON_IsNull(json_sticker))
                                    sticker_id = cJSON_GetNumberValue(json_sticker);
                                if (!cJSON_IsNull(json_photo)) {
                                    photo_id = cJSON_GetNumberValue(json_photo);
                                    photo_path = get_bitmap(photo_id);
                                }
                                generate_new_message(user_id, avatar, username, time, date, text, sticker_id, photo_path);
                                mx_strdel(&username);
                                mx_strdel(&photo_path);
                                cJSON_Delete(mes_response);
                                usleep(1000);
                            }
                        }
                        upd_data.busy = false;
                        upd_data.filling_init = false;
                    }
                    cJSON_Delete(response);
                    usleep(1000);  // 1 millisecond
                }
            }
            cJSON *get_chats_count = cJSON_CreateObject();
            cJSON *json_sender = cJSON_CreateObject();
            cJSON_AddNumberToObject(json_sender, "sender_id", t_account.id);
            cJSON_AddItemToObject(get_chats_count, "get_chats_count", json_sender);
            char *request = cJSON_PrintUnformatted(get_chats_count);
            char *result = NULL;
            ssl_client(request, &result);
            cJSON *response = cJSON_Parse(result);
            int count = cJSON_GetNumberValue(cJSON_GetObjectItem(response, "chats_count"));
            csum_t control_sum = cJSON_GetNumberValue(cJSON_GetObjectItem(response, "chats_sum"));
            cJSON_Delete(get_chats_count);
            cJSON_Delete(response);
            mx_strdel(&request);
            mx_strdel(&result);

            if (count > 0) {
                if (upd_data.count != count || upd_data.control_sum != control_sum) {
                    if (upd_data.chats_id) free(upd_data.chats_id);
                    if (upd_data.messages_id) free(upd_data.messages_id);
                    upd_data.chats_id = malloc(sizeof(int) * count);
                    upd_data.messages_id = malloc(sizeof(int) * count);
                    upd_data.count = count;
                    upd_data.control_sum = control_sum;
                    chat_clear_list(&chatlist);
                    gtk_container_forall(GTK_CONTAINER(t_msg.chatlist), (GtkCallback)gtk_widget_destroy, NULL);
                    cJSON *get_chats = cJSON_CreateObject();
                    json_sender = cJSON_CreateObject();
                    cJSON_AddNumberToObject(json_sender, "sender_id", t_account.id);
                    cJSON_AddItemToObject(get_chats, "get_chats", json_sender);
                    request = cJSON_PrintUnformatted(get_chats);
                    ssl_client(request, &result);
                    response = cJSON_Parse(result);
                    const cJSON *chat_item = NULL;
                    int i = 0;
                    cJSON_ArrayForEach(chat_item, response) {
                        upd_data.chats_id[i] = cJSON_GetNumberValue(cJSON_GetArrayItem(response, i));
                        upd_data.messages_id[i] = 0;

                        // Adding chat to chats list
                        t_chat_data *chat = malloc(sizeof(t_chat_data));
                        chat->user = malloc(sizeof(t_user));
                        chat->chat_id = upd_data.chats_id[i];;
                        get_chat(chat);
                        if (chat->user->id)
                            get_user(chat->user);
                        chat_push_back(&chatlist, chat);
                        free_user(chat->user);
                        mx_strdel(&chat->title);
                        free(chat);

                        display_new_chat();
                        i++;
                        usleep(10000);
                    }
                    cJSON_Delete(get_chats);
                    cJSON_Delete(response);
                    mx_strdel(&request);
                    mx_strdel(&result);
                }
            }
            usleep(0.5 /* <- seconds */ * 1000000);
        }
    }
    return NULL;
}
