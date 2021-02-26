#pragma once

#include <lua.hpp>
#include <time.h> /* clock_t, clock, CLOCKS_PER_SEC */
#include <functional>
#include <thread>
#include <filesystem>

namespace SkyLua {
	namespace Standalones 
	{
		int lua_getcurtime(lua_State* L);
	}

	namespace Util 
	{
		template<typename T>
		void lua_pushobject(lua_State* L, T* pObj, const char* metatable)
		{
			T** ud = static_cast<T**>(lua_newuserdata(L, sizeof(T*)));
			*ud = pObj;

			luaL_getmetatable(L, metatable);
			lua_setmetatable(L, -2);
		}

		template<typename T>
		T* lua_checkudata(lua_State* L, int n, const char* mtname)
		{
			return *(T**)luaL_checkudata(L, n, mtname);
		}

		namespace Tables 
		{
			// pushes key-value: string(key) && string (value)
			void lua_pushkv_str_str(lua_State* L, const char* key, const char* value);
			void lua_pushkv_str_int(lua_State* L, const char* key, int value);

			void lua_pushkv_int_str(lua_State* L, int key, int value);
			// pushes key-value : int(key) && userdata(value)

			template<typename T>
			void lua_pushkv_int_ud(lua_State* L, int key, T* value, const char* metatable) {
				lua_pushinteger(L, key);
				lua_pushobject(L, value, metatable);
				lua_settable(L, -3);
			}

			// pushes key-value : string(key) && userdata(value)
			template<typename T>
			void lua_pushkv_str_ud(lua_State* L, const char* key, T* value, const char* metatable) {
				lua_pushstring(L, key);
				lua_pushobject(L, value, metatable);
				lua_settable(L, -3);
			}
		}

		void LoadLuaFiles(lua_State* l, const char* path);
	}

	namespace Thinking 
	{
		void New(int milliseconds, std::function<void(void)> callback);
	}

	class MetaNames
	{
	public:
		inline static const char* ACTOR = "Actor";
		inline static const char* CELL = "Cell";
		inline static const char* OBJREF = "ObjectReference";
		inline static const char* PLAYER = "Player";
		inline static const char* VECTOR = "Vector";
	};
}

namespace SkyLua 
{
	namespace Libs 
	{
		namespace Hooking
		{
			typedef std::unordered_map<std::string, int> HookFuncs;
			typedef std::unordered_map<std::string, HookFuncs> Hooks;

			Hooks& GetAllHooks();
			HookFuncs& GetHooks(std::string eventID);

			int add(lua_State* l);
			int remove(lua_State* l);

			void call(lua_State* l, std::string eventID, std::function<int(lua_State*)> pusher);

			int lua_gethooks(lua_State* l);
			int registerLib(lua_State* l);

			static const struct luaL_Reg lib[] = {
				{ "GetTable", lua_gethooks},
				{ "Add", add },
				{ "Remove", remove },
				{ NULL, NULL }
			};
		}
	}
}