#pragma once

#include "../lua_skyrim.h"

using SkyLua::Globals::l_state;

namespace Events
{
	class CrosshairRefEventHandler : public RE::BSTEventSink<SKSE::CrosshairRefEvent>
	{
	public:
		using EventResult = RE::BSEventNotifyControl;

		static CrosshairRefEventHandler* GetSingleton();

		virtual EventResult ProcessEvent(const SKSE::CrosshairRefEvent* a_event, RE::BSTEventSource<SKSE::CrosshairRefEvent>* a_dispatcher) override;

	private:
		CrosshairRefEventHandler() = default;
		CrosshairRefEventHandler(const CrosshairRefEventHandler&) = delete;
		CrosshairRefEventHandler(CrosshairRefEventHandler&&) = delete;
		virtual ~CrosshairRefEventHandler() = default;

		CrosshairRefEventHandler& operator=(const CrosshairRefEventHandler&) = delete;
		CrosshairRefEventHandler& operator=(CrosshairRefEventHandler&&) = delete;
	};
}