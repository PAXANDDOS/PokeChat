#include "../inc/server.h"

static void escape_apostrophe(char **str) {
    int quotes = 0;
    char *temp = NULL;
    for (int i = 0; (*str)[i]; i++) {
        if ((*str)[i] == '\'')
            quotes++;
    }
    if (quotes == 0) {
        return;
    }
    temp = malloc(strlen(*str) + quotes + 1);
    char p[2];
    for (int i = 0; (*str)[i]; i++) {
        if ((*str)[i] == '\'')
            temp = mx_strrejoin(temp, "''");
        else {
            p[0] = (*str)[i];
            p[1] = '\0';
            temp = mx_strrejoin(temp, p);
        }
    }
    mx_strdel(&(*str));
    *str = mx_strdup(temp);
    mx_strdel(&temp);
}

static void message_handler(char msg[], char **reply, bool *alloc) {
    cJSON *json = cJSON_Parse(msg);
    cJSON *json_update_message_id = cJSON_GetObjectItem(json, "update_message_id");
    cJSON *json_update_messages_rest = cJSON_GetObjectItem(json, "update_messages_rest");
    cJSON *json_get_chats_count = cJSON_GetObjectItem(json, "get_chats_count");
    cJSON *json_get_chats = cJSON_GetObjectItem(json, "get_chats");
    cJSON *json_get_chat = cJSON_GetObjectItem(json, "get_chat");
    cJSON *json_get_user = cJSON_GetObjectItem(json, "get_user");
    cJSON *json_get_user_id = cJSON_GetObjectItem(json, "get_user_id");
    cJSON *json_get_bitmap = cJSON_GetObjectItem(json, "get_bitmap");
    cJSON *json_send_message = cJSON_GetObjectItem(json, "send_message");
    cJSON *json_send_sticker = cJSON_GetObjectItem(json, "send_sticker");
    cJSON *json_send_bitmap = cJSON_GetObjectItem(json, "send_bitmap");
    cJSON *json_send_photo = cJSON_GetObjectItem(json, "send_photo");
    cJSON *json_register_user = cJSON_GetObjectItem(json, "register_user");
    cJSON *json_login_user = cJSON_GetObjectItem(json, "login_user");
    cJSON *json_update_user_main = cJSON_GetObjectItem(json, "update_user_main");
    cJSON *json_update_user_avatar = cJSON_GetObjectItem(json, "update_user_avatar");
    cJSON *json_update_user_team = cJSON_GetObjectItem(json, "update_user_team");
    cJSON *json_update_user_theme = cJSON_GetObjectItem(json, "update_user_theme");
    cJSON *json_update_user_background = cJSON_GetObjectItem(json, "update_user_background");
    cJSON *json_update_user_online = cJSON_GetObjectItem(json, "update_user_online");
    cJSON *json_update_user_offline = cJSON_GetObjectItem(json, "update_user_offline");
    cJSON *json_create_chat = cJSON_GetObjectItem(json, "create_chat");
    cJSON *json_remove_chat = cJSON_GetObjectItem(json, "remove_chat");
    cJSON *json_rename_group = cJSON_GetObjectItem(json, "rename_group");
    if (json_update_message_id) {
        int sender_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_message_id, "sender_id"));
        int chat_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_message_id, "chat_id"));
        int message_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_message_id, "message_id"));
        // printf("UPDATE MESSAGE ID\nuser_id: %d\nchat_id: %d\nmessage_id: %d\n\n", sender_id, chat_id, message_id);
        char *sql_query = NULL;
        // Проверяем действительно ли тот юзер, который запрашивает данные, является участником чата
        char *sql_pattern = "SELECT EXISTS (SELECT id FROM members WHERE user_id=(%d) AND chat_id=(%d));";
        asprintf(&sql_query, sql_pattern, sender_id, chat_id);
        t_list *ex = NULL;
        ex = sqlite3_exec_db(sql_query, DB_LIST);
        int exist = atoi(ex->data);
        mx_strdel(&sql_query);
        mx_clear_list(&ex);
        if (exist == 0) {
            *reply = strdup("null");
            return;
        }
        sql_pattern = "SELECT user_id, date, time, text, sticker_id, photo_id FROM messages WHERE chat_id=(%d) AND message_id=(%d);";
        asprintf(&sql_query, sql_pattern, chat_id, message_id + 1);
        t_list *list = NULL;
        list = sqlite3_exec_db(sql_query, DB_LIST);
        mx_strdel(&sql_query);
        int list_size = mx_list_size(list);
        if (list_size == 0) {
            *reply = strdup("null");
            return;
        }
        t_list *p = list;
        cJSON *json_message = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_message, "message_id", message_id + 1);
        cJSON_AddNumberToObject(json_message, "user_id", atoi(list->data));
        list = list->next;
        cJSON_AddStringToObject(json_message, "date", list->data);
        list = list->next;
        cJSON_AddStringToObject(json_message, "time", list->data);
        list = list->next;
        if (strcmp(list->data, "NULL") != 0)
            cJSON_AddStringToObject(json_message, "text", list->data);
        else
            cJSON_AddNullToObject(json_message, "text");
        list = list->next;
        if (strcmp(list->data, "NULL") != 0)
            cJSON_AddNumberToObject(json_message, "sticker_id", atoi(list->data));
        else
            cJSON_AddNullToObject(json_message, "sticker_id");
        list = list->next;
        if (strcmp(list->data, "NULL") != 0)
            cJSON_AddNumberToObject(json_message, "photo_id", atoi(list->data));
        else
            cJSON_AddNullToObject(json_message, "photo_id");
        mx_clear_list(&p);
        *reply = strdup(cJSON_PrintUnformatted(json_message));
        cJSON_Delete(json_message);
    }
    else if (json_update_messages_rest) {
        int sender_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_messages_rest, "sender_id"));
        int chat_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_messages_rest, "chat_id"));
        int message_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_messages_rest, "message_id"));
        // printf("UPDATE MESSAGES REST\nuser_id: %d\nchat_id: %d\nmessage_id: %d\n\n", sender_id, chat_id, message_id);
        char *sql_query = NULL;
        // Проверяем действительно ли тот юзер, который запрашивает данные, является участником чата
        char *sql_pattern = "SELECT EXISTS (SELECT id FROM members WHERE user_id=(%d) AND chat_id=(%d));";
        asprintf(&sql_query, sql_pattern, sender_id, chat_id);
        t_list *ex = NULL;
        ex = sqlite3_exec_db(sql_query, DB_LIST);
        int exist = atoi(ex->data);
        mx_strdel(&sql_query);
        mx_clear_list(&ex);
        if (exist == 0) {
            *reply = strdup("null");
            return;
        }
        sql_pattern = "SELECT message_id FROM messages WHERE chat_id=(%d) ORDER BY message_id DESC;";
        asprintf(&sql_query, sql_pattern, chat_id);
        t_list *mes_list = NULL;
        mes_list = sqlite3_exec_db(sql_query, DB_LIST);
        mx_strdel(&sql_query);
        int list_size = mx_list_size(mes_list);
        int last_id = 0;
        if (list_size > 0)
            last_id = atoi(mes_list->data);
        mx_clear_list(&mes_list);
        int rest = last_id - message_id;
        if (rest > 0) {
            cJSON *json_messages_rest = cJSON_CreateObject();
            cJSON_AddNumberToObject(json_messages_rest, "messages_rest", rest);
            *reply = strdup(cJSON_PrintUnformatted(json_messages_rest));
            cJSON_Delete(json_messages_rest);
        }
        else {
            *reply = strdup("null");
        }
    }
    else if (json_get_chats_count) {
        int sender_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_get_chats_count, "sender_id"));;
        // printf("GET CHATS COUNT\nuser_id: %d\n\n", sender_id);
        char *sql_query = NULL;
        char *sql_pattern = "SELECT SUM(chats.increment) + SUM(users.increment), COUNT(members.id) FROM chats, users, members \
                             WHERE chats.id=members.chat_id AND users.id=members.user_id AND members.user_id=(%d);";
        asprintf(&sql_query, sql_pattern, sender_id);
        t_list *list = NULL;
        list = sqlite3_exec_db(sql_query, DB_LIST);
        mx_strdel(&sql_query);
        unsigned long long sum = 0;
        int chats_count = 0;
        int list_size = mx_list_size(list);
        if (list_size != 0) {
            sum = atoll(list->data);
            chats_count = atoi(list->next->data);
        }
        mx_clear_list(&list);
        // printf("chats_sum: %llu\n", sum);
        cJSON *json_chats_count = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_chats_count, "chats_count", chats_count);
        cJSON_AddNumberToObject(json_chats_count, "chats_sum", sum);
        *reply = strdup(cJSON_PrintUnformatted(json_chats_count));
        cJSON_Delete(json_chats_count);
    }
    else if (json_get_chats) {
        int sender_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_get_chats, "sender_id"));
        // printf("GET CHATS\nuser_id: %d\n\n", sender_id);
        char *sql_query = NULL;
        char *sql_pattern = "SELECT chat_id FROM members WHERE user_id=(%d);";
        asprintf(&sql_query, sql_pattern, sender_id);
        t_list *list = NULL;
        list = sqlite3_exec_db(sql_query, DB_LIST);
        t_list *p = list;
        int chats_count = mx_list_size(list);
        int *chats = malloc(sizeof(int) * chats_count);
        for (int i = 0; list; i++) {
            chats[i] = atoi(list->data);
            list = list->next;
        }
        mx_clear_list(&p);
        cJSON *json_chats = cJSON_CreateIntArray(chats, chats_count);
        *reply = strdup(cJSON_PrintUnformatted(json_chats));
        mx_strdel(&sql_query);
        cJSON_Delete(json_chats);
    }
    else if (json_get_chat) {
        int sender_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_get_chat, "sender_id"));
        int chat_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_get_chat, "chat_id"));
        // printf("GET CHAT\nchat: %d\n\n", sender_id);
        char *sql_query = NULL;
        char *sql_pattern = "SELECT EXISTS (SELECT id FROM members WHERE user_id=(%d) AND chat_id=(%d));";
        asprintf(&sql_query, sql_pattern, sender_id, chat_id);
        t_list *ex = NULL;
        ex = sqlite3_exec_db(sql_query, DB_LIST);
        int exist = atoi(ex->data);
        mx_clear_list(&ex);
        mx_strdel(&sql_query);
        if (exist == 0) {
            *reply = strdup("null");
        }
        sql_pattern = "SELECT title, members FROM chats WHERE id=(%d);";
        asprintf(&sql_query, sql_pattern, chat_id);
        t_list *list = NULL;
        list = sqlite3_exec_db(sql_query, DB_LIST);
        mx_strdel(&sql_query);
        t_list *p = list;
        cJSON *json_chat = cJSON_CreateObject();
        if (strcmp(list->data, "NULL") != 0) {
            cJSON_AddStringToObject(json_chat, "title", list->data);
            cJSON_AddNumberToObject(json_chat, "user_id", 0);
        }
        else {
            sql_pattern = "SELECT user_id FROM members WHERE chat_id=(%d) AND user_id!=(%d);";
            asprintf(&sql_query, sql_pattern, chat_id, sender_id);
            t_list *interlocutor = NULL;
            interlocutor = sqlite3_exec_db(sql_query, DB_LIST);
            int inter_id = atoi(interlocutor->data);
            mx_clear_list(&interlocutor);
            mx_strdel(&sql_query);
            sql_pattern = "SELECT username FROM users WHERE id=(%d);";
            asprintf(&sql_query, sql_pattern, inter_id);
            interlocutor = sqlite3_exec_db(sql_query, DB_LIST);
            cJSON_AddStringToObject(json_chat, "title", interlocutor->data);
            cJSON_AddNumberToObject(json_chat, "user_id", inter_id);
            mx_clear_list(&interlocutor);
            mx_strdel(&sql_query);
        }
        list = list->next;
        cJSON_AddNumberToObject(json_chat, "members", atoi(list->data));
        mx_clear_list(&p);
        *reply = strdup(cJSON_PrintUnformatted(json_chat));
        mx_strdel(&sql_query);
        cJSON_Delete(json_chat);
    }
    else if (json_get_user) {
        int user_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_get_user, "user_id"));
        // printf("GET USER\nuser_id: %d\n\n", user_id);
        char *sql_query = NULL;
        char *sql_pattern = "SELECT username, name, code, team, avatar, online FROM users WHERE id=(%d);";
        asprintf(&sql_query, sql_pattern, user_id);
        t_list *list = NULL;
        list = sqlite3_exec_db(sql_query, DB_LIST);
        t_list *p = list;
        mx_strdel(&sql_query);
        int list_size = mx_list_size(list);
        if (list_size == 0) {
            *reply = strdup("null");
            return;
        }
        cJSON *json_user = cJSON_CreateObject();
        cJSON_AddStringToObject(json_user, "username", list->data);
        list = list->next;
        cJSON_AddStringToObject(json_user, "name", list->data);
        list = list->next;
        cJSON_AddStringToObject(json_user, "code", list->data);
        list = list->next;
        cJSON_AddNumberToObject(json_user, "team", atoi(list->data));
        list = list->next;
        cJSON_AddNumberToObject(json_user, "avatar", atoi(list->data));
        list = list->next;
        cJSON_AddBoolToObject(json_user, "online", atoi(list->data));
        mx_clear_list(&p);
        *reply = strdup(cJSON_PrintUnformatted(json_user));
        cJSON_Delete(json_user);
    }
    else if (json_get_user_id) {
        char *username = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(json_get_user_id, "username")));
        escape_apostrophe(&username);
        // printf("GET USER ID\nusername: %s\n\n", username);
        char *sql_query = NULL;
        char *sql_pattern = "SELECT id, avatar FROM users WHERE username=('%s');";
        asprintf(&sql_query, sql_pattern, username);
        t_list *list = NULL;
        int user_id = 0, avatar = 0;
        list = sqlite3_exec_db(sql_query, DB_LIST);
        t_list *p = list;
        mx_strdel(&sql_query);
        int list_size = mx_list_size(list);
        if (list_size == 0) {
            *reply = strdup("null");
            return;
        }
        user_id = atoi(list->data);
        list = list->next;
        avatar = atoi(list->data);
        mx_clear_list(&p);
        cJSON *json_user_id = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_user_id, "user_id", user_id);
        cJSON_AddNumberToObject(json_user_id, "avatar", avatar);
        *reply = strdup(cJSON_PrintUnformatted(json_user_id));
        cJSON_Delete(json_user_id);
    }
    else if (json_get_bitmap) {
        int photo_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_get_bitmap, "photo_id"));
        char *count_str = mx_itoa(photo_id);
        char *filepath = mx_strjoin(MEDIA_DIR, count_str);
        char *filepath1 = mx_strjoin(filepath, ".png");
        char *filepath2 = mx_strjoin(filepath, ".jpg");
        char *filepath3 = mx_strjoin(filepath, ".jpeg");

        bool e1 = false, e2 = false, e3 = false;
        if(!access(filepath1, F_OK))
            e1 = true;
        else {
            if(!access(filepath2, F_OK))
                e2 = true;
            else {
                if(!access(filepath3, F_OK))
                    e3 = true;
            }
        }
        mx_strdel(&filepath1);
        mx_strdel(&filepath2);
        mx_strdel(&filepath3);
        mx_strdel(&count_str);
        if (!e1 && !e2 && !e3) {
            mx_strdel(&filepath);
            *reply = strdup("null");
            return;
        }
        if (e1)
            filepath = mx_strrejoin(filepath, ".png");
        else if (e2)
            filepath = mx_strrejoin(filepath, ".jpg");
        else if (e3)
            filepath = mx_strrejoin(filepath, ".jpeg");

        FILE *f = fopen(filepath, "rb");
        int img_size;
        for(img_size = 0; getc(f) != EOF; ++img_size);
        fclose(f);

        char *bitmap = malloc(img_size);
        BIO *file_bio = BIO_new_file(filepath, "rb");
        BIO_read(file_bio, bitmap, img_size);

        BIO *b64 = BIO_new(BIO_f_base64());
        BIO *fo = BIO_new_file(mx_strjoin(TEMP_DIR, "b64"), "w");
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
        BIO_push(b64, fo);
        BIO_write(b64, bitmap, img_size);
        BIO_flush(b64);
        BIO_free_all(b64);
        BIO_free_all(file_bio);
        mx_strdel(&bitmap);

        u_char *result = (u_char*)mx_file_to_str(mx_strjoin(TEMP_DIR, "b64"));

        cJSON *json_send_bitmap = cJSON_CreateObject();
        cJSON_AddStringToObject(json_send_bitmap, "bitmap", (const char*)result);
        cJSON_AddStringToObject(json_send_bitmap, "extension", e1 ? ".png" : (e2 ? ".jpg" : "jpeg"));
        *reply = cJSON_PrintUnformatted(json_send_bitmap);
        *alloc = true;
        cJSON_Delete(json_send_bitmap);
    }
    else if (json_send_message) {
        int sender_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_send_message, "sender_id"));
        int chat_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_send_message, "chat_id"));
        char *text = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(json_send_message, "text")));
        char *date = cJSON_GetStringValue(cJSON_GetObjectItem(json_send_message, "date"));
        char *time = cJSON_GetStringValue(cJSON_GetObjectItem(json_send_message, "time"));
        escape_apostrophe(&text);
        // printf("SEND MESSAGE\nchat_id: %d\nuser_id: %d\ntext: %s\n\n", chat_id, sender_id, text);
        char *sql_query = NULL;
        char *sql_pattern = "SELECT EXISTS (SELECT id FROM members WHERE user_id=(%d) AND chat_id=(%d));";
        asprintf(&sql_query, sql_pattern, sender_id, chat_id);
        t_list *ex = NULL;
        ex = sqlite3_exec_db(sql_query, DB_LIST);
        int exist = atoi(ex->data);
        // printf("exist: %d\n", exist);
        mx_clear_list(&ex);
        mx_strdel(&sql_query);
        if (exist == 0) {
            mx_strdel(&text);
            *reply = strdup("null");
            return;
        }
        sql_pattern = "SELECT message_id FROM messages WHERE chat_id=(%d) ORDER BY message_id DESC;";
        asprintf(&sql_query, sql_pattern, chat_id);
        t_list *mes_list = NULL;
        mes_list = sqlite3_exec_db(sql_query, DB_LIST);
        mx_strdel(&sql_query);
        int list_size = mx_list_size(mes_list);
        int last_id = 0;
        if (list_size > 0)
            last_id = atoi(mes_list->data);
        mx_clear_list(&mes_list);
        sql_pattern = "INSERT INTO messages (message_id, chat_id, user_id, date, time, text) VALUES (%d, %d, %d, '%s', '%s', '%s');";
        asprintf(&sql_query, sql_pattern, last_id + 1, chat_id, sender_id, date, time, text);
        sqlite3_exec_db(sql_query, DB_LAST_ID);
        mx_strdel(&text);
        cJSON *json_reply = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_reply, "message_id", last_id + 1);
        *reply = strdup(cJSON_PrintUnformatted(json_reply));
        mx_strdel(&sql_query);
        cJSON_Delete(json_reply);
    }
    else if (json_send_sticker) {
        int sender_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_send_sticker, "sender_id"));
        int chat_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_send_sticker, "chat_id"));
        int sticker_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_send_sticker, "sticker_id"));
        char *date = cJSON_GetStringValue(cJSON_GetObjectItem(json_send_sticker, "date"));
        char *time = cJSON_GetStringValue(cJSON_GetObjectItem(json_send_sticker, "time"));
        // printf("SEND STICKER\nchat_id: %d\nuser_id: %d\nsticker: %d\n\n", chat_id, sender_id, sticker_id);
        char *sql_query = NULL;
        char *sql_pattern = "SELECT EXISTS (SELECT id FROM members WHERE user_id=(%d) AND chat_id=(%d));";
        asprintf(&sql_query, sql_pattern, sender_id, chat_id);
        t_list *ex = NULL;
        ex = sqlite3_exec_db(sql_query, DB_LIST);
        int exist = atoi(ex->data);
        // printf("exist: %d\n", exist);
        mx_clear_list(&ex);
        mx_strdel(&sql_query);
        if (exist == 0) {
            *reply = strdup("null");
            return;
        }
        sql_pattern = "SELECT message_id FROM messages WHERE chat_id=(%d) ORDER BY message_id DESC;";
        asprintf(&sql_query, sql_pattern, chat_id);
        t_list *mes_list = NULL;
        mes_list = sqlite3_exec_db(sql_query, DB_LIST);
        mx_strdel(&sql_query);
        int list_size = mx_list_size(mes_list);
        int last_id = 0;
        if (list_size > 0)
            last_id = atoi(mes_list->data);
        mx_clear_list(&mes_list);
        sql_pattern = "INSERT INTO messages (message_id, chat_id, user_id, date, time, sticker_id) VALUES (%d, %d, %d, '%s', '%s', %d);";
        asprintf(&sql_query, sql_pattern, last_id + 1, chat_id, sender_id, date, time, sticker_id);
        sqlite3_exec_db(sql_query, DB_LAST_ID);
        cJSON *json_reply = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_reply, "message_id", last_id + 1);
        *reply = strdup(cJSON_PrintUnformatted(json_reply));
        mx_strdel(&sql_query);
        cJSON_Delete(json_reply);
    }
    else if (json_send_bitmap) {
        char *bitmap64 = cJSON_GetStringValue(cJSON_GetObjectItem(json_send_bitmap, "bitmap"));
        char *extension = cJSON_GetStringValue(cJSON_GetObjectItem(json_send_bitmap, "extension"));

        FILE *file = fopen("media_count", "rb");
        int buf, count = 1;
        if (file) {
            fread(&buf, sizeof(buf), 1, file);
            count = buf + 1;
            fclose(file);
        }
        file = NULL;
        file = fopen("media_count", "wb");
        fwrite(&count, sizeof(buf), 1, file);
        fclose(file);
        file = NULL;

        int length = strlen((const char*)bitmap64);
        const int img_size = length * 3 / 4;
        u_char *bitmap = malloc(img_size + 1);
        EVP_DecodeBlock(bitmap, (const u_char*)bitmap64, length);

        char *count_str = mx_itoa(count);
        char *filepath = mx_strjoin(MEDIA_DIR, count_str);
        filepath = mx_strrejoin(filepath, extension);
        file = fopen(filepath, "wb");
        fwrite(bitmap, img_size, 1, file);
        fclose(file);
        if (bitmap)
            free(bitmap);

        cJSON *json_reply = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_reply, "photo_id", count);
        *reply = strdup(cJSON_PrintUnformatted(json_reply));
        mx_strdel(&count_str);
        cJSON_Delete(json_reply);
    }
    else if (json_send_photo) {
        int sender_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_send_photo, "sender_id"));
        int chat_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_send_photo, "chat_id"));
        int photo_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_send_photo, "photo_id"));
        char *date = cJSON_GetStringValue(cJSON_GetObjectItem(json_send_photo, "date"));
        char *time = cJSON_GetStringValue(cJSON_GetObjectItem(json_send_photo, "time"));

        char *sql_query = NULL;
        char *sql_pattern = "SELECT EXISTS (SELECT id FROM members WHERE user_id=(%d) AND chat_id=(%d));";
        asprintf(&sql_query, sql_pattern, sender_id, chat_id);
        t_list *ex = NULL;
        ex = sqlite3_exec_db(sql_query, DB_LIST);
        int exist = atoi(ex->data);
        mx_clear_list(&ex);
        mx_strdel(&sql_query);
        if (exist == 0) {
            *reply = strdup("null");
            return;
        }
        sql_pattern = "SELECT message_id FROM messages WHERE chat_id=(%d) ORDER BY message_id DESC;";
        asprintf(&sql_query, sql_pattern, chat_id);
        t_list *mes_list = NULL;
        mes_list = sqlite3_exec_db(sql_query, DB_LIST);
        mx_strdel(&sql_query);
        int list_size = mx_list_size(mes_list);
        int last_id = 0;
        if (list_size > 0)
            last_id = atoi(mes_list->data);
        mx_clear_list(&mes_list);
        sql_pattern = "INSERT INTO messages (message_id, chat_id, user_id, date, time, photo_id) VALUES (%d, %d, %d, '%s', '%s', %d);";
        asprintf(&sql_query, sql_pattern, last_id + 1, chat_id, sender_id, date, time, photo_id);
        sqlite3_exec_db(sql_query, DB_LAST_ID);
        cJSON *json_reply = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_reply, "message_id", last_id + 1);
        *reply = strdup(cJSON_PrintUnformatted(json_reply));
        mx_strdel(&sql_query);
        cJSON_Delete(json_reply);
    }
    else if (json_register_user) {
        char *username = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(json_register_user, "username")));
        char *name = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(json_register_user, "name")));
        char *code = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(json_register_user, "code")));
        char *password = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(json_register_user, "password")));
        int team = cJSON_GetNumberValue(cJSON_GetObjectItem(json_register_user, "team"));
        // printf("%s\n", username);
        escape_apostrophe(&username);
        escape_apostrophe(&name);
        escape_apostrophe(&code);
        escape_apostrophe(&password);
        // printf("REGISTER USER\nusername: %s\nname: %s\ncode: %s\npassword: %s\n\n", username, name, code, password);
        char *sql_query = NULL;
        char *sql_pattern = "SELECT EXISTS (SELECT id FROM users WHERE username=('%s'));";
        asprintf(&sql_query, sql_pattern, username);
        t_list *ex = NULL;
        ex = sqlite3_exec_db(sql_query, DB_LIST);
        int exist = atoi(ex->data);
        // printf("exist: %d\n", exist);
        mx_clear_list(&ex);
        mx_strdel(&sql_query);
        if (exist == 1) {
            *reply = strdup("{\"user_id\": 0}");
            return;
        }
        sql_pattern = "INSERT INTO users (username, name, code, password, team) VALUES ('%s', '%s', '%s', '%s', %d);";
        asprintf(&sql_query, sql_pattern, username, name, code, password, team);
        int *ai = sqlite3_exec_db(sql_query, DB_LAST_ID);
        int user_id = *ai;
        mx_strdel(&username);
        mx_strdel(&name);
        mx_strdel(&code);
        mx_strdel(&password);
        cJSON *json_reply = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_reply, "user_id", user_id);
        *reply = strdup(cJSON_PrintUnformatted(json_reply));
        mx_strdel(&sql_query);
        cJSON_Delete(json_reply);
    }
    else if (json_login_user) {
        char *username = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(json_login_user, "username")));
        char *password = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(json_login_user, "password")));
        escape_apostrophe(&username);
        escape_apostrophe(&password);
        // printf("LOGIN USER\nusername: %s\npassword: %s\n\n", username, password);
        char *sql_query = NULL;
        char *sql_pattern = "SELECT id, name, code, team, avatar, theme, background FROM users WHERE username=('%s') AND password=('%s');";
        asprintf(&sql_query, sql_pattern, username, password);
        t_list *list = NULL;
        list = sqlite3_exec_db(sql_query, DB_LIST);
        t_list *p = list;
        mx_strdel(&sql_query);
        mx_strdel(&username);
        mx_strdel(&password);
        if (list == NULL) {
            *reply = strdup("null");
            return;
        }
        cJSON *json_login_data = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_login_data, "user_id", atoi(list->data));
        list = list->next;
        cJSON_AddStringToObject(json_login_data, "name", list->data);
        list = list->next;
        cJSON_AddStringToObject(json_login_data, "code", list->data);
        list = list->next;
        cJSON_AddNumberToObject(json_login_data, "team", atoi(list->data));
        list = list->next;
        cJSON_AddNumberToObject(json_login_data, "avatar", atoi(list->data));
        list = list->next;
        cJSON_AddNumberToObject(json_login_data, "theme", atoi(list->data));
        list = list->next;
        cJSON_AddNumberToObject(json_login_data, "background", atoi(list->data));
        mx_clear_list(&p);
        *reply = strdup(cJSON_PrintUnformatted(json_login_data));
        cJSON_Delete(json_login_data);
    }
    else if (json_update_user_main) {
        int user_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_user_main, "user_id"));
        char *username = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(json_update_user_main, "username")));
        char *name = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(json_update_user_main, "name")));
        char *code = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(json_update_user_main, "code")));
        char *password = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(json_update_user_main, "password")));
        escape_apostrophe(&username);
        escape_apostrophe(&name);
        escape_apostrophe(&code);
        escape_apostrophe(&password);
        // printf("UPDATE USER MAIN\nusername: %s\nname: %s\ncode: %s\npassword: %s\n\n", username, name, code, password);
        char *sql_query = NULL;
        char *sql_pattern = "UPDATE users SET username=('%s'), name=('%s'), code=('%s'), password=('%s') WHERE id=(%d);";
        asprintf(&sql_query, sql_pattern, username, name, code, password, user_id);
        sqlite3_exec_db(sql_query, DB_LAST_ID);
        mx_strdel(&sql_query);
        mx_strdel(&username);
        mx_strdel(&name);
        mx_strdel(&code);
        mx_strdel(&password);
        *reply = strdup("null");
    }
    else if (json_update_user_avatar) {
        int user_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_user_avatar, "user_id"));
        int avatar_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_user_avatar, "avatar"));
        // printf("UPDATE USER AVATAR\navatar_id: %d\n\n", avatar_id);
        char *sql_query = NULL;
        char *sql_pattern = "UPDATE users SET avatar=(%d), increment=increment+1 WHERE id=(%d);";
        asprintf(&sql_query, sql_pattern, avatar_id, user_id);
        sqlite3_exec_db(sql_query, DB_LAST_ID);
        mx_strdel(&sql_query);
        *reply = strdup("null");
    }
    else if (json_update_user_team) {
        int user_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_user_team, "user_id"));
        int team = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_user_team, "team"));
        // printf("UPDATE USER TEAM\nteam: %d\n\n", team);
        char *sql_query = NULL;
        char *sql_pattern = "UPDATE users SET team=(%d) WHERE id=(%d);";
        asprintf(&sql_query, sql_pattern, team, user_id);
        sqlite3_exec_db(sql_query, DB_LAST_ID);
        mx_strdel(&sql_query);
        *reply = strdup("null");
    }
    else if (json_update_user_theme) {
        int user_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_user_theme, "user_id"));
        int theme = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_user_theme, "theme"));
        // printf("UPDATE USER THEME\ntheme: %d\n\n", theme);
        char *sql_query = NULL;
        char *sql_pattern = "UPDATE users SET theme=(%d) WHERE id=(%d);";
        asprintf(&sql_query, sql_pattern, theme, user_id);
        sqlite3_exec_db(sql_query, DB_LAST_ID);
        mx_strdel(&sql_query);
        *reply = strdup("null");
    }
    else if (json_update_user_background) {
        int user_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_user_background, "user_id"));
        int bg = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_user_background, "background"));
        // printf("UPDATE USER BG\nbackground: %d\n\n", bg);
        char *sql_query = NULL;
        char *sql_pattern = "UPDATE users SET background=(%d) WHERE id=(%d);";
        asprintf(&sql_query, sql_pattern, bg, user_id);
        sqlite3_exec_db(sql_query, DB_LAST_ID);
        mx_strdel(&sql_query);
        *reply = strdup("null");
    }
    else if (json_update_user_online) {
        int user_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_user_online, "user_id"));
        // printf("UPDATE USER ONLINE\nuser_id: %d\n\n", user_id);
        char *sql_query = NULL;
        char *sql_pattern = "UPDATE users SET online=(1), increment=increment+1 WHERE id=(%d);";
        asprintf(&sql_query, sql_pattern, user_id);
        sqlite3_exec_db(sql_query, DB_LAST_ID);
        mx_strdel(&sql_query);
        *reply = strdup("null");
    }
    else if (json_update_user_offline) {
        int user_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_user_offline, "user_id"));
        // printf("UPDATE USER OFFLINE\nuser_id: %d\n\n", user_id);
        char *sql_query = NULL;
        char *sql_pattern = "UPDATE users SET online=(0), increment=increment+1 WHERE id=(%d);";
        asprintf(&sql_query, sql_pattern, user_id);
        sqlite3_exec_db(sql_query, DB_LAST_ID);
        mx_strdel(&sql_query);
        *reply = strdup("null");
    }
    else if (json_create_chat) {
        int sender_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_create_chat, "sender_id"));
        char *title = NULL;
        if (!cJSON_IsNull(cJSON_GetObjectItem(json_create_chat, "title"))) {
            title = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(json_create_chat, "title")));
            escape_apostrophe(&title);
        }
        cJSON *users = cJSON_GetObjectItem(json_create_chat, "users_id");
        int members = cJSON_GetArraySize(users);
        // printf("CREATE CHAT\n\n");
        char *sql_query = NULL;
        if (title) {
            char *sql_pattern = "INSERT INTO chats (title, members) VALUES ('%s', %d);";
            asprintf(&sql_query, sql_pattern, title, members + 1);
        }
        else {
            int user_id = cJSON_GetNumberValue(cJSON_GetArrayItem(users, 0));
            char *sql_pattern = "SELECT chats.id FROM chats, members WHERE members.chat_id=chats.id AND chats.title IS NULL AND members.user_id=(%d);";
            asprintf(&sql_query, sql_pattern, sender_id);
            t_list *list1 = NULL;
            list1 = sqlite3_exec_db(sql_query, DB_LIST);
            mx_strdel(&sql_query);
            t_list *p1 = list1;
            int list1_size = mx_list_size(list1);
            if (list1_size > 0) {
                asprintf(&sql_query, sql_pattern, user_id);
                t_list *list2 = NULL;
                list2 = sqlite3_exec_db(sql_query, DB_LIST);
                mx_strdel(&sql_query);
                t_list *p2 = list2;
                int list2_size = mx_list_size(list2);
                if (list2_size > 0) {
                    for (int i = 0; i < list1_size; i++, list1 = list1->next)
                        for (int j = 0; j < list2_size; j++, list2 = list2->next)
                            if (atoi(list1->data) == atoi(list2->data)) {
                                mx_clear_list(&p1);
                                mx_clear_list(&p2);
                                *reply = strdup("null");
                                return;
                            }
                    mx_clear_list(&p2);
                }
                mx_clear_list(&p1);
            }
            sql_query = strdup("INSERT INTO chats (members) VALUES (2);");
        }
        int *ai = sqlite3_exec_db(sql_query, DB_LAST_ID);
        int chat_id = *ai;
        mx_strdel(&sql_query);

        char *sql_array = NULL;
        char *temp_chat_id = mx_itoa(chat_id);
        for (int i = 0; i < members; i++) {
            int user_id = cJSON_GetNumberValue(cJSON_GetArrayItem(users, i));
            sql_array = mx_strrejoin(sql_array, "(");
            sql_array = mx_strrejoin(sql_array, temp_chat_id);
            sql_array = mx_strrejoin(sql_array, ",");
            char *temp_user_id = mx_itoa(user_id);
            sql_array = mx_strrejoin(sql_array, temp_user_id);
            sql_array = mx_strrejoin(sql_array, ",0),");
            mx_strdel(&temp_user_id);
        }
        sql_array = mx_strrejoin(sql_array, "(");
        sql_array = mx_strrejoin(sql_array, temp_chat_id);
        sql_array = mx_strrejoin(sql_array, ",");
        char *temp_user_id = mx_itoa(sender_id);
        sql_array = mx_strrejoin(sql_array, temp_user_id);
        sql_array = mx_strrejoin(sql_array, ",1)");
        mx_strdel(&temp_chat_id);
        mx_strdel(&temp_user_id);
        sql_query = strdup("INSERT INTO members (chat_id, user_id, admin) VALUES ");
        sql_query = mx_strrejoin(sql_query, sql_array);
        sql_query = mx_strrejoin(sql_query, ";");
        sqlite3_exec_db(sql_query, DB_LAST_ID);
        mx_strdel(&title);
        mx_strdel(&sql_query);
        mx_strdel(&sql_array);
        cJSON *new_chat = cJSON_CreateObject();
        cJSON_AddNumberToObject(new_chat, "chat_id", chat_id);
        *reply = strdup(cJSON_PrintUnformatted(new_chat));
        cJSON_Delete(new_chat);
    }
    else if (json_remove_chat) {
        int sender_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_remove_chat, "sender_id"));
        int chat_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_remove_chat, "chat_id"));
        char *sql_query = NULL;
        char *sql_pattern = "SELECT members FROM chats WHERE id=(%d);";
        asprintf(&sql_query, sql_pattern, chat_id);
        t_list *list = NULL;
        list = sqlite3_exec_db(sql_query, DB_LIST);
        mx_strdel(&sql_query);
        if (mx_list_size(list) == 0) {
            *reply = strdup("null");
            return;
        }
        bool direct = atoi(list->data) == 2;
        mx_clear_list(&list);
        if (direct) {
            sql_pattern = "DELETE FROM chats WHERE id=(%d);";
            asprintf(&sql_query, sql_pattern, chat_id);
            sqlite3_exec_db(sql_query, DB_LAST_ID);
            mx_strdel(&sql_query);
            sql_pattern = "DELETE FROM members WHERE chat_id=(%d);";
            asprintf(&sql_query, sql_pattern, chat_id);
            sqlite3_exec_db(sql_query, DB_LAST_ID);
        }
        else {
            sql_pattern = "DELETE FROM members WHERE user_id=(%d);";
            asprintf(&sql_query, sql_pattern, sender_id);
            sqlite3_exec_db(sql_query, DB_LAST_ID);
        }
        mx_strdel(&sql_query);
        *reply = strdup("null");
    }
    else if (json_rename_group) {
        int sender_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_rename_group, "sender_id"));
        int chat_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_rename_group, "chat_id"));
        char *title = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(json_rename_group, "title")));
        escape_apostrophe(&title);
        char *sql_query = NULL;
        char *sql_pattern = "SELECT EXISTS (SELECT id FROM members WHERE user_id=(%d) AND chat_id=(%d));";
        asprintf(&sql_query, sql_pattern, sender_id, chat_id);
        t_list *ex = NULL;
        ex = sqlite3_exec_db(sql_query, DB_LIST);
        int exist = atoi(ex->data);
        mx_clear_list(&ex);
        mx_strdel(&sql_query);
        if (exist == 0) {
            mx_strdel(&title);
            *reply = strdup("null");
            return;
        }
        sql_pattern = "UPDATE chats SET title=('%s'), increment=increment+1 WHERE id=(%d);";
        asprintf(&sql_query, sql_pattern, title, chat_id);
        sqlite3_exec_db(sql_query, DB_LAST_ID);
        mx_strdel(&sql_query);
        mx_strdel(&title);
        *reply = strdup("null");
    }
    else {
        *reply = strdup("null");
    }
    cJSON_Delete(json);
}

