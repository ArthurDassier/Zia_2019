//
// connection.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "connection.hpp"
#include <utility>
#include <vector>
#include "connection_manager.hpp"
#include "request_handler.hpp"
#include <iostream>

namespace http {
namespace server {

connection::connection(boost::asio::ip::tcp::socket socket,
    connection_manager& manager, request_handler& handler,
    oZ::Pipeline &pipeline):
    socket_(std::move(socket)),
    connection_manager_(manager),
    request_handler_(handler),
    _pipeline(pipeline)
{
}

void connection::start()
{
  do_read();
}

void connection::stop()
{
  socket_.close();
}

void connection::do_read()
{
  auto self(shared_from_this());
  socket_.async_read_some(boost::asio::buffer(buffer_),
      [this, self](boost::system::error_code ec, std::size_t bytes_transferred)
      {
        if (!ec)
        {
          runPipeline();
        }
        else if (ec != boost::asio::error::operation_aborted)
        {
          connection_manager_.stop(shared_from_this());
        }
      });
}

void connection::runPipeline(void)
{
    std::string str(buffer_.data());

    oZ::ByteArray arr(str.size());

    std::transform(str.begin(), str.end(), arr.begin(),
    [](char c)
    {
      return static_cast<char>(c);
    });

    oZ::Packet packet(std::move(arr), oZ::Endpoint(socket_.remote_endpoint().address().to_string(), socket_.remote_endpoint().port()));
    oZ::Context context(std::move(packet));
    _pipeline.runPipeline(context);
    do_write(std::move(context));
}

void connection::do_write(oZ::Context &&context)
{
  auto self(shared_from_this());

  std::string response(
        "HTTP/" +
        std::to_string(context.getResponse().getVersion().majorVersion) +
        "." +
        std::to_string(context.getResponse().getVersion().minorVersion) +
        " " +
        std::to_string(static_cast<int>(context.getResponse().getCode())) +
        " " +
        context.getResponse().getReason() +
        "\n"
    );

  boost::asio::async_write(socket_, boost::asio::buffer(response),
      [this, self](boost::system::error_code ec, std::size_t)
      {
        if (!ec)
        {
          // Initiate graceful connection closure.
          boost::system::error_code ignored_ec;
          socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
            ignored_ec);
        }

        if (ec != boost::asio::error::operation_aborted)
        {
          connection_manager_.stop(shared_from_this());
        }
      });
}

} // namespace server
} // namespace http