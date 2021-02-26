#pragma once

#include "lua_common.h"

#include <PCH.h>
#include <map>

#include "Classes/ObjectReference.h"
#include "Classes/Actor.h"
#include "Classes/Player.h"

namespace SkyLua 
{
//	static const wchar_t* script_dir = L"Data/SKSE/Plugins/Scripts/Lua";

	namespace Globals 
	{
		extern lua_State* l_state;

		// List of references the current cell contains.
		extern std::vector<RE::TESObjectREFR*> g_cellRefs;

		extern RE::TESObjectREFR* g_refLookedAt;

		namespace Lua 
		{
			void InitEnums(lua_State* l);

			
		}
	}

	namespace Libs 
	{
		namespace Refs 
		{
			// Map of "enums' of which the scripter can use for "As" castings in Lua
			const std::map<int, const char*> Filters = 
			{
				{ 0, "TES_NONE" },
				{ 1, "TES_ACTOR" }, //  RE::FormType::ActorCharacter = 62
			};

			enum EFilters 
			{
				TES_NONE = 0,
				TES_ACTOR = 1,
				TES_CELL = 2,
			};

			int lua_getall(lua_State* l);
			int lua_getRefLookedAt(lua_State* l);
			
			static bool PushFromFilter(lua_State* l, Classes::LuaObjRef* obj, int filter);

			static const struct luaL_Reg lib[] = {
				{ "GetAll", lua_getall},
				{ "GetPlayerTrace", lua_getRefLookedAt},
				{ NULL, NULL }
			};

			int registerLib(lua_State* l);
		}

		namespace Debug
		{
			int lua_log(lua_State* l);
			int lua_notification(lua_State* l);

			static const struct luaL_Reg lib[] = {
				{ "Log", lua_log},
				{ "Notification", lua_notification},
				{ NULL, NULL }
			};

			int registerLib(lua_State* l);
		}
	}

	namespace Standalones {
		 int lua_getActorsNearPoint(lua_State* l);
		 int lua_getGlobalCellRefs(lua_State* l);
		 int lua_getPlayer(lua_State* l);
	}

	namespace Overrides {
		int lua_print(lua_State* L);
	}

	namespace Util {
	//	void lua_console_dumpstack(lua_State* l);
		void lua_checkerror(lua_State* l);
	}

	void UpdateGlobalCellRefs();
}
