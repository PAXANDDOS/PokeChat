#include "../inc/client.h"

void *send_message() {
    char *text = strdup(msg_data.content_final);
    // Easter egg 1
    if (!strcmp(text, "pikachu") || !strcmp(text, "Pikachu")) {
        mx_strdel(&t_pokefact.pokemon_fact_audio);
        t_pokefact.pokemon_fact_audio = strdup("client/data/pokemon-audio/9.wav");
        play_audio(SOUND_POKEMON);
    }

    int chat_id = msg_data.chat_id;
    int sender_id = t_account.id;
    // printf("%s\n", text);
    cJSON *json = cJSON_CreateObject();
    cJSON *json_send_message = cJSON_CreateObject();
    cJSON_AddNumberToObject(json_send_message, "sender_id", sender_id);
    cJSON_AddNumberToObject(json_send_message, "chat_id", chat_id);
    cJSON_AddStringToObject(json_send_message, "text", text);
    cJSON_AddStringToObject(json_send_message, "date", mx_str_getdate());
    cJSON_AddStringToObject(json_send_message, "time", mx_str_gettime());
    cJSON_AddItemToObject(json, "send_message", json_send_message);
    char *json_string = cJSON_PrintUnformatted(json);
    // printf("%s\n", json_string);
    char *result = NULL;
    ssl_client(json_string, &result);
    cJSON *response = cJSON_Parse(result);
    if (!cJSON_IsNull(response)) {
        upd_data.suspend = true;
        for (int i = 0; i < upd_data.count; i++)
            if (upd_data.chats_id[i] == chat_id) {
                upd_data.messages_id[i] = cJSON_GetNumberValue(cJSON_GetObjectItem(response, "message_id"));
                break;
            }
        upd_data.suspend = false;
    }
    mx_strdel(&result);
    mx_strdel(&json_string);
    mx_strdel(&msg_data.content_final);
    mx_strdel(&text);
    cJSON_Delete(json);
    cJSON_Delete(response);
    play_audio(SOUND_HIGH_POP);
    return NULL;
}

void *send_sticker() {
    int chat_id = sticker_data.chat_id;
    int sender_id = t_account.id;
    cJSON *json = cJSON_CreateObject();
    cJSON *json_send_sticker = cJSON_CreateObject();
    cJSON_AddNumberToObject(json_send_sticker, "sender_id", sender_id);
    cJSON_AddNumberToObject(json_send_sticker, "chat_id", chat_id);
    cJSON_AddNumberToObject(json_send_sticker, "sticker_id", sticker_data.sticker_id);
    cJSON_AddStringToObject(json_send_sticker, "date", mx_str_getdate());
    cJSON_AddStringToObject(json_send_sticker, "time", mx_str_gettime());
    cJSON_AddItemToObject(json, "send_sticker", json_send_sticker);
    char *json_string = cJSON_PrintUnformatted(json);
    // printf("%s\n", json_string);
    char *result = NULL;
    ssl_client(json_string, &result);
    cJSON *response = cJSON_Parse(result);
    if (!cJSON_IsNull(response)) {
        upd_data.suspend = true;
        for (int i = 0; i < upd_data.count; i++)
            if (upd_data.chats_id[i] == chat_id) {
                upd_data.messages_id[i] = cJSON_GetNumberValue(cJSON_GetObjectItem(response, "message_id"));
                break;
            }
        upd_data.suspend = false;
    }
    mx_strdel(&result);
    mx_strdel(&json_string);
    cJSON_Delete(json);
    cJSON_Delete(response);
    play_audio(SOUND_HIGH_POP);
    return NULL;
}


static int get_buff_size(char *filepath) {
    FILE *f = fopen(filepath, "rb");
    int bytes;
    for(bytes = 0; getc(f) != EOF; ++bytes);
    fclose(f);
    return bytes;
}

