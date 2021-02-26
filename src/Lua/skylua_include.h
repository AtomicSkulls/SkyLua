#pragma once

#include "Classes/Actor.h"
#include "Classes/Cell.h"
#include "Classes/ObjectReference.h"
#include "Classes/Vector.h"

#include "Events/CellChangeEventHandler.h"
#include "Events/LoadGameEventHandler.h"
#include "Events/CrosshairRefEventHandler.h"

#include "Commands/RunLua.h"


namespace SkyLua
{
	void RegisterGlobals(lua_State* l);
	void RegisterOverrides(lua_State* L);
	void RegisterClasses(lua_State* l);
	void RegisterStandalones(lua_State* L);
	void RegisterHooks(lua_State* L);
}