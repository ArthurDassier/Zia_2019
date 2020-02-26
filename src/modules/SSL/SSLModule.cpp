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
    // pipeline.registerCallback(
    //     oZ::State::BeforeParse,
    //     oZ::Priority::ASAP,
    //     this, &SSLModule::AcceptSSL
    // );
}

void SSLModule::onConnection(const oZ::FileDescriptor fd, const oZ::Endpoint endpoint, const bool useEncryption)
{
    if (useEncryption == true) {
        _sslMap[fd] = SSL_new(_ctx);
        if (!_sslMap[fd])
            return;

        SSL_set_fd(_sslMap[fd], fd);

        if (SSL_accept(_sslMap[fd]) < 0) {
            ERR_print_errors_fp(stdout);
            return;
        }
        std::cout << "connected" << std::endl;
    }
}

void SSLModule::onDisconnection(const oZ::FileDescriptor fd, const oZ::Endpoint endpoint)
{
    if (_sslMap[fd])
        SSL_free(_sslMap[fd]);
}

void SSLModule::onLoadConfigurationFile(const std::string &directory)
{
    Init();
}

void SSLModule::Init()
{

    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();

    create_context();
    configure_context();
    
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
    _ctx = SSL_CTX_new(SSLv23_server_method());
    if (!_ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
}

bool SSLModule::WriteSSL(oZ::Context &context)
{
    if (!(context.getPacket().hasEncryption())) {
        std::cout << "NOT HTTPS" << std::endl;
        return true;
    }
    int client = context.getPacket().getFileDescriptor();
    int ret = 0;

    std::cout << "IS HTTPS" << std::endl;
    std::string response(
        "HTTP/1.1 200 Ok\nContent-Length: 142\nContent-Type: text/html\n\n<!doctype html>\n<html>\n  <head>\n    <title>Titreee</title>\n  </head>\n\n  <body>\n    <p>Je suis le contenu de la page TEST</p>\n  </body>\n</html>"
    );
    if ((ret = SSL_accept(_sslMap[client])) <= 0) {
        std::cout << "SSL ERROR: " << SSL_get_error(_sslMap[client], ret) << std::endl;
        perror("");
        ERR_print_errors_fp(stdout);
        return false;
    } else {
        SSL_write(_sslMap[client], response.c_str(), strlen(response.c_str()));
        return true;
    }
}

bool SSLModule::AcceptSSL(oZ::Context &context)
{
    int ret = 0;

    if ((ret = SSL_accept(_ssl)) <= 0) {
        std::cout << "SSL ERROR: " << SSL_get_error(_ssl, ret) << std::endl;
        perror("");
        ERR_print_errors_fp(stdout);
        return false;
    }
    return true;
}