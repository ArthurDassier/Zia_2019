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
    pipeline.registerCallback(
        oZ::State::BeforeParse,
        oZ::Priority::ASAP,
        this, &SSLModule::ReadSSL
    );
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
        // std::cout << "NOT HTTPS" << std::endl;
        return true;
    }
    int client = context.getPacket().getFileDescriptor();
    int ret = 0;

    std::cout << "IS HTTPS" << std::endl;
    if (context.getRequest().getURI() == "")
        exit(0);
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
    SSL_write(_sslMap[client], response.c_str(), strlen(response.c_str()));
    return true;
}

bool SSLModule::ReadSSL(oZ::Context &context)
{

    if (!(context.getPacket().hasEncryption())) {
        std::cout << "NOT HTTPS" << std::endl;
        return true;
    }

    const std::size_t readSize = 1024;
    std::size_t len = 0;
    std::string content;

    auto *ssl = _sslMap[context.getPacket().getFileDescriptor()];

    if (!ssl)
        return false;

    while (true) {

        char buff[readSize + 1] = {0};
        std::size_t recv = SSL_read(ssl, buff, readSize);

        if (SSL_get_error(ssl, recv) == SSL_ERROR_WANT_READ) {
            std::cout << std::endl << "SSL: closing the ssl" << std::endl;
            exit (0);
//            return false;
        }

        if (recv <= 0)
            break;
        buff[recv] = 0;

        try {
            content.append(buff, recv);
        } catch (const std::exception &e) {
            std::cout << "ModuleSSL : error read" << std::endl;
            break;

        }
        len += recv;
        if (recv < readSize)
            break;
    }

    std::string str(content.data());

    oZ::ByteArray arr(str.size());

    // std::cout << "le packet recu : " << std::endl << str << std::endl;
    std::transform(str.begin(), str.end(), arr.begin(),
    [](char c)
    {
      return static_cast<char>(c);
    });

    context.getPacket().getByteArray() = arr;
    
    // std::cout << "~~~~~" << content << std::endl;

    return true;
}