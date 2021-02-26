#pragma once

#include "../lua_common.h"
#include <PCH.h>

#define GETTER(NAME, RETURN_TYPE, pMEMBER) \
	RETURN_TYPE NAME() \
	{ \
		return pMEMBER->NAME(); \
	}	\


namespace SkyLua 
{
	namespace Classes 
	{
		namespace Actor 
		{
			int lua_destructor(lua_State* l);
			int lua_registerclass(lua_State* l);

			int lua_getname(lua_State* l);
			int lua_getlevel(lua_State* l);
			int lua_gethealth(lua_State* l);

			int lua_sethealth(lua_State* l);



			// DERIVED

			int lua_getname(lua_State* l);
			int lua_getID(lua_State* l);

			int lua_setname(lua_State* l);

			// END DERIVED


			const luaL_Reg regs[] =
			{
				{ "__gc", lua_destructor },

				{ "GetName", lua_getname },
				{ "GetLevel", lua_getlevel },
				{ "GetHealth", lua_gethealth },

				{ "SetHealth", lua_sethealth },

				// DERIVED
				{ "GetID", lua_getID },
				{ "GetName", lua_getname },

				{ "SetName", lua_setname },
				{ NULL, NULL }
			};

		}


		struct LuaActor 
		{
			LuaActor(RE::Actor* pActor) 
			{
				m_pActor = pActor;
			}

			RE::Actor* m_pActor;
		};
	}
}

#undef GETTER