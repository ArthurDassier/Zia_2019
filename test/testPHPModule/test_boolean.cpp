#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include <modules/parser/ParserModule.hpp>
#include <server/ServerConfig.hpp>

using namespace ParserModule;

Test(Parser, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("../lib/modules/", "config_test/config_test_parser.json");
    std::string str = "GET / HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";

    oZ::ByteArray arr(str.size());

    // std::cout << "le packet recu : " << std::endl << str << std::endl;
    std::transform(str.begin(), str.end(), arr.begin(),
    [](char c)
    {
      return static_cast<char>(c);
    });

    oZ::Context context;
    context.getPacket().getByteArray() = arr;


    pipeline.loadModules();

    pipeline.runPipeline(context);


    cr_assert_eq(context.getRequest().getMethod(), oZ::HTTP::Method::Get);
}