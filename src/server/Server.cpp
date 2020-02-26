/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Server
*/

#include <iostream>
#include "Server.hpp"
#include "Log.hpp"
#include <boost/asio.hpp>
#include <vector>
#include <iterator>

using namespace Zia;

Server::Server(const std::string &ip, int port,
std::string &&modules, std::string &&configs)
:
    _pipeline(std::move(modules), std::move(configs)),
    _configManager("./config"),
    _socket(_io_service),
    _acceptor(_io_service),
    _acceptorHTTPS(_io_service),
    _signals(_io_service),
    _ip(ip),
    _port(port)
{
    _signals.add(SIGINT);
    _signals.add(SIGTERM);
#if defined(SIGQUIT)
    _signals.add(SIGQUIT);
#endif // defined(SIGQUIT)

    ManagingSignals();

    boost::asio::ip::tcp::resolver resolver(_io_service);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve({ip, std::to_string(port)});
    _acceptor.open(endpoint.protocol());
    _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    _acceptor.bind(endpoint);
    _acceptor.listen();

    boost::asio::ip::tcp::endpoint endpoint2 = *resolver.resolve({ip, std::to_string(DefaultPortHTTPS)});
    _acceptorHTTPS.open(endpoint2.protocol());
    _acceptorHTTPS.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    _acceptorHTTPS.bind(endpoint2);
    _acceptorHTTPS.listen();

    std::filesystem::directory_entry de;
    std::filesystem::path config_path("config/server_config.json");
    de.assign(config_path);

    auto config = _configManager.getConfig("server_config");
    _serverConfig = ConfigPtr(new ServerConfig(config->getFileDescriptor(), config->getName()));
    _serverConfig->loadConfig(_serverConfig->getPath());

    addEnabledModules(_serverConfig->getEnabledModulesList());

    _configManager.onConfigChange([this]() {
        _serverConfig->loadConfig(_serverConfig->getPath());
        addEnabledModules(_serverConfig->getEnabledModulesList());
    });
    _configManager.manage();

    std::cout << "Number of modules loaded: " << _pipeline.getModules().size() << std::endl;

    WaitingClient();

    Log::info("Server Started\n> IP\t" + _ip + "\n> Port\t" + std::to_string(_port));
}

void Server::run()
{
    _io_service.run();
}

void Server::close()
{
    _connectionManager.eraseAll();
    Log::info("Server closed");
}

void Server::WaitingClient()
{
    _acceptor.async_accept(_socket, [this](boost::system::error_code error) {
        if (!_acceptor.is_open())
            return;
        if (!error)
        {
            _connectionManager.addClient(std::make_shared<Connection>(
                std::move(_socket), _connectionManager, _pipeline
            ));
        }
        WaitingClient();
        std::cout << _configManager.getConfig("config")->getName() << ": " << _configManager.getConfig("config")->getPath() << std::endl;
    });
    _acceptorHTTPS.async_accept(_socket, [this](boost::system::error_code error)
    {
        if (!_acceptorHTTPS.is_open())
            return;
        if (!error) {
            _connectionManager.addClient(std::make_shared<Connection>(
                std::move(_socket), _connectionManager, _pipeline
            ));
        }
        WaitingClient();
    });
}

void Server::ManagingSignals()
{
    _signals.async_wait([this](boost::system::error_code, int)
    {
        _connectionManager.eraseAll();
        _acceptor.close();
        _acceptorHTTPS.close();
    });
}

void Server::addEnabledModules(const EnabledList &modulesList)
{
    for (auto &module : modulesList) {
        std::filesystem::copy(module->getPath(), std::getenv("TMP_MODULES_PATH"),
            std::filesystem::copy_options::skip_existing);
    }
    _pipeline.loadModules();
}