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

void *async_conn(void *args_get) {
    struct async_args *args = args_get;
    SSL *ssl = SSL_new(args->ctx);
    SSL_set_fd(ssl, args-> client);
    requests_handler(ssl);
    pthread_exit(NULL);
    return NULL;
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

        int client = accept(server, (struct sockaddr*)&addr, &len);
        // printf("Connection: %s:%d\n",inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

        struct async_args args;
        args.ctx = ctx;
        args.client = client;
        pthread_t ssl_thread = NULL;
        pthread_create(&ssl_thread, NULL, async_conn, (void*)&args);
    }
    close(server);
    SSL_CTX_free(ctx);
}

// static void *display_running() {
//     char load[] = "\\|/-";
//     int i = 0, msec = 0;
//     long sec = 0, min = 0, hour = 0;
//     mx_printstr("\033[1;33mNOTE: \033[33mPress \033[1;33mCtrl+C \033[33mto exit\033[0m\n");
//     while (true) {
//         if (i == 4)
//             i = 0;
//         if (++msec % 5 == 0)
//             msec = 0, sec++;
//         if (sec == 60)
//             sec = 0, min++;
//         if (min == 60)
//             min = 0, hour++;
//         mx_printstr("\r\033[32mServer is running \033[35m");
//         if (hour > 0) {
//             mx_printint(hour);
//             mx_printstr(" h. ");
//         }
//         if (min > 0) {
//             mx_printint(min);
//             mx_printstr(" m. ");
//         }
//         mx_printint(sec);
//         mx_printstr(" s. \033[36m");
//         mx_printchar(load[i++]);
//         mx_printstr("\033[0m  ");
//         usleep(200000);
//     }
//     return NULL;
// }

static void daemonize() {
    pid_t pid;
    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);
    if (pid > 0)
        exit(EXIT_SUCCESS);
    if (setsid() < 0)
        exit(EXIT_FAILURE);
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);
    if (pid > 0)
        exit(EXIT_SUCCESS);
    umask(0);

    int uchat_pid = getpid();
    printf("\033[32muchat_server started successfully\033[0m\n");
    printf("\033[36muchat_server pid: \033[0m%d\n", uchat_pid);
    printf("\033[1;33mTo \033[1;31mSTOP \033[1;33muchat_server: \033[0mkill %d\n", uchat_pid);
    printf("\033[1;33mIf you lost uchat_server pid:\033[0m ps -ax | grep uchat_server\n");
    for (int x = sysconf(_SC_OPEN_MAX); x >= 0; x--)
        close(x);
}

int main(int argc, char *argv[]) {
    // pthread_t display_thread = NULL;
    // pthread_create(&display_thread, NULL, display_running, NULL);
    if (argc != 2) {
        fprintf(stderr, "usage : ./uchat_server [port]\n");
        exit(EXIT_FAILURE);
    }
    daemonize();
    int portnum = atoi(argv[1]);
    ssl_server(portnum);
}
