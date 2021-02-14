#include "../inc/client.h"

static void add_new_int(int **arr, int new_int, int count) {
    int *temp = malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++)
        temp[i] = (*arr)[i];
    free(*arr);
    *arr = malloc(sizeof(int) * (count + 1));
    for (int i = 0; i < count; i++)
        (*arr)[i] = temp[i];
    (*arr)[count] = new_int;
    free(temp);
}

bool add_user_to_group(char *name, int *user_id, int *avatar) {
    if (!strcmp(name, t_account.username))
        return false;
    cJSON *json = cJSON_CreateObject();
    cJSON *json_get_user_id = cJSON_CreateObject();
    cJSON_AddStringToObject(json_get_user_id, "username", name);
    cJSON_AddItemToObject(json,  "get_user_id", json_get_user_id);
    char *json_string = cJSON_PrintUnformatted(json);
    // printf("%s\n", json_string);
    char *result = NULL;
    ssl_client(json_string, &result);
    cJSON *response = cJSON_Parse(result);
    mx_strdel(&result);
    mx_strdel(&json_string);
    cJSON_Delete(json);
    if (cJSON_IsNull(response)) {
        cJSON_Delete(response);
        return false;
    }
    *user_id = cJSON_GetNumberValue(cJSON_GetObjectItem(response, "user_id"));
    *avatar = cJSON_GetNumberValue(cJSON_GetObjectItem(response, "avatar"));
    if (!new_group->count) {
        new_group->users_id = malloc(sizeof(int*));
        new_group->users_id[0] = *user_id;
    }
    else
        add_new_int(&new_group->users_id, *user_id, new_group->count);
    new_group->count = new_group->count + 1;
    cJSON_Delete(response);
    return true;
}

void create_group(int *chat_id) {
    cJSON *json = cJSON_CreateObject();
    cJSON *json_create_chat = cJSON_CreateObject();
    cJSON *json_users_id = cJSON_CreateIntArray(new_group->users_id, new_group->count);
    cJSON_AddItemToObject(json_create_chat, "users_id", json_users_id);
    cJSON_AddNumberToObject(json_create_chat, "sender_id", t_account.id);
    if (new_group->title)
        cJSON_AddStringToObject(json_create_chat, "title", new_group->title);
    else
        cJSON_AddNullToObject(json_create_chat, "title");
    cJSON_AddItemToObject(json,  "create_chat", json_create_chat);
    char *json_string = cJSON_PrintUnformatted(json);
    // printf("%s\n", json_string);
    char *result = NULL;
    ssl_client(json_string, &result);
    mx_strdel(&json_string);
    cJSON *response = cJSON_Parse(result);
    if (cJSON_IsNull(response))
        *chat_id = 0;
    else
        *chat_id = cJSON_GetNumberValue(cJSON_GetObjectItem(response, "chat_id"));
    mx_strdel(&result);
    cJSON_Delete(response);
    cJSON_Delete(json);
    mx_strdel(&new_group->title);
    free(new_group->users_id);
    free(new_group);
}

void get_user(t_user *user) {
    cJSON *user_request = cJSON_CreateObject();
    cJSON *get_user = cJSON_CreateObject();
    cJSON_AddNumberToObject(get_user, "user_id", user->id);
    cJSON_AddItemToObject(user_request, "get_user", get_user);
    char *request_string = cJSON_Print(user_request);
    char *result = NULL;
    cJSON_Delete(user_request);
    ssl_client(request_string, &result);
    mx_strdel(&request_string);
    cJSON *user_response = cJSON_Parse(result);
    mx_strdel(&result);
    user->username = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(user_response, "username")));
    user->name = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(user_response, "name")));
    user->code = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(user_response, "code")));
    user->team = cJSON_GetNumberValue(cJSON_GetObjectItem(user_response, "team"));
    user->avatar = cJSON_GetNumberValue(cJSON_GetObjectItem(user_response, "avatar"));
    user->online = cJSON_IsTrue(cJSON_GetObjectItem(user_response, "online"));
    cJSON_Delete(user_response);
}

void free_user(t_user *user) {
    if (user->id) {
        mx_strdel(&user->username);
        mx_strdel(&user->name);
        mx_strdel(&user->code);
    }
    free(user);
}

void get_chat(t_chat_data *chat) {
    cJSON *chat_request = cJSON_CreateObject();
    cJSON *get_chat = cJSON_CreateObject();
    cJSON_AddNumberToObject(get_chat, "sender_id", t_account.id);
    cJSON_AddNumberToObject(get_chat, "chat_id", chat->chat_id);
    cJSON_AddItemToObject(chat_request, "get_chat", get_chat);
    char *request_string = cJSON_PrintUnformatted(chat_request);
    char *result = NULL;
    cJSON_Delete(chat_request);
    ssl_client(request_string, &result);
    mx_strdel(&request_string);
    cJSON *user_response = cJSON_Parse(result);
    mx_strdel(&result);
    chat->title = strdup(cJSON_GetStringValue(cJSON_GetObjectItem(user_response, "title")));
    chat->members = cJSON_GetNumberValue(cJSON_GetObjectItem(user_response, "members"));
    chat->user->id = cJSON_GetNumberValue(cJSON_GetObjectItem(user_response, "user_id"));
    cJSON_Delete(user_response);
}
