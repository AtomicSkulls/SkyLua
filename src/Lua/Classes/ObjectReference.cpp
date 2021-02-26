#include "ObjectReference.h"

namespace SkyLua
{
	namespace Classes
	{
		namespace ObjectReference
		{
			int lua_destructor(lua_State* l)
			{
				LuaObjRef* obj = SkyLua::Util::lua_checkudata<LuaObjRef>(l, 1, MetaNames::OBJREF);
				delete obj;

				return 0;
			}

			int lua_registerclass(lua_State* l)
			{
				luaL_newmetatable(l, MetaNames::OBJREF);

				luaL_setfuncs(l, regs, 0);

				lua_pushvalue(l, -1);

				lua_setfield(l, -1, "__index");

				lua_pop(l, 1);

				return 0;
			}

			int lua_getname(lua_State* l) {
				LuaObjRef* obj = SkyLua::Util::lua_checkudata<LuaObjRef>(l, 1, MetaNames::OBJREF);

				lua_pushstring(l, obj->m_pRef->GetName());

				return 1;
			}

			int lua_getowner(lua_State* l)
			{
				LuaObjRef* obj = SkyLua::Util::lua_checkudata<LuaObjRef>(l, 1, MetaNames::OBJREF);

				auto s = obj->m_pRef->GetOwner();

				return 0;
			}

			int lua_getparentcell(lua_State* l)
			{
				LuaObjRef* obj = SkyLua::Util::lua_checkudata<LuaObjRef>(l, 1, MetaNames::OBJREF);

				auto s = obj->m_pRef->GetParentCell();

				Util::lua_pushobject(l, new LuaCell(s), "lua_cell");

				return 1;
			}

			int lua_getposition(lua_State* l)
			{
				LuaObjRef* obj = SkyLua::Util::lua_checkudata<LuaObjRef>(l, 1, MetaNames::OBJREF);

				auto pos = obj->m_pRef->GetPosition();

				LuaVector* v = new LuaVector(pos);

				Util::lua_pushobject(l, new LuaVector(pos), "lua_vector");

				return 1;
			}

			int lua_setposition(lua_State* l)
			{
				LuaObjRef* obj = SkyLua::Util::lua_checkudata<LuaObjRef>(l, 1, MetaNames::OBJREF);
				LuaVector* vec = SkyLua::Util::lua_checkudata<LuaVector>(l, 2, "lua_vector");

				obj->m_pRef->SetPosition(vec->m_fX, vec->m_fY, vec->m_fZ);

				return 1;
			}

			int lua_isactor(lua_State* l)
			{
				LuaObjRef* obj = SkyLua::Util::lua_checkudata<LuaObjRef>(l, 1, MetaNames::OBJREF);

				lua_pushboolean(l, obj->m_pRef->formType == RE::FormType::ActorCharacter);

				return 1;
			}

			int lua_asactor(lua_State* l) 
			{
				LuaObjRef* obj = SkyLua::Util::lua_checkudata<LuaObjRef>(l, 1, MetaNames::OBJREF);

				auto actor = obj->m_pRef->As<RE::Actor>();
				
				if (obj->m_pRef->formType == RE::FormType::ActorCharacter) 
					Util::lua_pushobject(l, new LuaActor(actor), MetaNames::ACTOR);
				else
					lua_pushnil(l);
				
				return 1;
			}

			int lua_disable(lua_State* l) 
			{
				LuaObjRef* obj = SkyLua::Util::lua_checkudata<LuaObjRef>(l, 1, MetaNames::OBJREF);

				obj->m_pRef->Disable();

				return 1;
			}

			int lua_iswater(lua_State* l)
			{
				LuaObjRef* obj = SkyLua::Util::lua_checkudata<LuaObjRef>(l, 1, MetaNames::OBJREF);

				lua_pushboolean(l, obj->m_pRef->IsWater());

				return 1;
			}
		}
	}
}
