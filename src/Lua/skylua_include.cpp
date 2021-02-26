#include "skylua_include.h"

namespace SkyLua {
	void RegisterClasses(lua_State* l) {
		Classes::Actor::lua_registerclass(l);
		Classes::Cell::lua_registerclass(l);
		Classes::ObjectReference::lua_registerclass(l);
		Classes::Vector::lua_registerclass(l);
	}

	void RegisterGlobals(lua_State* l)
	{
		for (const auto& s : Libs::Refs::Filters) 
		{
			lua_pushnumber(l, s.first);
			lua_setglobal(l, s.second);
		}
	}

	void RegisterOverrides(lua_State* L)
	{
		static const struct luaL_Reg lib[] = {
		  {"print", Overrides::lua_print},
		  {NULL, NULL} /* end of array */
		};

		lua_getglobal(L, "_G");
		luaL_setfuncs(L, lib, 0);

		lua_pop(L, 1);
	}

	void RegisterStandalones(lua_State* L)
	{
		static const struct luaL_Reg lib[] = {
			{"CurTime", Standalones::lua_getcurtime},
			{"GetCellRefs", Standalones::lua_getGlobalCellRefs},
			{"GetPlayer", Standalones::lua_getPlayer},

			{NULL, NULL} /* end of array */
		};

		lua_getglobal(L, "_G");
		luaL_setfuncs(L, lib, 0);

		lua_pop(L, 1);
	}

	void RegisterHooks(lua_State* L)
	{
		Libs::Hooking::registerLib(L);
	}
}