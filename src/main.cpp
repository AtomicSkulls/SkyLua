//#include <lua.hpp>
#include "Lua/lua_skyrim.h"
#include "Lua/skylua_include.h"

//#include "Lua/lua_hook.h"
//#include "src/Lua/lua_common.h"
//#include "src/Lua/Events/LoadGameEventHandler.h"
//#include "src/Lua/Events/CellChangeEventHandler.h"

namespace {
	void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
	{
		switch (a_msg->type) {
		case SKSE::MessagingInterface::kDataLoaded:
		{

			auto events = RE::ScriptEventSourceHolder::GetSingleton();
			events->AddEventSink(Events::LoadGameEventHandler::GetSingleton());
			events->AddEventSink(Events::CellLoadEventHandler::GetSingleton());
			events->AddEventSink(Events::ActorLocationChangeEventHandler::GetSingleton());

			auto events2 = RE::PlayerCharacter::GetSingleton();
			events2->RE::BSTEventSource<RE::BGSActorCellEvent>::AddEventSink(Events::CellChangeEventHandler::GetSingleton());

			SKSE::GetCrosshairRefEventSource()->AddEventSink(Events::CrosshairRefEventHandler::GetSingleton());

			CC_RunLua::Register();

		}
		break;
		}
	}
}

namespace fs = std::filesystem;

static void LoadLuaFiles(lua_State* l, const char* path)
{
	for (const auto& entry : fs::directory_iterator(path))
	{
		//	const auto fn = entry.path().filename().string();

		const auto p = entry.path();
		const char* s = fs::canonical(p).string().c_str();

		luaL_dofile(l, s);
	}

}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface * a_skse, SKSE::PluginInfo * a_info)
{
#ifndef NDEBUG
	auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
#else
	auto path = logger::log_directory();
	if (!path) {
		return false;
	}

	*path /= "MyFirstPlugin.log"sv;
	auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
#endif

	auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

#ifndef NDEBUG
	log->set_level(spdlog::level::trace);
#else
	log->set_level(spdlog::level::info);
	log->flush_on(spdlog::level::warn);
#endif

	spdlog::set_default_logger(std::move(log));
	spdlog::set_pattern("%g(%#): [%^%l%$] %v"s);

	logger::info("SkyLua v1.0.0");

	a_info->infoVersion = SKSE::PluginInfo::kVersion;
	a_info->name = "SkyLua";
	a_info->version = 1;

	if (a_skse->IsEditor()) {
		logger::critical("Loaded in editor, marking as incompatible"sv);
		return false;
	}

	const auto ver = a_skse->RuntimeVersion();
	if (ver < SKSE::RUNTIME_1_5_39) {
		logger::critical(FMT_STRING("Unsupported runtime version {}"), ver.string());
		return false;
	}

	return true;
}


extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface * a_skse)
{
	logger::info("SkyLua loaded");

	SKSE::Init(a_skse);

	auto messaging = SKSE::GetMessagingInterface();
	if (!messaging->RegisterListener("SKSE", MessageHandler)) {
		return false;
	}

	luaL_openlibs(SkyLua::Globals::l_state);

	SkyLua::RegisterOverrides(SkyLua::Globals::l_state);
	SkyLua::RegisterStandalones(SkyLua::Globals::l_state);
	SkyLua::RegisterClasses(SkyLua::Globals::l_state);


	const char* lua_dir = R"(Data\scripts\lua\)";
	//	auto lua_dir = L"Data\scripts\lua";

	LoadLuaFiles(SkyLua::Globals::l_state, lua_dir);

	return true;
}
