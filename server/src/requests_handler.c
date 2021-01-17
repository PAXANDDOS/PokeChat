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

static void message_handler(char msg[], char **reply) {
    cJSON *json = cJSON_Parse(msg);
    cJSON *json_update_message_id = cJSON_GetObjectItem(json, "update_message_id");
    cJSON *json_get_chats_count = cJSON_GetObjectItem(json, "get_chats_count");
    cJSON *json_get_chats = cJSON_GetObjectItem(json, "get_chats");
    cJSON *json_send_message = cJSON_GetObjectItem(json, "send_message");
    cJSON *json_register_user = cJSON_GetObjectItem(json, "register_user");
    cJSON *json_login_user = cJSON_GetObjectItem(json, "login_user");
    cJSON *json_update_user_main = cJSON_GetObjectItem(json, "update_user_main");
    cJSON *json_update_user_team = cJSON_GetObjectItem(json, "update_user_team");
    cJSON *json_update_user_theme = cJSON_GetObjectItem(json, "update_user_theme");
    cJSON *json_update_user_background = cJSON_GetObjectItem(json, "update_user_background");
    if (json_update_message_id) {
        int sender_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_message_id, "sender_id"));
        int chat_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_message_id, "chat_id"));
        int message_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_message_id, "message_id"));
        printf("UPDATE MESSAGE ID\nuser_id: %d\nchat_id: %d\nmessage_id: %d\n\n", sender_id, chat_id, message_id);
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
        // Вытаскиваем последний message_id
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
        // Если у клиента id меньше актуального
        if (message_id < last_id) {
            cJSON *message_array = cJSON_CreateArray();
            // Заполняем массив из недостающих сообщений
            for (int i = message_id + 1; i <= last_id; i++) {
                sql_pattern = "SELECT user_id, text, sticker_id, photo_id FROM messages WHERE chat_id=(%d) AND message_id=(%d);";
                asprintf(&sql_query, sql_pattern, chat_id, i);
                t_list *list = NULL;
                list = sqlite3_exec_db(sql_query, DB_LIST);
                mx_strdel(&sql_query);
                cJSON *json_message = cJSON_CreateObject();
                cJSON_AddNumberToObject(json_message, "message_id", i);
                cJSON_AddNumberToObject(json_message, "user_id", atoi(list->data));
                list = list->next;
                if (strcmp(list->data, "NULL") != 0)
                    cJSON_AddStringToObject(json_message, "text", list->data);
                list = list->next;
                if (strcmp(list->data, "NULL") != 0)
                    cJSON_AddNumberToObject(json_message, "sticker_id", atoi(list->data));
                list = list->next;
                if (strcmp(list->data, "NULL") != 0)
                    cJSON_AddNumberToObject(json_message, "photo_id", atoi(list->data));
                mx_clear_list(&list);
                cJSON_AddItemToArray(message_array, json_message);
            }
            *reply = strdup(cJSON_PrintUnformatted(message_array));
            cJSON_Delete(message_array);
        }
        else {
            *reply = strdup("null");
        }
    }
    else if (json_get_chats_count) {
        int sender_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_get_chats_count, "sender_id"));;
        printf("GET CHATS COUNT\nuser_id: %d\n\n", sender_id);
        char *sql_query = NULL;
        char *sql_pattern = "SELECT COUNT(id) FROM members WHERE user_id=(%d);";
        asprintf(&sql_query, sql_pattern, sender_id);
        t_list *list = NULL;
        int chats_count = 0;
        list = sqlite3_exec_db(sql_query, DB_LIST);
        int list_size = mx_list_size(list);
        if (list_size != 0)
            chats_count = atoi(list->data);
        mx_clear_list(&list);
        printf("chats_count: %d\n", chats_count);
        cJSON *json_chats_count = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_chats_count, "chats_count", chats_count);
        *reply = strdup(cJSON_PrintUnformatted(json_chats_count));
        mx_strdel(&sql_query);
        cJSON_Delete(json_chats_count);
    }
    else if (json_get_chats) {
        int sender_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_get_chats, "sender_id"));
        printf("GET CHATS\nuser_id: %d\n\n", sender_id);
        char *sql_query = NULL;
        char *sql_pattern = "SELECT chat_id FROM members WHERE user_id=(%d);";
        asprintf(&sql_query, sql_pattern, sender_id);
        t_list *list = NULL;
        list = sqlite3_exec_db(sql_query, DB_LIST);
        int chats_count = mx_list_size(list);
        int *chats = malloc(sizeof(int) * chats_count);
        for (int i = 0; list; i++) {
            chats[i] = atoi(list->data);
            list = list->next;
        }
        cJSON *json_chats = cJSON_CreateIntArray(chats, chats_count);
        *reply = strdup(cJSON_PrintUnformatted(json_chats));
        mx_strdel(&sql_query);
        cJSON_Delete(json_chats);
    }
    else if (json_send_message) {
        int sender_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_send_message, "sender_id"));
        int chat_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_send_message, "chat_id"));
        char *text = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(json_send_message, "text")));
        escape_apostrophe(&text);
        printf("SEND MESSAGE\nchat_id: %d\nuser_id: %d\ntext: %s\n\n", chat_id, sender_id, text);
        char *sql_query = NULL;
        char *sql_pattern = "SELECT EXISTS (SELECT id FROM members WHERE user_id=(%d) AND chat_id=(%d));";
        asprintf(&sql_query, sql_pattern, sender_id, chat_id);
        t_list *ex = NULL;
        ex = sqlite3_exec_db(sql_query, DB_LIST);
        int exist = atoi(ex->data);
        printf("exist: %d\n", exist);
        mx_clear_list(&ex);
        mx_strdel(&sql_query);
        if (exist == 0) {
            mx_strdel(&sql_query);
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
        sql_pattern = "INSERT INTO messages (message_id, chat_id, user_id, text) VALUES (%d, %d, %d, '%s');";
        asprintf(&sql_query, sql_pattern, last_id + 1, chat_id, sender_id, text);
        sqlite3_exec_db(sql_query, DB_LAST_ID);
        mx_strdel(&text);
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
        printf("%s\n", username);
        escape_apostrophe(&username);
        escape_apostrophe(&name);
        escape_apostrophe(&code);
        escape_apostrophe(&password);
        printf("REGISTER USER\nusername: %s\nname: %s\ncode: %s\npassword: %s\n\n", username, name, code, password);
        char *sql_query = NULL;
        char *sql_pattern = "SELECT EXISTS (SELECT id FROM users WHERE username=('%s'));";
        asprintf(&sql_query, sql_pattern, username);
        t_list *ex = NULL;
        ex = sqlite3_exec_db(sql_query, DB_LIST);
        int exist = atoi(ex->data);
        printf("exist: %d\n", exist);
        mx_clear_list(&ex);
        mx_strdel(&sql_query);
        if (exist == 1) {
            *reply = strdup("{\"user_id\": -1}");
            return;
        }
        sql_pattern = "INSERT INTO users (username, name, code, password) VALUES ('%s', '%s', '%s', '%s');";
        asprintf(&sql_query, sql_pattern, username, name, code, password);
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
        printf("LOGIN USER\nusername: %s\npassword: %s\n\n", username, password);
        char *sql_query = NULL;
        char *sql_pattern = "SELECT id, name, code, team, avatar, theme, background FROM users WHERE username=('%s') AND password=('%s');";
        asprintf(&sql_query, sql_pattern, username, password);
        t_list *list = NULL;
        list = sqlite3_exec_db(sql_query, DB_LIST);
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
        mx_clear_list(&list);
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
        printf("UPDATE USER MAIN\nusername: %s\nname: %s\ncode: %s\npassword: %s\n\n", username, name, code, password);
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
    else if (json_update_user_team) {
        int user_id = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_user_team, "user_id"));
        int team = cJSON_GetNumberValue(cJSON_GetObjectItem(json_update_user_team, "team"));
        printf("UPDATE USER TEAM\nteam: %d\n\n", team);
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
        printf("UPDATE USER THEME\ntheme: %d\n\n", theme);
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
        printf("UPDATE USER BG\nbackground: %d\n\n", bg);
        char *sql_query = NULL;
        char *sql_pattern = "UPDATE users SET background=(%d) WHERE id=(%d);";
        asprintf(&sql_query, sql_pattern, bg, user_id);
        sqlite3_exec_db(sql_query, DB_LAST_ID);
        mx_strdel(&sql_query);
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
            printf("Client message: \"%s\"\n", buf);

            message_handler(buf, &reply);
            printf("reply: %s\n", reply);

            SSL_write(ssl, reply, strlen(reply));
        }
        else
            ERR_print_errors_fp(stderr);
    }
    mx_strdel(&reply);
    sd = SSL_get_fd(ssl);
    SSL_free(ssl);
    close(sd);
}
