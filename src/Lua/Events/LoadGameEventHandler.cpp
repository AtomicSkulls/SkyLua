#include "LoadGameEventHandler.h"



namespace fs = std::filesystem;

namespace Events {
	LoadGameEventHandler* LoadGameEventHandler::GetSingleton()
	{
		static LoadGameEventHandler singleton;
		return &singleton;
	}

	auto LoadGameEventHandler::ProcessEvent(const RE::TESLoadGameEvent* a_event, RE::BSTEventSource<RE::TESLoadGameEvent>* a_dispatcher)
		-> EventResult
	{
		
	//	lua_State* L = luaL_newstate();
	//	luaL_openlibs(L);

		SkyLua::Libs::Hooking::registerLib(SkyLua::Globals::l_state);
		SkyLua::Libs::Refs::registerLib(SkyLua::Globals::l_state);

		auto* console = RE::ConsoleLog::GetSingleton();
		


		SkyLua::Libs::Hooking::call(l_state, "OnLoadGame", [](lua_State* l) {
			return 0;
		});

		const char* lua_dir = R"(Data\scripts\lua\)";
//		SkyLua::Util::LoadLuaFiles(l_state, lua_dir);
		

//	luaL_dostring(l_state, "print(\"Hello from Lua\")");
//		luaL_dostring(l_state, "print(CurTime())");

		return EventResult::kContinue;
	}
}