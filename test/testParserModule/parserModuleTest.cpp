#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include <modules/parser/ParserModule.hpp>
#include <server/ServerConfig.hpp>

using namespace ParserModule;

Test(parser_method_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testParserModule/modules", "cc");
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

    cr_assert_eq(context.getRequest().getMethod(), oZ::HTTP::Method::Get);
}

Test(parser_method_neq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testParserModule/modules", "cc");
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

    cr_assert_neq(context.getRequest().getMethod(), oZ::HTTP::Method::Post);
}

Test(parser_url_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testParserModule/modules", "cc");
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

    cr_assert_eq(context.getRequest().getURI(), "/");
}

Test(parser_url_neq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testParserModule/modules", "cc");
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

    cr_assert_neq(context.getRequest().getURI(), "/blblblb");
}

Test(parser_minor_version_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testParserModule/modules", "cc");
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
    oZ::HTTP::Version v;
    v.majorVersion = 1;
    v.minorVersion = 1;
    context.getRequest().setVersion(v);

    cr_assert_eq(context.getRequest().getVersion().minorVersion, v.minorVersion);
}

Test(parser_minor_version_neq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testParserModule/modules", "cc");
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
    oZ::HTTP::Version v;
    v.majorVersion = 1;
    v.minorVersion = 1;
    context.getRequest().setVersion(v);
    v.minorVersion = 2;

    cr_assert_neq(context.getRequest().getVersion().minorVersion, v.minorVersion);
}

Test(parser_major_version_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testParserModule/modules", "cc");
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
    oZ::HTTP::Version v;
    v.majorVersion = 1;
    v.minorVersion = 1;
    context.getRequest().setVersion(v);

    cr_assert_eq(context.getRequest().getVersion().majorVersion, v.majorVersion);
}

Test(parser_major_version_neq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testParserModule/modules", "cc");
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
    oZ::HTTP::Version v;
    v.majorVersion = 1;
    v.minorVersion = 1;
    context.getRequest().setVersion(v);
    v.majorVersion = 2;

    cr_assert_neq(context.getRequest().getVersion().majorVersion, v.majorVersion);
}

Test(parser_header_content_1_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testParserModule/modules", "cc");
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

    cr_assert_eq(context.getRequest().getHeader().get("User-Agent"), "Mozilla/4.0 (compatible; MSIE5.01; Windows NT)");
}

Test(parser_header_content_1_neq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testParserModule/modules", "cc");
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

    cr_assert_neq(context.getRequest().getHeader().get("User-Agent"), "Mozilla/1.0 (compatible; MSIE5.01; Windows NT)");
}

Test(parser_header_content_2_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testParserModule/modules", "cc");
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

    cr_assert_eq(context.getRequest().getHeader().get("Accept-Language"), "en-us");
}

Test(parser_header_content_2_neq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testParserModule/modules", "cc");
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

    cr_assert_neq(context.getRequest().getHeader().get("Accept-Language"), "fr");
}

Test(parser_header_content_3_eq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testParserModule/modules", "cc");
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

    cr_assert_eq(context.getRequest().getHeader().get("Connection"), "Keep-Alive");
}

Test(parser_header_content_3_neq_good, StdOut, .init=cr_redirect_stdout)
{
    oZ::Pipeline pipeline("testParserModule/modules", "cc");
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

    cr_assert_neq(context.getRequest().getHeader().get("Connection"), "Dont-Keep-Alive");
}