static BIO *base64_encrypt(char *data, int dlen) {
    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *fo = BIO_new_file(mx_strjoin(TEMP_DIR, "b64"), "w");
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    BIO_push(b64, fo);
    BIO_write(b64, data, dlen);
    BIO_flush(b64);
    return b64;
}

// static unsigned char *base64_decrypt(u_char *input, int length) {
//     const int pl = length * 3 / 4;
//     u_char *output = malloc(pl + 1);
//     EVP_DecodeBlock(output, (const u_char*)input, length);
//     return output;
// }

void *send_photo() {
    int chat_id = photo_data.chat_id;
    int sender_id = t_account.id;
    char *filepath = photo_data.photo_path;

    int img_size = get_buff_size(filepath);
    char *bitmap = malloc(img_size);
    BIO *file_bio = BIO_new_file(filepath, "rb");
    BIO_read(file_bio, bitmap, img_size);

    // BIO *output = BIO_new_fp(stdout, BIO_NOCLOSE);
    BIO *b64 = base64_encrypt(bitmap, img_size);
    BIO_free_all(b64);
    BIO_free_all(file_bio);
    mx_strdel(&bitmap);

    int expoint = 0;
    char extension[6];
    for (int i = strlen(filepath) - 1; i >= 0; i--)
        if (filepath[i] == '.') {
            expoint = i;
            break;
        }
    int i = 0;
    for (int j = expoint; j < (int)strlen(filepath); j++)
        extension[i++] = filepath[j];
    extension[i] = 0;
    mx_strdel(&filepath);

    u_char *result = (u_char*)mx_file_to_str(mx_strjoin(TEMP_DIR, "b64"));

    cJSON *json = cJSON_CreateObject();
    cJSON *json_send_bitmap = cJSON_CreateObject();
    cJSON_AddStringToObject(json_send_bitmap, "bitmap", (const char*)result);
    cJSON_AddStringToObject(json_send_bitmap, "extension", extension);
    cJSON_AddItemToObject(json, "send_bitmap", json_send_bitmap);
    char *json_string = cJSON_PrintUnformatted(json);
    if (result)
        free(result);
    char *reply = NULL;
    ssl_client_alloc_len(json_string, &reply);
    cJSON_Delete(json);

    cJSON *response = cJSON_Parse(reply);
    // printf("%s\n", reply);
    int photo_id = cJSON_GetNumberValue(cJSON_GetObjectItem(response, "photo_id"));
    cJSON_Delete(response);
    mx_strdel(&reply);
    json_string = NULL;
    reply = NULL;
    response = NULL;

    cJSON *json_photo = cJSON_CreateObject();
    cJSON *json_send_photo = cJSON_CreateObject();
    cJSON_AddNumberToObject(json_send_photo, "sender_id", sender_id);
    cJSON_AddNumberToObject(json_send_photo, "chat_id", chat_id);
    cJSON_AddNumberToObject(json_send_photo, "photo_id", photo_id);
    cJSON_AddStringToObject(json_send_photo, "date", mx_str_getdate());
    cJSON_AddStringToObject(json_send_photo, "time", mx_str_gettime());
    cJSON_AddItemToObject(json_photo, "send_photo", json_send_photo);
    json_string = cJSON_PrintUnformatted(json_photo);
    ssl_client(json_string, &reply);
    response = cJSON_Parse(reply);
    if (!cJSON_IsNull(response)) {
        upd_data.suspend = true;
        for (int i = 0; i < upd_data.count; i++)
            if (upd_data.chats_id[i] == chat_id) {
                upd_data.messages_id[i] = cJSON_GetNumberValue(cJSON_GetObjectItem(response, "message_id"));
                break;
            }
        upd_data.suspend = false;
    }
    mx_strdel(&reply);
    mx_strdel(&json_string);
    cJSON_Delete(json_photo);
    cJSON_Delete(response);
    play_audio(SOUND_HIGH_POP);
    return NULL;
}
