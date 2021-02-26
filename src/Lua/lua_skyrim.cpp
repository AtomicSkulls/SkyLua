#include "lua_skyrim.h"


namespace SkyLua 
{
    namespace Globals 
    {
        lua_State* l_state = luaL_newstate();

        // List of references the current cell contains.
        std::vector<RE::TESObjectREFR*> g_cellRefs;

        RE::TESObjectREFR* g_refLookedAt = nullptr;

        enum ERefFilters
        {
            TES_NONE = 0,
            TES_ACTOR = 62,
        };

        namespace Lua 
        {
            void InitEnums(lua_State* l)
            {
                lua_pushinteger(l, 0);
                lua_setglobal(l, "TES_NONE");

                lua_pushinteger(l, 62);
                lua_setglobal(l, "TES_ACTOR");

            }
        }
    }

    namespace Standalones 
    {
        int lua_getGlobalCellRefs(lua_State* l)
        {

            auto player = RE::PlayerCharacter::GetSingleton();

            if (player == nullptr)
                return 0;

            auto cell = player->GetParentCell();

            if (cell == nullptr)
                return 0;

            lua_newtable(l);
            int i = 1;

            auto y = [&](RE::TESObjectREFR& r) {

                Util::Tables::lua_pushkv_int_ud(l, i, new Classes::LuaObjRef(&r), MetaNames::OBJREF);

                i++;

                return true;
            };

            cell->ForEachReference(y);

            return 1;
        }

        int lua_getPlayer(lua_State* l) 
        {
            auto player = RE::PlayerCharacter::GetSingleton();

            SkyLua::Util::lua_pushobject(l, new SkyLua::Classes::LuaPlayer(player), "lua_player");

            return 1;
        }

    }

    namespace Overrides 
    {
        
        /*
        int lua_print(lua_State* L)
        {
            auto* console = RE::ConsoleLog::GetSingleton();

            if (!console)
                return 0;

            int n = lua_gettop(L);  
            int i;
            for (i = 1; i <= n; i++) { 
                size_t l;
                const char* s = luaL_tolstring(L, i, &l); 
            //   if (i > 1)  
            //       lua_writestring("\t", 1);  
                console->Print(s);

                lua_pop(L, 1); 
            }
         //   lua_writeline();

            return 0;
        }
        */

        
        int lua_print(lua_State* L) {
            int n = lua_gettop(L);  
            int i;

            auto* console = RE::ConsoleLog::GetSingleton();

            lua_getglobal(L, "tostring");
            for (i = 1; i <= n; i++) {
                const char* s;
                lua_pushvalue(L, -1);  
                lua_pushvalue(L, i);  
                lua_call(L, 1, 1);
                s = lua_tostring(L, -1);
                if (s == NULL)
                //    return luaL_error(L, LUA_QL("tostring") " must return a string to "
                 //       LUA_QL("print"));
                if (i > 1) console->Print("\t");
                console->Print(s);
                lua_pop(L, 1); 
            }
         //   console->Print("\n");
            return 0;
        }
    }

    namespace Util
    {
        void lua_console_dumpstack(lua_State* L) 
        {
            auto console = RE::ConsoleLog::GetSingleton();
            int i;
            int top = lua_gettop(L);
            for (i = 1; i <= top; i++) {  /* repeat for each level */
                int t = lua_type(L, i);
                switch (t) {

                case LUA_TSTRING:  /* strings */
                 //   printf("`%s'", lua_tostring(L, i));
                    console->Print(lua_tostring(L, i));
                    break;

                case LUA_TBOOLEAN:  /* booleans */
                //    printf(lua_toboolean(L, i) ? "true" : "false");
                    console->Print(lua_toboolean(L, i) ? "true" : "false");
                    break;

                case LUA_TNUMBER:  /* numbers */
                 //   printf("%g", lua_tonumber(L, i));

                    console->Print(std::to_string(lua_tonumber(L, i)).c_str());
                    break;

                default:  /* other values */
                 //   printf("%s", lua_typename(L, t));

                    console->Print(lua_typename(L, t));
                    break;

                }
                //    printf("  ");  /* put a separator */
            }
            //printf("\n");  /* end the listing */
        }
        void lua_checkerror(lua_State* L) {
            if (lua_tostring(SkyLua::Globals::l_state, -1) != NULL)
            {
                auto console = RE::ConsoleLog::GetSingleton();

                console->Print(lua_tostring(SkyLua::Globals::l_state, -1));
            }
        }
    }

