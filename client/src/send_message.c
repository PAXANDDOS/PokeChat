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

void send_message() {
    int chat_id = 1000;
    char *text = msg_data.content;
    printf("%s\n", text);
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "chat_id", (double)chat_id);
    cJSON_AddStringToObject(json, "text", text);
    char *json_string = cJSON_Print(json);
    printf("%s\n", json_string);
    ssl_client("10.11.4.9", 4096, json_string);
    mx_strdel(&json_string);
}

void send_sticker() {
    int chat_id = 1000;
    int sticker_id = 1;
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "chat_id", (double)chat_id);
    cJSON_AddNumberToObject(json, "sticker", sticker_id);
    printf("%s\n", cJSON_Print(json));
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
