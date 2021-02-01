#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <netinet/in.h>
#include <sqlite3.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <malloc/malloc.h>
#include <arpa/inet.h>
#include <resolv.h>
#include "openssl/ssl.h"
#include "openssl/err.h"
#include "libmx.h"
#include "cJSON.h"
#include <sqlite3.h>

#define DB_NAME "database.db"
#define DB_TABLE_USERS "users"
#define DB_TABLE_CHATS "chats"
#define DB_TABLE_MESSAGES "messages"
#define DB_LIST     0x01
#define DB_LAST_ID  0x02
#define MEDIA_DIR   "media_server/"
#define TEMP_DIR    "temp/"

struct async_args {
    SSL_CTX *ctx;
    int client;
};

void requests_handler(SSL*);
void *sqlite3_exec_db(char *query, int type);
