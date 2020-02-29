#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include <modules/fillPage/FillPage.hpp>
#include <server/ServerConfig.hpp>

Test(fill_minor_version_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testFillModule/modules", "cc");
    std::string str = "GET / HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
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

Test(fill_minor_version_neq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testFillModule/modules", "cc");
    std::string str = "GET / HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
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

Test(fill_major_version_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testFillModule/modules", "cc");
    std::string str = "GET / HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
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

Test(fill_major_version_neq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testFillModule/modules", "cc");
    std::string str = "GET / HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
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

Test(fill_code_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testFillModule/modules", "cc");
    std::string str = "GET / HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
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

Test(fill_code_neq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testFillModule/modules", "cc");
    std::string str = "GET / HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
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

Test(fill_reason_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testFillModule/modules", "cc");
    std::string str = "GET / HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
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

Test(fill_reason_neq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testFillModule/modules", "cc");
    std::string str = "GET / HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
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

Test(fill_content_length_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testFillModule/modules", "cc");
    std::string str = "GET / HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
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

Test(fill_content_type_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testFillModule/modules", "cc");
    std::string str = "GET / HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
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

Test(fill_content_type_neq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testFillModule/modules", "cc");
    std::string str = "GET / HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nAccept-Language: en-us\nConnection: Keep-Alive";
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