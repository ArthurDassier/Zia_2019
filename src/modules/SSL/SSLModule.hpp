/*
** EPITECH PROJECT, 2020
** SSLModule
** File description:
** SSLModule
*/

#pragma once

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <stdlib.h>
#include <iostream>

#include <openZia/IModule.hpp>
#include <openZia/Pipeline.hpp>

class SSLModule : public oZ::IModule {
    public:

        SSLModule() = default;
        ~SSLModule();

        virtual const char *getName(void) const { return "TestModule"; }

        virtual void onRegisterCallbacks(oZ::Pipeline &pipeline);

        virtual void onLoadConfigurationFile(const std::string &);

        virtual void onConnection(const oZ::FileDescriptor fd, const oZ::Endpoint endpoint, const bool useEncryption);
        virtual void onDisconnection(const oZ::FileDescriptor fd, const oZ::Endpoint endpoint);

    private:

        bool WriteSSL(oZ::Context &context);
        bool AcceptSSL(oZ::Context &context);

        void configure_context(void);
        void create_context(void);

        void Init(void);

        std::map<int, SSL*> _sslMap;

        int _client = 0;
        SSL_CTX *_ctx = nullptr;
        SSL *_ssl = nullptr;
};