#pragma once

#include "../lua_skyrim.h"

using SkyLua::Globals::l_state;

namespace Events
{
	class LoadGameEventHandler : public RE::BSTEventSink<RE::TESLoadGameEvent>
	{
	public:
		using EventResult = RE::BSEventNotifyControl;

		static LoadGameEventHandler* GetSingleton();

		virtual EventResult ProcessEvent(const RE::TESLoadGameEvent* a_event, RE::BSTEventSource<RE::TESLoadGameEvent>* a_dispatcher) override;

	private:
		LoadGameEventHandler() = default;
		LoadGameEventHandler(const LoadGameEventHandler&) = delete;
		LoadGameEventHandler(LoadGameEventHandler&&) = delete;
		virtual ~LoadGameEventHandler() = default;

		LoadGameEventHandler& operator=(const LoadGameEventHandler&) = delete;
		LoadGameEventHandler& operator=(LoadGameEventHandler&&) = delete;
	};
}