#include "../inc/client.h"

int ssl_client_alloc_len(char *message, char **response) {
    SSL_CTX *ctx;
    int server;
    SSL *ssl;
    char buf[4096];
    int bytes;
    char *host = getenv("UCHAT_HOST");
    int port = atoi(getenv("UCHAT_PORT"));

    SSL_library_init();

    ctx = InitCTX();
    server = OpenConnection(host, port);
    ssl = SSL_new(ctx);
    SSL_set_mode(ssl, SSL_MODE_ASYNC);
    SSL_set_fd(ssl, server);
    if (SSL_connect(ssl) == -1)
        ERR_print_errors_fp(stderr);
    else {
        int len = strlen(message);
        char *len_str = mx_itoa(len);
        SSL_write(ssl, len_str, strlen(len_str));
        SSL_read(ssl, buf, sizeof(buf));
        SSL_write(ssl, message, len);
        bytes = SSL_read(ssl, buf, sizeof(buf));
        buf[bytes] = 0;
        // printf("Received: \"%s\"\n", buf);
        mx_strdel(&len_str);
        SSL_free(ssl);
    }
    close(server);
    SSL_CTX_free(ctx);

    *response = strdup(buf);

    return EXIT_SUCCESS;
}
