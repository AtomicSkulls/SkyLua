#include "CrosshairRefEventHandler.h"

namespace Events
{
	CrosshairRefEventHandler* CrosshairRefEventHandler::GetSingleton()
	{
		return nullptr;
	}

	auto CrosshairRefEventHandler::ProcessEvent(const SKSE::CrosshairRefEvent* a_event, RE::BSTEventSource<SKSE::CrosshairRefEvent>* a_dispatcher)
		-> EventResult
	{
		auto src = a_event->crosshairRef;

		if (src && src != nullptr)
		{
			SkyLua::Globals::g_refLookedAt = src->AsReference();
		}

		return EventResult::kContinue;
	}
}