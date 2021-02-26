#pragma once

#include "../lua_common.h"
#include <PCH.h>

// so we can construct a new lua objects
#include "Actor.h"
#include "Cell.h"
#include "Vector.h"

namespace SkyLua
{
	namespace Classes 
	{
		namespace ObjectReference
		{
			int lua_destructor(lua_State* l);
			int lua_registerclass(lua_State* l);

			int lua_disable(lua_State* l);

			int lua_getname(lua_State* l);
			int lua_getowner(lua_State* l);
			int lua_getposition(lua_State* l);
			int lua_getparentcell(lua_State* l);

			int lua_setposition(lua_State* l);

			int lua_iswater(lua_State* l);

			int lua_isactor(lua_State* l);
			int lua_asactor(lua_State* l);


			const luaL_Reg regs[] =
			{
				{ "__gc", lua_destructor },
				{ "Disable", lua_disable },
				{ "GetName", lua_getname },
				{ "GetOwner", lua_getowner },
				{ "GetPos", lua_getposition },
				{ "IsActor", lua_isactor },
				{ "Actor", lua_asactor },
				{ NULL, NULL }
			};
		}

		struct LuaObjRef {
			LuaObjRef(RE::TESObjectREFR* pRef)
			{
				m_pRef = pRef;
			}

			RE::TESObjectREFR* m_pRef;
		};
	}
}