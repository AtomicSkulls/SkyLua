# SkyLua
## Information
This project aims to fully implement the Lua scripting language into Skyrim. Utilizing LuaJIT, impact on perfomrance is minimal.

## Build Dependencies
* [All Dependencies from CommonLib](https://github.com/Ryan-rsm-McKenzie/CommonLibSSE)

## Building
Building should just be a matter of using CMake. If you are missing the required Lua libs and lua51.dll after building the project, try running [build_lua](build_lua.bat) or [building Lua manually](https://github.com/LuaJIT/LuaJIT). After building, make sure to copy lua51.dll to your main Skyrim folder.