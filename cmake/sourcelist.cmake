set(sources ${sources}
	include/main.cpp
	include/PCH.cpp
	include/Lua/lua_common.cpp
	include/Lua/lua_skyrim.cpp
	include/Lua/skylua_include.cpp
	include/Lua/Classes/Actor.cpp
	include/Lua/Classes/Cell.cpp
	include/Lua/Classes/ObjectReference.cpp
	include/Lua/Classes/Player.cpp
	include/Lua/Classes/Vector.cpp
	include/Lua/Commands/CommandPipe.cpp
	include/Lua/Commands/RunLua.cpp
	include/Lua/Events/CellChangeEventHandler.cpp
	include/Lua/Events/CrosshairRefEventHandler.cpp
	include/Lua/Events/LoadGameEventHandler.cpp
)