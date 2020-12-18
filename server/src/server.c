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

void Servlet(SSL* ssl) {
    char buf[1024];
    char reply[1024];
    int sd, bytes;
    const char* answer = "echo: %s";

    if (SSL_accept(ssl) == -1)
        ERR_print_errors_fp(stderr);
    else {
        bytes = SSL_read(ssl, buf, sizeof(buf));
        if ( bytes > 0 ) {
            buf[bytes] = 0;
            printf("Client message: \"%s\"\n", buf);
            sprintf(reply, answer, buf);
            SSL_write(ssl, reply, strlen(reply));
        }
        else
            ERR_print_errors_fp(stderr);
    }
    sd = SSL_get_fd(ssl);
    SSL_free(ssl);
    close(sd);
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
        Servlet(ssl);
    }
    close(server);
    SSL_CTX_free(ctx);
}

int main() {
    int portnum = 4096;
    ssl_server(portnum);
}
