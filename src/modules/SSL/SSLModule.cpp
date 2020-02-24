/*
** EPITECH PROJECT, 2020
** SSLModule
** File description:
** SSLModule
*/

#include "SSLModule.hpp"

extern "C" oZ::ModulePtr CreateModule(void) { return std::make_shared<SSLModule>(); }

void SSLModule::onRegisterCallbacks(oZ::Pipeline &pipeline)
{
    std::cout << "=> SSLcallback" << std::endl;
    pipeline.registerCallback(
        oZ::State::AfterInterpret,
        oZ::Priority::ASAP,
        this, &SSLModule::WriteSSL
    );
}

void SSLModule::InitSSLModule(int client)
{
    _client = client;
    SSL_load_error_strings();	
    OpenSSL_add_ssl_algorithms();
    _ctx = this->create_context();

    this->configure_context(_ctx);
    _ssl = SSL_new(_ctx);

    SSL_set_fd(_ssl, _client);
}

SSLModule::~SSLModule()
{
    SSL_shutdown(_ssl);
    SSL_free(_ssl);
    SSL_CTX_free(_ctx);
    EVP_cleanup();
}

int create_socket(int port)
{
    int s;
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("Unable to create socket");
        exit(1);
    }

    if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Unable to bind");
        exit(1);
    }

    if (listen(s, 1) < 0) {
        perror("Unable to listen");
        exit(1);
    }

    return s;
}

void init_openssl()
{ 
    SSL_load_error_strings();	
    OpenSSL_add_ssl_algorithms();
}

void cleanup_openssl()
{
    EVP_cleanup();
}

SSL_CTX *create_context()
{
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    method = SSLv23_server_method();

    ctx = SSL_CTX_new(method);
    if (!ctx) {
	perror("Unable to create SSL context");
	ERR_print_errors_fp(stderr);
	exit(1);
    }

    return ctx;
}

void configure_context(SSL_CTX *ctx)
{
    SSL_CTX_set_ecdh_auto(ctx, 1);

    /* Set the key and cert */
    if (SSL_CTX_use_certificate_file(ctx, "cert.pem", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
	exit(1);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, "key.pem", SSL_FILETYPE_PEM) <= 0 ) {
        ERR_print_errors_fp(stderr);
	exit(1);
    }
}

bool SSLModule::WriteSSL(oZ::Context &context)
{
    std::cout << "Je suis le module SSL" << std::endl;

    std::string response(
        "HTTP/"
        + std::to_string(context.getResponse().getVersion().majorVersion)
        + "."
        + std::to_string(context.getResponse().getVersion().minorVersion) 
        + " "
        + std::to_string(static_cast<int>(context.getResponse().getCode())) 
        + " " 
        + context.getResponse().getReason() + "\n"
        + "Content-Length: " + context.getResponse().getHeader().get("Content-Length") + "\n"
        + "Content-Type: " + context.getResponse().getHeader().get("Content-Type") + "\n\n"
        + context.getResponse().getBody()
    );

    int sock;
    SSL_CTX *ctx;

    init_openssl();
    ctx = create_context();

    configure_context(ctx);

    sock = create_socket(4433);

    struct sockaddr_in addr;
    uint len = sizeof(addr);
    SSL *ssl;

    int client = accept(sock, (struct sockaddr*)&addr, &len);
    if (client < 0) {
        perror("Unable to accept");
        exit(1);
    }

    if (SSL_accept(_ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        return false;
    } else {
        SSL_write(_ssl, response.c_str(), strlen(response.c_str()));
        close(client);
        close(sock);
        return true;
    }
    return true;
}

void SSLModule::configure_context(SSL_CTX *ctx)
{
    SSL_CTX_set_ecdh_auto(ctx, 1);

    if (SSL_CTX_use_certificate_file(ctx, "./src/modules/SSL/cert.pem", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, "./src/modules/SSL/key.pem", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
}

SSL_CTX *SSLModule::create_context(void)
{
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    method = SSLv23_server_method();

    ctx = SSL_CTX_new(method);
    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    return ctx;
}
