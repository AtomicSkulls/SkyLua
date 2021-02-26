#pragma once

#include "../lua_common.h"
#include <PCH.h>

namespace SkyLua
{
	namespace Classes
	{
		namespace Player
		{
			int lua_destructor(lua_State* l);
			int lua_registerclass(lua_State* l);

			const luaL_Reg regs[] =
			{
				{ "__gc", lua_destructor },
				{ NULL, NULL }
			};
		}

		struct LuaPlayer
		{
			LuaPlayer(RE::PlayerCharacter* pPlayer)
			{
				m_pPlayer = pPlayer;
			}

			RE::PlayerCharacter* m_pPlayer;
		};
	}
}