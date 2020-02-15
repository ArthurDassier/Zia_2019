/* --- Hello.cpp --- */
#include "Hello.hpp"

extern "C" oZ::IModule *CreateModule(void) { return new Hello(); }