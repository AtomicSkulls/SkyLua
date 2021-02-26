#include "RunLua.h"

bool CC_RunLua::Exec(const RE::SCRIPT_PARAMETER* a_paramInfo, RE::SCRIPT_FUNCTION::ScriptData* a_scriptData, RE::TESObjectREFR* a_thisObj, RE::TESObjectREFR* a_containingObj, RE::Script* a_scriptObj, RE::ScriptLocals* a_locals, double& a_result, std::uint32_t& a_opcodeOffsetPtr)
{
    auto strChunk = a_scriptData->GetStringChunk();
    auto luaCode = strChunk->GetString();

    lua_run(luaCode.c_str());

    return false;
}

void CC_RunLua::Register()
{
    using Type = RE::SCRIPT_PARAM_TYPE;

    auto info = RE::SCRIPT_FUNCTION::LocateConsoleCommand("BetaComment");  // Unused

	if (info) {
		static RE::SCRIPT_PARAMETER params[] = {
			{ "String", Type::kChar, 0 }
		};

		info->functionName = "lua_run";
		info->shortName = "lua_r";
		info->helpString = "";
		info->referenceFunction = false;
		info->SetParameters(params);
		info->executeFunction = Exec;
		info->conditionFunction = nullptr;
		info->editorFilter = false;
		info->invalidatesCellList = false;

		logger::info(FMT_STRING("Registered console command: {} ({})"), "lua_run", "lua_r");
	}
	else {
		logger::error(FMT_STRING("Failed to register console command: {} ({})"), "lua_run", "lua_r");
	}
}

void CC_RunLua::lua_run(const char* luaCode)
{
	luaL_dostring(SkyLua::Globals::l_state, luaCode);
}
