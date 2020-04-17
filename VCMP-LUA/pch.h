#ifndef PCH_H
#define PCH_H

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

#include <vcmp.h>
#include <SimpleIni.h>

extern "C" {
#include "lua/include/lua.h"
#include "lua/include/lualib.h"
#include "lua/include/lauxlib.h"
}

#include <LuaBridge/LuaBridge.h>

#ifdef WIN32
#include <Windows.h>
#pragma comment(lib, "lua/liblua53.a")
#endif

#endif //PCH_H
