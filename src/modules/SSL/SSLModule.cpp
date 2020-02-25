/*
** EPITECH PROJECT, 2020
** SSLModule
** File description:
** SSLModule
*/

#include "SSLModule.hpp"

OPEN_ZIA_MAKE_ENTRY_POINT(SSLModule)

SSLModule::~SSLModule()
{
    // SSL_shutdown(_ssl);
    // SSL_free(_ssl);
    // SSL_CTX_free(_ctx);
    // EVP_cleanup();
}

void SSLModule::onRegisterCallbacks(oZ::Pipeline &pipeline)
{
    std::cout << "=> SSLcallback" << std::endl;
    pipeline.registerCallback(
        oZ::State::AfterInterpret,
        oZ::Priority::ASAP,
        this, &SSLModule::WriteSSL
    );
}


void SSLModule::configure_context(void)
{
    SSL_CTX_set_ecdh_auto(_ctx, 1);

    if (SSL_CTX_use_certificate_file(_ctx, "./src/modules/SSL/cert.pem", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    if (SSL_CTX_use_PrivateKey_file(_ctx, "./src/modules/SSL/key.pem", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
}

void SSLModule::create_context(void)
{
    const SSL_METHOD *method;
    _ctx = nullptr;

    method = SSLv23_server_method();

    _ctx = SSL_CTX_new(method);
    if (!_ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
}

void SSLModule::InitSSLModule(int client)
{
    _client = client;
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
    this->create_context();
    this->configure_context();
    _ssl = SSL_new(_ctx);
    SSL_set_fd(_ssl, _client);
}

bool SSLModule::WriteSSL(oZ::Context &context)
{
    std::cout << "Je suis le module SSL2" << std::endl;

    int client = context.getPacket().getFileDescriptor();
    std::cout << "FD: " << context.getPacket().getFileDescriptor() << std::endl;
    InitSSLModule(client);
    std::string response(
        "HTTP/1.1 302 Ok\nContent-Length: 142\nContent-Type: text/html\n\n<!doctype html>\n<html>\n  <head>\n    <title>Titreee</title>\n  </head>\n\n  <body>\n    <p>Je suis le contenu de la page TEST</p>\n  </body>\n</html>"
    );
    int ret;
    if ((ret = SSL_accept(_ssl)) <= 0) {
        std::cout << "SSL ERROR: " << SSL_get_error(_ssl, ret) << std::endl;
        perror("");
        ERR_print_errors_fp(stdout);
        return false;
    } else {
        SSL_write(_ssl, response.c_str(), strlen(response.c_str()));
        return true;
    }
}

