#pragma once

#include "../lua_skyrim.h"
#include "../Classes/Cell.h"

using SkyLua::Globals::l_state;

namespace Events
{
	class CellChangeEventHandler : public RE::BSTEventSink<RE::BGSActorCellEvent>
	{
	public:
		using EventResult = RE::BSEventNotifyControl;

		static CellChangeEventHandler* GetSingleton();

		virtual EventResult ProcessEvent(const RE::BGSActorCellEvent* a_event, RE::BSTEventSource<RE::BGSActorCellEvent>* a_dispatcher) override;

	private:
		CellChangeEventHandler() = default;
		CellChangeEventHandler(const CellChangeEventHandler&) = delete;
		CellChangeEventHandler(CellChangeEventHandler&&) = delete;
		virtual ~CellChangeEventHandler() = default;

		CellChangeEventHandler& operator=(const CellChangeEventHandler&) = delete;
		CellChangeEventHandler& operator=(CellChangeEventHandler&&) = delete;
	};

	class CellLoadEventHandler : public RE::BSTEventSink<RE::TESCellFullyLoadedEvent>
	{
	public:
		using EventResult = RE::BSEventNotifyControl;

		static CellLoadEventHandler* GetSingleton();

		virtual EventResult ProcessEvent(const RE::TESCellFullyLoadedEvent* a_event, RE::BSTEventSource<RE::TESCellFullyLoadedEvent>* a_dispatcher) override;

	private:
		CellLoadEventHandler() = default;
		CellLoadEventHandler(const CellLoadEventHandler&) = delete;
		CellLoadEventHandler(CellLoadEventHandler&&) = delete;
		virtual ~CellLoadEventHandler() = default;

		CellLoadEventHandler& operator=(const CellLoadEventHandler&) = delete;
		CellLoadEventHandler& operator=(CellLoadEventHandler&&) = delete;
	};

	class ActorLocationChangeEventHandler : public RE::BSTEventSink<RE::TESActorLocationChangeEvent>
	{
	public:
		using EventResult = RE::BSEventNotifyControl;

		static ActorLocationChangeEventHandler* GetSingleton();

		virtual EventResult ProcessEvent(const RE::TESActorLocationChangeEvent* a_event, RE::BSTEventSource<RE::TESActorLocationChangeEvent>* a_dispatcher) override;

	private:
		ActorLocationChangeEventHandler() = default;
		ActorLocationChangeEventHandler(const ActorLocationChangeEventHandler&) = delete;
		ActorLocationChangeEventHandler(ActorLocationChangeEventHandler&&) = delete;
		virtual ~ActorLocationChangeEventHandler() = default;

		ActorLocationChangeEventHandler& operator=(const ActorLocationChangeEventHandler&) = delete;
		ActorLocationChangeEventHandler& operator=(ActorLocationChangeEventHandler&&) = delete;

		const char* m_strCurrentCellName = NULL;
	};
}