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