#include "Player.h"


namespace SkyLua
{
	namespace Classes
	{
		namespace Player
		{
			int lua_destructor(lua_State* l)
			{
				LuaPlayer* obj = SkyLua::Util::lua_checkudata<LuaPlayer>(l, 1, "lua_player");
				delete obj;

				return 0;
			}

			int lua_registerclass(lua_State* l)
			{
				luaL_newmetatable(l, "lua_player");

				luaL_setfuncs(l, regs, 0);

				lua_pushvalue(l, -1);

				lua_setfield(l, -1, "__index");

				lua_pop(l, 1);

				return 0;
			}
		}
	}
}