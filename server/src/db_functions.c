#include "../inc/server.h"

static void sqlite3_create_db() {
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);
    char *sql = NULL, *err_msg = 0;
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    sql = mx_strrejoin(sql, "PRAGMA encoding = \"UTF-8\";");
    sql = mx_strrejoin(sql, "CREATE TABLE `users` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT , `username` VARCHAR(10) NOT NULL , `name` VARCHAR(10) NOT NULL , `code` VARCHAR(12) NOT NULL , `password` VARCHAR(16) NOT NULL, `team` INT(1) NOT NULL DEFAULT '1', `avatar` INT(9) NOT NULL DEFAULT '0', `theme` INT(1) NOT NULL DEFAULT '2', `background` INT(1) NOT NULL DEFAULT '1', `online` BOOLEAN NOT NULL DEFAULT TRUE, `increment` UNSIGNED INT NOT NULL DEFAULT 1 );");
    sql = mx_strrejoin(sql, "CREATE TABLE `chats` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT , `title` VARCHAR(16) DEFAULT NULL , `members` INT(4) NOT NULL DEFAULT '2', `increment` UNSIGNED INT NOT NULL DEFAULT 1 );");
    sql = mx_strrejoin(sql, "CREATE TABLE `members` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT , `chat_id` INT NOT NULL , `user_id` INT NOT NULL , `admin` BOOLEAN NOT NULL DEFAULT FALSE );");
    sql = mx_strrejoin(sql, "CREATE TABLE `messages` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT , `message_id` INT NOT NULL , `chat_id` INT NOT NULL , `user_id` INT NOT NULL , `date` VARCHAR(10) NOT NULL , `time` VARCHAR(5) NOT NULL , `text` VARCHAR(1024) NULL DEFAULT NULL , `sticker_id` INT NULL DEFAULT NULL , `photo_id` INT NULL DEFAULT NULL );");
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    mx_strdel(&sql);
    sqlite3_close(db);
}

static int callback(void *data, int argc, char **argv, char **azColName) {
    (void)azColName;
    t_list **list_data = (t_list**)data;

    if (argc == 0)
        return 0;
    for (int i = 0; i < argc; i++) {
        // printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        if(argv[i] == NULL)
            mx_push_back(*(&list_data), strdup("NULL"));
        else
            mx_push_back(*(&list_data), strdup(argv[i]));
    }
    return 0;
}

static void sqlite3_open_db() {
    struct stat buffer;
    int exist = stat(DB_NAME, &buffer);
    if (exist != 0)
        sqlite3_create_db();
}

void *sqlite3_exec_db(char *query, int type) {
    sqlite3_open_db();
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);
    char *err_msg = 0;
    t_list *list = NULL;
    int auto_inc;

    // printf("database_request: %s\n", query);
    if (type == DB_LIST) {
        rc = sqlite3_exec(db, query, callback, &list, &err_msg);
        sqlite3_close(db);
        return list;
    }
    if (type == DB_LAST_ID) {
        rc = sqlite3_exec(db, query, 0, 0, &err_msg);
        auto_inc = sqlite3_last_insert_rowid(db);
        sqlite3_close(db);
        int *p = &auto_inc;
        return p;
    }
    return NULL;
}
