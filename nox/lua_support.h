#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "texture.h"

#include <iostream>
#include <string>
#include "globals.h"

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

//GLM SUpport for LUA
int lua_HostSum(lua_State* L) {
	float a = lua_tonumber(L, 1);
	float b = lua_tonumber(L, 2);
	std::cout << "[CPP] Host Function called" << std::endl;
	float c = (a * a) + b;
	lua_pushnumber(L, c);

	return 1;
}

int lua_glUniform1f(lua_State* L) {
	float value = lua_tonumber(L, 2);
	std::string uniformName = lua_tostring(L, 1);
	glUniform1f(glGetUniformLocation(CURRENT_ACTIVE_OBJECT_SHADER_ID, uniformName.c_str()),value);
	return 1;
}

int lua_glUniform3f(lua_State* L) {
	float value1 = lua_tonumber(L, 2);
	float value2 = lua_tonumber(L, 3);
	float value3 = lua_tonumber(L, 4);
	std::string uniformName = lua_tostring(L, 1);
	glUniform3f(glGetUniformLocation(CURRENT_ACTIVE_OBJECT_SHADER_ID, uniformName.c_str()), value1,value2,value3);
	return 1;
}

int lua_setCameraToShader(lua_State* L) {
	std::string uniformName = lua_tostring(L, 1);
	glUniform3fv(glGetUniformLocation(CURRENT_ACTIVE_OBJECT_SHADER_ID, uniformName.c_str()), 1,glm::value_ptr(gCamera->position));
	return 1;
}

int lua_setTexture(lua_State* L) {
	std::string textureLocation = lua_tostring(L, 1);
	bool flip = lua_toboolean(L, 2);
	bool hasAlpha = lua_toboolean(L, 3);
	std::string textureName = lua_tostring(L, 4);
	int textureID = lua_tonumber(L, 5);
	Texture texture(textureLocation, flip, hasAlpha);
	texture.activate(CURRENT_ACTIVE_OBJECT_SHADER_ID, textureName, textureID);
	return 1;
}

void LuaSupport(std::string lua_script_location) {
	lua_State* L = luaL_newstate();//creating a Virtual Lua Machine
	luaL_openlibs(L);//opens basic lua libs
	lua_register(L, "HostSum", lua_HostSum);
	lua_register(L, "setUniform1f", lua_glUniform1f);
	lua_register(L, "setUniform3f", lua_glUniform3f);
	lua_register(L, "setCameraToShader", lua_setCameraToShader);
	lua_register(L, "setTexture", lua_setTexture);

	luaL_dofile(L, lua_script_location.c_str());

	//close LUA
	lua_close(L);
}

void LuaSupportTexture(std::string lua_texture_script_location) {
	lua_State* L = luaL_newstate();//creating a Virtual Lua Machine
	luaL_openlibs(L);//opens basic lua libs
	lua_register(L, "setTexture", lua_setTexture);

	luaL_dofile(L, lua_texture_script_location.c_str());

	//close LUA
	lua_close(L);
}