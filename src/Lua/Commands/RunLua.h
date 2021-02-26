#pragma once

#include "../lua_common.h"
#include "../lua_skyrim.h"
#include <PCH.h>

class CC_RunLua {
public:
	static bool Exec(const RE::SCRIPT_PARAMETER* a_paramInfo, RE::SCRIPT_FUNCTION::ScriptData* a_scriptData, RE::TESObjectREFR* a_thisObj, RE::TESObjectREFR* a_containingObj, RE::Script* a_scriptObj, RE::ScriptLocals* a_locals, double& a_result, std::uint32_t& a_opcodeOffsetPtr);
	static void Register();

private:
	CC_RunLua() = delete;
	CC_RunLua(const CC_RunLua&) = delete;
	CC_RunLua(CC_RunLua&&) = delete;
	~CC_RunLua() = delete;

	static void lua_run(const char* luaCode);
};