#include "../inc/client.h"

// пока не юзается, я сделал, а потом не понял зачем я это сделал :-/ Спать хочу -_-
// static void add_new_int(int **arr, int new_int, int count) {
//     int *temp = malloc(sizeof(int) * count);
//     for (int i = 0; i < count; i++)
//         temp[i] = *arr[i];
//     free(*arr);
//     *arr = malloc(sizeof(int) * (count + 1));
//     for (int i = 0; i < count; i++)
//         *arr[i] = temp[i];
//     *arr[count] = new_int;
//     free(temp);
// }

// Тут будет генерация новых сообщений в виде новых виджетов
static void generate_new_message(int user_id, char *text, char *sticker, char *photo) {
    printf("User: %d\nText: %s\nSticker: %s\nPhoto: %s\n\n", user_id, text, sticker, photo);
}

void *updater() {
    upd_data.chats_id = NULL;
    upd_data.messages_id = NULL;
    upd_data.count = 0;
    while (true) {
        if (upd_data.count > 0) {
            for (int i = 0; i < upd_data.count; i++) {
                cJSON *update_request = cJSON_CreateObject();
                cJSON *updated_chat = cJSON_CreateObject();

                cJSON_AddNumberToObject(updated_chat, "sender_id", t_account.id);
                cJSON_AddNumberToObject(updated_chat, "chat_id", upd_data.chats_id[i]);
                cJSON_AddNumberToObject(updated_chat, "message_id", upd_data.messages_id[i]);
                cJSON_AddItemToObject(update_request, "update_message_id", updated_chat);
                char *request_string = cJSON_Print(update_request);
                cJSON_Delete(update_request);
                char *result = NULL;
                ssl_client(request_string, &result);
                mx_strdel(&request_string);

                cJSON *response = cJSON_Parse(result);
                mx_strdel(&result);
                if (!cJSON_IsNull(response)) {
                    const cJSON *message_item = NULL;
                    cJSON_ArrayForEach(message_item, response) {
                        upd_data.messages_id[i] = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(message_item, "message_id"));
                        int user_id = cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(message_item, "user_id"));
                        cJSON *json_text = cJSON_GetObjectItemCaseSensitive(message_item, "text");
                        cJSON *json_sticker = cJSON_GetObjectItemCaseSensitive(message_item, "sticker");
                        cJSON *json_photo = cJSON_GetObjectItemCaseSensitive(message_item, "photo");
                        char *text = NULL, *sticker = NULL, *photo = NULL;
                        if (json_text)
                            text = cJSON_GetStringValue(json_text);
                        if (json_sticker)
                            sticker = cJSON_GetStringValue(json_sticker);
                        if (json_photo)
                            photo = cJSON_GetStringValue(json_photo);
                        generate_new_message(user_id, text, sticker, photo);
                        // mx_strdel(&text);
                        // mx_strdel(&sticker);
                        // mx_strdel(&photo);
                    }
                    // cJSON_Delete(message_item);
                }
                cJSON_Delete(response);
                usleep(1000);  // 1 millisecond
            }
        }
        else {
            cJSON *get_chats_count = cJSON_CreateObject();
            cJSON *json_sender = cJSON_CreateObject();
            cJSON_AddNumberToObject(json_sender, "sender_id", t_account.id);
            cJSON_AddItemToObject(get_chats_count, "get_chats_count", json_sender);
            char *request = cJSON_Print(get_chats_count);
            char *result = NULL;
            ssl_client(request, &result);
            cJSON *response = cJSON_Parse(result);
            cJSON *chats_count = cJSON_GetObjectItem(response, "chats_count");
            int count = cJSON_GetNumberValue(chats_count);
            cJSON_Delete(get_chats_count);
            cJSON_Delete(response);
            mx_strdel(&request);
            mx_strdel(&result);

            if (count > 0) {
                // implement all below
                if (upd_data.chats_id) free(upd_data.chats_id);
                if (upd_data.messages_id) free(upd_data.messages_id);
                upd_data.chats_id = malloc(sizeof(int) * count);
                upd_data.messages_id = malloc(sizeof(int) * count);
                upd_data.count = count;
                cJSON *get_chats = cJSON_CreateObject();
                json_sender = cJSON_CreateObject();
                cJSON_AddNumberToObject(json_sender, "sender_id", t_account.id);
                cJSON_AddItemToObject(get_chats, "get_chats", json_sender);
                request = cJSON_Print(get_chats);
                ssl_client(request, &result);
                response = cJSON_Parse(result);
                const cJSON *chat_item = NULL;
                int i = 0;
                cJSON_ArrayForEach(chat_item, response) {
                    upd_data.chats_id[i] = cJSON_GetNumberValue(cJSON_GetArrayItem(response, i));
                    upd_data.messages_id[i] = 0;
                    i++;
                }
                cJSON_Delete(get_chats);
                // cJSON_Delete(chat_item);
                cJSON_Delete(response);
                mx_strdel(&request);
                mx_strdel(&result);
            }
        }
        usleep(5 * 1000000);  // 5 second
    }
    return NULL;
}
