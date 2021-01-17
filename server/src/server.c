#include "../inc/server.h"

int OpenListener(int port) {
    int sd;
    struct sockaddr_in addr;

    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 ) {
        perror("can't bind port");
        abort();
    }
    if ( listen(sd, 10) != 0 ) {
        perror("Can't configure listening port");
        abort();
    }
    return sd;
}

SSL_CTX* InitServerCTX(void) {
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    method = SSLv23_server_method();
    ctx = SSL_CTX_new(method);
    if ( ctx == NULL ) {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

void LoadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile) {
    if ( SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0 ) {
        ERR_print_errors_fp(stderr);
        abort();
    }
    if ( SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0 ) {
        ERR_print_errors_fp(stderr);
        abort();
    }
    if ( !SSL_CTX_check_private_key(ctx) ) {
        fprintf(stderr, "Private key does not match the public certificate\n");
        abort();
    }
}

void ssl_server(int portnum) {
    SSL_CTX *ctx;
    int server;

    SSL_library_init();

    ctx = InitServerCTX();
    LoadCertificates(ctx, "server/cert.crt", "server/key.key");
    server = OpenListener(portnum);
    while (true) {
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        SSL *ssl;

        int client = accept(server, (struct sockaddr*)&addr, &len);
        printf("Connection: %s:%d\n",inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, client);
        requests_handler(ssl);
    }
    close(server);
    SSL_CTX_free(ctx);
}

static void *display_running() {
    char load[] = "\\|/-";
    int i = 0, msec = 0;
    long sec = 0, min = 0, hour = 0;
    while (true) {
        if (i == 4)
            i = 0;
        if (++msec % 5 == 0)
            msec = 0, sec++;
        if (sec == 60)
            sec = 0, min++;
        if (min == 60)
            min = 0, hour++;
        mx_printstr("\r\x1b[32mServer is running \x1b[35m");
        if (min > 0) {
            mx_printint(min);
            mx_printstr(" m. ");
        }
        if (hour > 0) {
            mx_printint(hour);
            mx_printstr(" h. ");
        }
        mx_printint(sec);
        mx_printstr(" s. \x1b[36m");
        mx_printchar(load[i++]);
        mx_printstr("\x1b[0m");
        usleep(200000);
    }
    return NULL;
}

int main() {
    pthread_t display_thread = NULL;
    pthread_create(&display_thread, NULL, display_running, NULL);
    int portnum = 10000;
    ssl_server(portnum);
}