    void UpdateGlobalCellRefs()
    {
        Globals::g_cellRefs.clear();

        
        auto player = RE::PlayerCharacter::GetSingleton();

        if (player == nullptr)
            return;

        auto cell = player->GetParentCell();

        if (cell == nullptr)
            return;

        std::vector<RE::TESObjectREFR*> cellRefs;

        auto y = [&](RE::TESObjectREFR& r) {
      //      Globals::g_cellRefs.push_back(std::ref(r));
            cellRefs.push_back(&r);
            return true;
        };

        cell->ForEachReference(y);
        
    }
}



namespace SkyLua 
{
    namespace Libs 
    {
        namespace Refs 
        {
            int lua_getall(lua_State* l)
            {
                int filter = luaL_checkinteger(l, 1); // pretty sure the default is 0

                auto player = RE::PlayerCharacter::GetSingleton();

                if (player == nullptr)
                    return 0;

                auto cell = player->GetParentCell();

                if (cell == nullptr)
                    return 0;

                lua_newtable(l);
                int i = 1; // lua number-indexed arrays start at 1 

                auto y = [&](RE::TESObjectREFR& r) {

                    lua_pushinteger(l, i);

                    auto c = new Classes::LuaObjRef(&r);

                    if (!PushFromFilter(l, c, filter)) {
                        SkyLua::Util::lua_pushobject(l, c, MetaNames::OBJREF);
                    }
                  
                    i++;

                    return true;
                };

                cell->ForEachReference(y);

                return 1;
            }

            int lua_getRefLookedAt(lua_State* l)
            {
                if (Globals::g_refLookedAt != nullptr) 
                {
                    auto c = new Classes::LuaObjRef(Globals::g_refLookedAt);

                    SkyLua::Util::lua_pushobject(l, c, MetaNames::OBJREF);
                }
                else 
                {
                    lua_pushnil(l);
                }

                return 1;
            }
            
            bool PushFromFilter(lua_State* l, Classes::LuaObjRef* obj, int filter)
            {
                switch (filter) 
                {
                    case TES_ACTOR:
                    {
                        auto actor = obj->m_pRef->As<RE::Actor>();
                        SkyLua::Util::lua_pushobject(l, new Classes::LuaActor(actor), MetaNames::ACTOR);

                        return true;
                    }
                    case TES_CELL:
                    {
                        auto cell = obj->m_pRef->As<RE::TESObjectCELL>();
                        SkyLua::Util::lua_pushobject(l, new Classes::LuaCell(cell), MetaNames::ACTOR);

                        return true;
                    }
                    default:
                        return false;
                }
            }

            int registerLib(lua_State* l)
            {
                luaL_newlib(l, lib);
                lua_setglobal(l, "refs");

                return 1;
            }
        }
        namespace Debug
        {
            int lua_notification(lua_State* l)
            {
                const char* msg = luaL_checkstring(l, 1);

                RE::DebugNotification(msg, "");

                return 1;
            }

            int lua_log(lua_State* l)
            {
            //    std::string msg = luaL_checkstring(l, 1);
             //   logger::info(msg);

                return 1;
            }

            int registerLib(lua_State* l)
            {
                luaL_newlib(l, lib);
                lua_setglobal(l, "refs");

                return 1;
            }
        }
    }
}