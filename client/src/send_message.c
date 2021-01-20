#include "../inc/client.h"
#define TEMP_FOLDER "temp/"

static int get_buff_size(char *filepath) {
    FILE *f = fopen(filepath, "rb");
    int bytes;
    for(bytes = 0; getc(f) != EOF; ++bytes);
    fclose(f);
    return bytes;
}

static BIO *base64_encrypt(char *data, int dlen) {
    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *fo = BIO_new_file(mx_strjoin(TEMP_FOLDER, "b64"), "w");
    BIO_push(b64, fo);
    BIO_write(b64, data, dlen);
    BIO_flush(b64);
    return b64;
}

// static int calcDecodeLength(const char* b64input) { //Calculates the length of a decoded base64 string
//     int len = strlen(b64input);
//     int padding = 0;

//     if (b64input[len-1] == '=' && b64input[len-2] == '=') //last two chars are =
//         padding = 2;
//     else if (b64input[len-1] == '=') //last char is =
//         padding = 1;

//     return (int)len * 0.75 - padding;
// }

// static char *base64_decrypt(char* b64message) { //Decodes a base64 encoded string
//     BIO *bio, *b64;
//     int decodeLen = calcDecodeLength(b64message);
//     int len = 0;
//     char *buffer = malloc(decodeLen+1);
//     FILE* stream = fmemopen(b64message, strlen(b64message), "r");

//     b64 = BIO_new(BIO_f_base64());
//     bio = BIO_new_fp(stream, BIO_NOCLOSE);
//     bio = BIO_push(b64, bio);
//     BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Do not use newlines to flush buffer
//     len = BIO_read(bio, buffer, strlen(b64message));
//         //Can test here if len == decodeLen - if not, then return an error
//     buffer[len] = '\0';

//     BIO_free_all(bio);
//     fclose(stream);
//     printf("%s", buffer);
//     return buffer;
// }

void *send_message() {
    int chat_id = 1;
    int sender_id = t_account.id;
    char *text = msg_data.content_final;
    printf("%s\n", text);
    cJSON *json = cJSON_CreateObject();
    cJSON *json_send_message = cJSON_CreateObject();
    cJSON_AddNumberToObject(json_send_message, "sender_id", sender_id);
    cJSON_AddNumberToObject(json_send_message, "chat_id", chat_id);
    cJSON_AddStringToObject(json_send_message, "text", text);
    cJSON_AddStringToObject(json_send_message, "date", mx_str_getdate());
    cJSON_AddStringToObject(json_send_message, "time", mx_str_gettime());
    cJSON_AddItemToObject(json, "send_message", json_send_message);
    char *json_string = cJSON_PrintUnformatted(json);
    printf("%s\n", json_string);
    char *result = NULL;
    ssl_client(json_string, &result);
    cJSON *response = cJSON_Parse(result);
    if (!cJSON_IsNull(response))
        for (int i = 0; i < upd_data.count; i++)
            if (upd_data.chats_id[i] == chat_id) {
                upd_data.messages_id[i] = cJSON_GetNumberValue(cJSON_GetObjectItem(response, "message_id"));
                break;
            }
    mx_strdel(&result);
    mx_strdel(&json_string);
    mx_strdel(&msg_data.content_final);
    cJSON_Delete(json);
    cJSON_Delete(response);
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
    printf("%s\n", json_string);
    char *result = NULL;
    ssl_client(json_string, &result);
    cJSON *response = cJSON_Parse(result);
    if (!cJSON_IsNull(response))
        for (int i = 0; i < upd_data.count; i++)
            if (upd_data.chats_id[i] == chat_id) {
                upd_data.messages_id[i] = cJSON_GetNumberValue(cJSON_GetObjectItem(response, "message_id"));
                break;
            }
    mx_strdel(&result);
    mx_strdel(&json_string);
    cJSON_Delete(json);
    cJSON_Delete(response);
    return NULL;
}

void send_photo() {
    char *test_path = "client/data/images/logo.png";

    int img_size = get_buff_size(test_path);
    char *bitmap = malloc(img_size);
    BIO *file_bio = BIO_new_file(test_path, "rb");
    BIO_read(file_bio, bitmap, img_size);

    // BIO *output = BIO_new_fp(stdout, BIO_NOCLOSE);
    BIO *b64 = base64_encrypt(bitmap, img_size);
    BIO_free_all(b64);
    BIO_free_all(file_bio);
    mx_strdel(&bitmap);
    
    // testing
    char *result = mx_file_to_str(mx_strjoin(TEMP_FOLDER, "b64"));

    char *new_bitmap = NULL;
    // new_bitmap = base64_decrypt(result);
    mx_strdel(&result);

    FILE *f = fopen(mx_strjoin(TEMP_FOLDER, "test.png"), "wb");
    fwrite(new_bitmap, img_size, 1, f);
    fclose(f);

    mx_strdel(&new_bitmap);
    
/*
    BIO *bio, *b64;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new_fp(stdout, BIO_NOCLOSE);
    BIO_push(b64, bio);
    BIO_write(b64, json_string, strlen(json_string));
    BIO_flush(b64);

    BIO_free_all(b64);
    */
}
