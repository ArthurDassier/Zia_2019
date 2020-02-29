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

/**
 * @brief SSLModule class to manage the SSL module.
 */
class SSLModule : public oZ::IModule {
    public:

        /**
         * @brief Default constructor for the ssl module
         */
        SSLModule() = default;

        /**
         * @brief Default destructor for the php module
         */
        ~SSLModule();

        /**
         * @brief Get the name of the module
         * 
         * @return The name of the module
         */
        virtual const char *getName(void) const { return "SSLModule"; }

        /**
         * @brief Fct for the pipeline (load in the right place in the right position)
         * 
         * @param pipeline Reference on the pipeline where the module is load
         */
        virtual void onRegisterCallbacks(oZ::Pipeline &pipeline);

        /**
         * @brief Load the conf for the pipeline
         * 
         * @param conf Conf for modif the pipeline
         */
        virtual void onLoadConfigurationFile(const std::string &conf);

        /**
         * @brief Init the ssl lib
         * 
         * @param fd Fd open for the listen
         * @param endpoint Endpoint use for the listen
         * @param useEncryption Bool to know if it's HTTP or HTTPS
         */
        virtual void onConnection(const oZ::FileDescriptor fd, const oZ::Endpoint endpoint, const bool useEncryption);

        /**
         * @brief Destroy the ssl lib
         * 
         * @param fd Fd close after the listen
         * @param endpoint Endpoint close after the listen
         */
        virtual void onDisconnection(const oZ::FileDescriptor fd, const oZ::Endpoint endpoint);

    private:

        /**
         * @brief Send the response packet with ssl encrypt
         * 
         * @param context Context given by the server
         * 
         * @return Bool to know if nothing wrong happened
         */
        bool WriteSSL(oZ::Context &context);

        /**
         * @brief Read from the browser with ssl
         * 
         * @param context Context given by the server
         * 
         * @return Bool to know if nothing wrong happened
         */
        bool ReadSSL(oZ::Context &context);

        /**
         * @brief Configure the context
         */
        void configure_context(void);

        /**
         * @brief Create the context
         */
        void create_context(void);

        /**
         * @brief Init the ssl module
         */
        void Init(void);

        std::string createResponse(const oZ::Context &context);

        std::map<int, SSL*> _sslMap;

        int _client = 0;
        SSL_CTX *_ctx = nullptr;
        SSL *_ssl = nullptr;
};