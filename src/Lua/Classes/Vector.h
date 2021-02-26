#pragma once

#include "../lua_common.h"
#include <PCH.h>

namespace SkyLua 
{
	namespace Classes 
	{
		namespace Vector 
		{
			int lua_destructor(lua_State* l);
			int lua_constructor(lua_State* l);
			int lua_registerclass(lua_State* l);

			const luaL_Reg regs[] =
			{
				{ "new", lua_constructor },
				{ "__gc", lua_destructor },
				{ NULL, NULL }
			};
		}

		class LuaVector {
		public:
			LuaVector(RE::NiPoint3& pPoint)
			{
				m_fX, m_fY, m_fZ = pPoint.x, pPoint.y, pPoint.z;
			}
			LuaVector(float x, float y, float z)
			{
				m_fX, m_fY, m_fZ = x, y, z;
			}

			float m_fX = 0.0F;
			float m_fY = 0.0F;
			float m_fZ = 0.0F;
		};
	}
}

