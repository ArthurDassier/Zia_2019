#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include <modules/PHP/PHPModule.hpp>
#include <server/ServerConfig.hpp>

Test(php_minor_version_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testPHPModule/modules", "cc");
    std::string str = "GET /php HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
    oZ::ByteArray arr(str.size());
    std::transform(str.begin(), str.end(), arr.begin(),
    [](char c)
    {
      return static_cast<char>(c);
    });
    oZ::Context context;

    context.getPacket().getByteArray() = arr;
    pipeline.loadModules();
    pipeline.runPipeline(context);


    cr_assert_eq(context.getResponse().getVersion().minorVersion, 1);
}

Test(php_minor_version_neq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testPHPModule/modules", "cc");
    std::string str = "GET /php HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
    oZ::ByteArray arr(str.size());
    std::transform(str.begin(), str.end(), arr.begin(),
    [](char c)
    {
      return static_cast<char>(c);
    });
    oZ::Context context;

    context.getPacket().getByteArray() = arr;
    pipeline.loadModules();
    pipeline.runPipeline(context);


    cr_assert_neq(context.getResponse().getVersion().minorVersion, 2);
}

Test(php_major_version_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testPHPModule/modules", "cc");
    std::string str = "GET /php HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
    oZ::ByteArray arr(str.size());
    std::transform(str.begin(), str.end(), arr.begin(),
    [](char c)
    {
      return static_cast<char>(c);
    });
    oZ::Context context;

    context.getPacket().getByteArray() = arr;
    pipeline.loadModules();
    pipeline.runPipeline(context);


    cr_assert_eq(context.getResponse().getVersion().majorVersion, 1);
}

Test(php_major_version_neq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testPHPModule/modules", "cc");
    std::string str = "GET /php HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
    oZ::ByteArray arr(str.size());
    std::transform(str.begin(), str.end(), arr.begin(),
    [](char c)
    {
      return static_cast<char>(c);
    });
    oZ::Context context;

    context.getPacket().getByteArray() = arr;
    pipeline.loadModules();
    pipeline.runPipeline(context);


    cr_assert_neq(context.getResponse().getVersion().majorVersion, 2);
}

Test(php_code_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testPHPModule/modules", "cc");
    std::string str = "GET /php HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
    oZ::ByteArray arr(str.size());
    std::transform(str.begin(), str.end(), arr.begin(),
    [](char c)
    {
      return static_cast<char>(c);
    });
    oZ::Context context;

    context.getPacket().getByteArray() = arr;
    pipeline.loadModules();
    pipeline.runPipeline(context);


    cr_assert_eq(context.getResponse().getCode(), oZ::HTTP::Code::OK);
}

Test(php_code_neq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testPHPModule/modules", "cc");
    std::string str = "GET /php HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
    oZ::ByteArray arr(str.size());
    std::transform(str.begin(), str.end(), arr.begin(),
    [](char c)
    {
      return static_cast<char>(c);
    });
    oZ::Context context;

    context.getPacket().getByteArray() = arr;
    pipeline.loadModules();
    pipeline.runPipeline(context);


    cr_assert_neq(context.getResponse().getCode(), oZ::HTTP::Code::BadRequest);
}

Test(php_reason_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testPHPModule/modules", "cc");
    std::string str = "GET /php HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
    oZ::ByteArray arr(str.size());
    std::transform(str.begin(), str.end(), arr.begin(),
    [](char c)
    {
      return static_cast<char>(c);
    });
    oZ::Context context;

    context.getPacket().getByteArray() = arr;
    pipeline.loadModules();
    pipeline.runPipeline(context);


    cr_assert_eq(context.getResponse().getReason(), "Ok");
}

Test(php_reason_neq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testPHPModule/modules", "cc");
    std::string str = "GET /php HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
    oZ::ByteArray arr(str.size());
    std::transform(str.begin(), str.end(), arr.begin(),
    [](char c)
    {
      return static_cast<char>(c);
    });
    oZ::Context context;

    context.getPacket().getByteArray() = arr;
    pipeline.loadModules();
    pipeline.runPipeline(context);


    cr_assert_neq(context.getResponse().getReason(), "KO");
}

Test(php_content_length_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testPHPModule/modules", "cc");
    std::string str = "GET /php HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
    oZ::ByteArray arr(str.size());
    std::transform(str.begin(), str.end(), arr.begin(),
    [](char c)
    {
      return static_cast<char>(c);
    });
    oZ::Context context;

    context.getPacket().getByteArray() = arr;
    pipeline.loadModules();
    pipeline.runPipeline(context);


    cr_assert_eq(context.getResponse().getHeader().get("Content-Length"), "0");
}

Test(php_content_type_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testPHPModule/modules", "cc");
    std::string str = "GET /php HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
    oZ::ByteArray arr(str.size());
    std::transform(str.begin(), str.end(), arr.begin(),
    [](char c)
    {
      return static_cast<char>(c);
    });
    oZ::Context context;

    context.getPacket().getByteArray() = arr;
    pipeline.loadModules();
    pipeline.runPipeline(context);


    cr_assert_eq(context.getResponse().getHeader().get("Content-Type"), "text/html");
}

Test(php_content_type_neq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testPHPModule/modules", "cc");
    std::string str = "GET /php HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
    oZ::ByteArray arr(str.size());
    std::transform(str.begin(), str.end(), arr.begin(),
    [](char c)
    {
      return static_cast<char>(c);
    });
    oZ::Context context;

    context.getPacket().getByteArray() = arr;
    pipeline.loadModules();
    pipeline.runPipeline(context);


    cr_assert_neq(context.getResponse().getHeader().get("Content-Type"), "text/css");
}

Test(php_body_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testPHPModule/modules", "cc");
    std::string str = "GET /php HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
    oZ::ByteArray arr(str.size());
    std::transform(str.begin(), str.end(), arr.begin(),
    [](char c)
    {
      return static_cast<char>(c);
    });
    oZ::Context context;

    context.getPacket().getByteArray() = arr;
    pipeline.loadModules();
    pipeline.runPipeline(context);


    cr_assert_eq(context.getResponse().getBody(), "");
}