void requests_handler(SSL *ssl) {
    char buf[4096];
    char *reply;
    int sd, bytes;

    if (SSL_accept(ssl) == -1)
        ERR_print_errors_fp(stderr);
    else {
        bytes = SSL_read(ssl, buf, sizeof(buf));
        if (bytes > 0) {
            buf[bytes] = 0;
            if (is_num(buf)) {  // For requests with more than 4096 bytes
                int len = atoi(buf);
                char *buf_alloc = NULL;
                SSL_write(ssl, "", 1);
                bytes = 0;
                while (bytes < len) {
                    bytes += SSL_read(ssl, buf, sizeof(buf) - 1);
                    buf[sizeof(buf) - 1] = 0;
                    buf_alloc = mx_strrejoin(buf_alloc, buf);
                    for (int i = 0; i < (int)sizeof(buf); i++)
                        buf[i] = 0;
                }
                if (bytes > 0) {
                    message_handler(buf_alloc, &reply, NULL);
                    SSL_write(ssl, reply, strlen(reply));
                    mx_strdel(&buf_alloc);
                }
                else
                    ERR_print_errors_fp(stderr);
            }
            else {
                bool alloc = false;
                message_handler(buf, &reply, &alloc);
                if (!alloc)
                    SSL_write(ssl, reply, strlen(reply));
                else {
                    int len = strlen(reply);
                    char *len_str = mx_itoa(len);
                    SSL_write(ssl, len_str, strlen(len_str));
                    SSL_read(ssl, buf, sizeof(buf));
                    SSL_write(ssl, reply, len);
                    mx_strdel(&len_str);
                }
            }
        }
        else
            ERR_print_errors_fp(stderr);
    }
    mx_strdel(&reply);
    sd = SSL_get_fd(ssl);
    SSL_free(ssl);
    close(sd);
}
