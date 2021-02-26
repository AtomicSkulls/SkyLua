#include "CellChangeEventHandler.h"


namespace Events {
	CellChangeEventHandler* CellChangeEventHandler::GetSingleton()
	{
		static CellChangeEventHandler singleton;
		return &singleton;
	}

	auto CellChangeEventHandler::ProcessEvent(const RE::BGSActorCellEvent* a_event, RE::BSTEventSource<RE::BGSActorCellEvent>* a_dispatcher)
		-> EventResult
	{
		/*
		auto player = RE::PlayerCharacter::GetSingleton();

		auto t = player->GetParentCell();

		auto console = RE::ConsoleLog::GetSingleton();

		if (t == nullptr) {
			console->Print("Cell is null!");

			return EventResult::kContinue;
		}

		console->Print(t->GetName());

		*/

		
		// VECTOR CONFIRMED WORKING

		/*
		auto console = RE::ConsoleLog::GetSingleton();

		const char* code = R"(
			print( "doing string...")
			y = Vector.new(2, 4, 6)
			print(y.z)
			)";

	//	console->Print(lua_tostring(SkyLua::Globals::l_state, -1));

		luaL_dostring(SkyLua::Globals::l_state, code);
		*/
		return EventResult::kContinue;

		
	}

	CellLoadEventHandler* CellLoadEventHandler::GetSingleton()
	{
		static CellLoadEventHandler singleton;
		return &singleton;
	}

	auto CellLoadEventHandler::ProcessEvent(const RE::TESCellFullyLoadedEvent* a_event, RE::BSTEventSource<RE::TESCellFullyLoadedEvent>* a_dispatcher)
		-> EventResult
	{
		
		SkyLua::UpdateGlobalCellRefs();

		const char* code = R"(
			x = GetCellRefs()
			for k, v in pairs( x ) do
				if v:IsActor() then
					print(v:GetName() .. ' is an actor!')
				end
			end
			
			)";

		luaL_dostring(SkyLua::Globals::l_state, code);
		
		SkyLua::Util::lua_checkerror(SkyLua::Globals::l_state);

		SkyLua::Libs::Hooking::call(l_state, "CellFullyLoaded", [a_event](lua_State* l) {
			SkyLua::Util::lua_pushobject(l, new SkyLua::Classes::LuaCell(a_event->cell), "lua_cell");
			
			return 1;
		});

		return EventResult::kContinue;
	}

	ActorLocationChangeEventHandler* ActorLocationChangeEventHandler::GetSingleton()
	{
		static ActorLocationChangeEventHandler singleton;

		return &singleton;
	}

	auto ActorLocationChangeEventHandler::ProcessEvent(const RE::TESActorLocationChangeEvent* a_event, RE::BSTEventSource<RE::TESActorLocationChangeEvent>* a_dispatcher)
		-> EventResult
	{		
		auto player = RE::PlayerCharacter::GetSingleton();
		auto cell = player->GetParentCell();

		auto console = RE::ConsoleLog::GetSingleton();

		if (cell == nullptr) {
			return EventResult::kContinue;
		}

		const char* name = cell->GetName();

		if (m_strCurrentCellName == NULL || m_strCurrentCellName != name) {
			m_strCurrentCellName = name;

		//	console->Print(m_strCurrentCellName);
			// call lua "OnCellChange" event
		}
		
		return EventResult::kContinue;
	}

}