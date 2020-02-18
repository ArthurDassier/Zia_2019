/*
** EPITECH PROJECT, 2020
** SSLModule
** File description:
** SSLModule
*/

#include "SSLModule.hpp"

extern "C" oZ::ModulePtr CreateModule(int client) { return std::make_shared<SSLModule>(client); }

void SSLModule::onRegisterCallbacks(oZ::Pipeline &pipeline)
{
    pipeline.registerCallback(
        oZ::State::Parse,
        oZ::Priority::ASAP,
        this, &SSLModule::WriteSSL
    );
}

void configure_context(SSL_CTX *ctx)
{
    SSL_CTX_set_ecdh_auto(ctx, 1);

    /* Set the key and cert */
    if (SSL_CTX_use_certificate_file(ctx, "./certificates/cert.pem", SSL_FILETYPE_PEM) <= 0)
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, "./certificates/key.pem", SSL_FILETYPE_PEM) <= 0)
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
}

SSL_CTX *create_context()
{
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    method = SSLv23_server_method();

    ctx = SSL_CTX_new(method);
    if (!ctx)
    {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    return ctx;
}

SSLModule::SSLModule(int client):
    _client(client)
{
    // const SSL_METHOD *method;

    SSL_load_error_strings();	
    OpenSSL_add_ssl_algorithms();
    // method = SSLv23_server_method();

    // std::cout << "Client = " << client << std::endl;

    // _ctx = SSL_CTX_new(method);
    _ctx = create_context();
    // if (!_ctx) {
    //     std::cout << "COUCOU" << std::endl;
    //     perror("Unable to create SSL context");
    //     ERR_print_errors_fp(stderr);
    //     exit(83);
    // }
    // SSL_CTX_set_ecdh_auto(_ctx, 1);
    // if (SSL_CTX_use_certificate_file(_ctx, "./certificates/cert.pem", SSL_FILETYPE_PEM) <= 0) {
    //     ERR_print_errors_fp(stderr);
    //     exit(85);
    // }

    // if (SSL_CTX_use_PrivateKey_file(_ctx, "./certificates/key.pem", SSL_FILETYPE_PEM) <= 0) {
    //     ERR_print_errors_fp(stderr);
    //     exit(86);
    // }
    configure_context(_ctx);
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

bool SSLModule::WriteSSL(oZ::Context &context)
{
    std::string reply;
    // reply += context.getResponse().getHeader().get(0);
    std :: cout << "Reply headers ======> " << reply << std::endl;
    reply += context.getResponse().getBody();
    if (SSL_accept(_ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        return false;
    } else {
        SSL_write(_ssl, reply.c_str(), strlen(reply.c_str()));
        return true;
    }
}