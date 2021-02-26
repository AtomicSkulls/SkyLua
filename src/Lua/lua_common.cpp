#include "lua_common.h"

namespace SkyLua {
	namespace Standalones {

		int lua_getcurtime(lua_State* L) 
		{
			clock_t t = clock();
			double ms = t / (CLOCKS_PER_SEC / 1000);

			lua_pushnumber(L, ms);

			return 1;
		}
	}

	namespace Util 
	{
		namespace Tables 
		{
			void lua_pushkv_str_str(lua_State* L, const char* key, const char* value) {
				lua_pushstring(L, key);
				lua_pushstring(L, value);
				lua_settable(L, -3);
			}

			void lua_pushkv_str_int(lua_State* L, const char* key, int value) {
				lua_pushstring(L, key);
				lua_pushnumber(L, value);
				lua_settable(L, -3);
			}
		}

		void LoadLuaFiles(lua_State* l, const char* path)
		{
			try {
				for (const auto& entry : std::filesystem::directory_iterator(path))
				{
					const auto p = entry.path();

					luaL_dofile(l, p.string().c_str());
				}
			}
			catch (...) {
			
			}
		}
	}


	namespace Thinking
	{
		void New(int milliseconds, std::function<void(void)> callback) {
			std::thread([&]
			{
				while (true)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));

					callback();
				}
			}).detach();
		}
	}
}

namespace SkyLua 
{
	namespace Libs
	{
		namespace Hooking
		{
			Hooks& GetAllHooks()
			{
				static Hooks reg;
				return reg;
			}

			HookFuncs& GetHooks(std::string eventID)
			{
				static Hooks reg;
				return reg[eventID];
			}

			int add(lua_State* L) {
				const char* event_ID = luaL_checkstring(L, 1);
				const char* hook_ID = luaL_checkstring(L, 2);

				bool func = lua_isfunction(L, 3);

				if (event_ID == NULL || hook_ID == NULL || !func) {
					luaL_error(L, "incorrect arguments");
				}

				lua_pushvalue(L, 3); // copy the function;

				int index = luaL_ref(L, LUA_REGISTRYINDEX);

				Hooks& table = GetAllHooks();
				HookFuncs& sub = table[event_ID];

				sub[hook_ID] = index;

				return 0;
			}

			int remove(lua_State* L)
			{
				const char* event_ID = luaL_checkstring(L, 1);
				const char* hook_ID = luaL_checkstring(L, 2);

				if (event_ID == NULL || hook_ID == NULL) {
					luaL_error(L, "incorrect arguments");
				}

				Hooks& table = GetAllHooks();

				if (table.contains(event_ID) && table[event_ID].contains(hook_ID)) {
					int r = table[event_ID][hook_ID];

					luaL_unref(L, LUA_REGISTRYINDEX, r);

					table[event_ID].erase(hook_ID);

					lua_pushboolean(L, true); // operation succeeded 
				}
				else
				{
					lua_pushboolean(L, false); // operation failed
				}

				return 1;
			}

			int registerLib(lua_State* l)
			{
				luaL_newlib(l, lib);
				lua_setglobal(l, "hook");

				return 1;
			}

			int lua_gethooks(lua_State* l)
			{
				lua_newtable(l); // 1

				for (auto const& x : GetAllHooks())
				{
					lua_pushstring(l, x.first.c_str()); // 2 (key)	
					lua_newtable(l); // 3 (value)

					for (auto const& y : x.second)
					{
						lua_pushstring(l, y.first.c_str()); // 4 (key)
						lua_rawgeti(l, LUA_REGISTRYINDEX, y.second); // 5 (value)
						lua_settable(l, -3);
					}

					lua_settable(l, 1);
				}

				return 1;
			}

			void call(lua_State* l, std::string eventID, std::function<int(lua_State*)> pusher)
			{
				Hooks& table = GetAllHooks();

				if (!table.contains(eventID))
				{
					return;
				}

				HookFuncs& sub = table[eventID];

				for (auto const& y : sub)
				{
					/*
					auto func = lua_rawgeti(l, LUA_REGISTRYINDEX, y.second);

					if (func)
					{
						int nArgs = pusher(l); // the function must push the arguments to lua_State and return the number of them
						lua_pcall(l, nArgs, 0, 0);
					}
					*/

					lua_rawgeti(l, LUA_REGISTRYINDEX, y.second);

				//	if (func)
				//	{
						int nArgs = pusher(l); // the function must push the arguments to lua_State and return the number of them
						lua_pcall(l, nArgs, 0, 0);
				//	}
				}

			}
		}
	}
}