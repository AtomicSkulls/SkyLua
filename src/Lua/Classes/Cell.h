#pragma once

#include "../lua_common.h"
#include <PCH.h>

namespace SkyLua
{
	namespace Classes
	{
		namespace Cell
		{
			int lua_destructor(lua_State* l);
			int lua_registerclass(lua_State* l);

			const luaL_Reg regs[] =
			{
				{ "__gc", lua_destructor },
				{ NULL, NULL }
			};
		}

		struct LuaCell 
		{
			LuaCell(RE::TESObjectCELL* pCell) 
			{
				m_pCell = pCell;
			}

			RE::TESObjectCELL* m_pCell;
		};
	}
}