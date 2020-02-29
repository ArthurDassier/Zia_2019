#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include <modules/parser/ParserModule.hpp>
#include <openZia/IModule.hpp>

using namespace ParserModule;

Test(Parser, StdOut, .init=cr_redirect_stdout)
{
    cr_assert_eq(true, true);
}