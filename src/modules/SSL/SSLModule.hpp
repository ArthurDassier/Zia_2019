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

        SSLModule(int);
        ~SSLModule();
        
        virtual const char *getName(void) const { return "TestModule"; }

        virtual void onRegisterCallbacks(oZ::Pipeline &pipeline);

    private:

        bool WriteSSL(oZ::Context &context);

        void configure_context(SSL_CTX *);
        SSL_CTX *create_context(void);

        int _client;
        SSL_CTX *_ctx;
        SSL *_ssl;
};