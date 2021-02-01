#include "../inc/client.h"

int OpenConnection(const char *hostname, int port) {
    int sd;
    struct hostent *host;
    struct sockaddr_in addr;

    if ((host = gethostbyname(hostname)) == NULL) {
        perror(hostname);
        abort();
    }
    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(long*)(host->h_addr);
    if (connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
        close(sd);
        perror(hostname);
        abort();
    }
    return sd;
}

SSL_CTX* InitCTX(void) {
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    method = SSLv23_client_method();
    ctx = SSL_CTX_new(method);
    if (ctx == NULL) {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

int ssl_client(char *message, char **response) {
    SSL_CTX *ctx;
    int server;
    SSL *ssl;
    char buf[4096];
    int bytes;

    char *host = getenv("UCHAT_HOST");
    int port = atoi(getenv("UCHAT_PORT"));
    // int fd = socket(AF_INET, SOCK_STREAM, 0);
    // struct timeval tv;

    // tv.tv_sec = 2; // 2 seconds
    // tv.tv_usec = 0;

    SSL_library_init();

    ctx = InitCTX();
    server = OpenConnection(host, port);
    ssl = SSL_new(ctx);
    SSL_set_mode(ssl, SSL_MODE_ASYNC);
    SSL_set_fd(ssl, server);
    if (SSL_connect(ssl) == -1)
        ERR_print_errors_fp(stderr);
    else {
        // printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
        SSL_write(ssl, message, strlen(message));
        bytes = SSL_read(ssl, buf, sizeof(buf) - 1);
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
                *response = strdup(buf_alloc);
                mx_strdel(&buf_alloc);
            }
            else
                ERR_print_errors_fp(stderr);
        }
        else {
            *response = strdup(buf);
        }
        SSL_free(ssl);
    }
    close(server);
    SSL_CTX_free(ctx);

    return EXIT_SUCCESS;
}
