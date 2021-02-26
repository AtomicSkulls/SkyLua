#include "Actor.h"


namespace SkyLua {
	namespace Classes {
		namespace Actor {

			int lua_destructor(lua_State* l)
			{
				LuaActor* obj = SkyLua::Util::lua_checkudata<LuaActor>(l, 1, MetaNames::ACTOR);
				delete obj;

				return 0;
			}

			int lua_registerclass(lua_State* l) 
			{
				luaL_newmetatable(l, MetaNames::ACTOR);

				luaL_setfuncs(l, regs, 0);

				lua_pushvalue(l, -1);

				lua_setfield(l, -1, "__index");

				lua_pop(l, 1);

				return 0;
			}

			int lua_getlevel(lua_State* l)
			{
				LuaActor* obj = SkyLua::Util::lua_checkudata<LuaActor>(l, 1, MetaNames::ACTOR);
				
				lua_pushnumber(l, obj->m_pActor->GetLevel());

				return 1;
			}

			int lua_gethealth(lua_State* l)
			{
				LuaActor* obj = SkyLua::Util::lua_checkudata<LuaActor>(l, 1, MetaNames::ACTOR);

				lua_pushnumber(l, obj->m_pActor->GetActorValue(RE::ActorValue::kHealth));

				return 1;
			}

			int lua_sethealth(lua_State* l)
			{
				LuaActor* obj = SkyLua::Util::lua_checkudata<LuaActor>(l, 1, MetaNames::ACTOR);
				float x = luaL_checknumber(l, 2);

				obj->m_pActor->SetActorValue(RE::ActorValue::kHealth, x);

				return 0;
			}
		}
	}
}


// DERIVED

namespace SkyLua 
{
	namespace Classes 
	{
		namespace Actor 
		{
			int lua_getID(lua_State* l) 
			{
				LuaActor* obj = SkyLua::Util::lua_checkudata<LuaActor>(l, 1, MetaNames::ACTOR);
				lua_pushstring(l, obj->m_pActor->GetFormEditorID());

				return 1;
			}

			int lua_getname(lua_State* l)
			{
				LuaActor* obj = SkyLua::Util::lua_checkudata<LuaActor>(l, 1, MetaNames::ACTOR);

				lua_pushstring(l, obj->m_pActor->GetName());

				return 1;
			}

			int lua_setname(lua_State* l)
			{
				LuaActor* obj = SkyLua::Util::lua_checkudata<LuaActor>(l, 1, MetaNames::ACTOR);
				const char* x = luaL_checkstring(l, 2);

				obj->m_pActor->SetDisplayName(x, true);

				return 0;
			}
		}
	}
}