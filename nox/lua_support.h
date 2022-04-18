#pragma once

#include <iostream>
#include <string>

extern "C" {
#include <lua/lua.h>
#include <lua/lauxlib.h>
#include <lua/lualib.h>
}

#pragma comment(lib,"liblua54.a")

bool CheckLua(lua_State* L, int r) {
	if (r != LUA_OK) {
		std::string errmsg = lua_tostring(L, -1);
		std::cout << errmsg << std::endl;
		return false;
	}
	return true;
}

int lua_HostSum(lua_State* L) {
	float a = lua_tonumber(L, 1);
	float b = lua_tonumber(L, 2);
	std::cout << "[CPP] Host Function called" << std::endl;
	float c = (a * a) + b;
	lua_pushnumber(L, c);

	return 1;
}

void LuaSupport() {
	lua_State* L = luaL_newstate();//creating a Virtual Lua Machine
	luaL_openlibs(L);//opens basic lua libs
	lua_register(L, "HostSum", lua_HostSum);



	if (CheckLua(L, luaL_dofile(L, "luaScript.lua"))) {
		lua_getglobal(L, "MathStuff");
		if (lua_isfunction(L, -1)) {
			lua_pushnumber(L, 3.13f);
			lua_pushnumber(L, 11.63f);

			if (CheckLua(L, lua_pcall(L, 2, 1, 0))) {
				std::cout << "[CPP] MathStuff: " << (float)lua_tonumber(L, -1) << std::endl;
			}
		}

		lua_getglobal(L, "changeTime");
		if (lua_isfunction(L, -1)) {
			lua_pushnumber(L, 393939);
			lua_pcall(L, 1, 0, 0);
		}
	}
	std::cout << "######" << std::endl;

	//close LUA
	lua_close(L);
}