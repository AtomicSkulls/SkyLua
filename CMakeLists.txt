cmake_minimum_required(VERSION 3.18)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" CACHE STRING "")
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "")

project(
	SkyLua
	VERSION 1.0.0
	LANGUAGES CXX
)

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/version.rc.in
	${CMAKE_CURRENT_BINARY_DIR}/version.rc
	@ONLY
)


if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
	message(
		FATAL_ERROR
			"In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
)
endif()

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_DEBUG OFF)

set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON CACHE BOOL "")
set(Boost_USE_DEBUG_RUNTIME ON)

if (MSVC)
	add_compile_definitions(
		_UNICODE
	)
	
	set(COMPILE_OPTIONS_DEBUG
		/Zc:inline-	# Keep unreferenced COMDAT
		/JMC	# Just My Code debugging
	)
	
	set(COMPILE_OPTIONS_RELEASE
		/Zc:inline	# Remove unreferenced COMDAT
		/JMC-	# Disable Just My Code debugging
	)

	add_compile_options(
		/Gy	# Enable Function-Level Linking
		/MP	# Build with Multiple Processes
		/Oi	# Generate Intrinsic Functions
		/sdl	# Enable Additional Security Checks
		/Zi	# Debug Information Format
		
		/permissive-	# Standards conformance
		
		/Zc:alignedNew	# C++17 over-aligned allocation
		/Zc:auto	# Deduce Variable Type
		/Zc:char8_t
		/Zc:__cplusplus	# Enable updated __cplusplus macro
		/Zc:externC
		/Zc:externConstexpr	# Enable extern constexpr variables
		/Zc:forScope	# Force Conformance in for Loop Scope
		/Zc:hiddenFriend
		/Zc:implicitNoexcept	# Implicit Exception Specifiers
		/Zc:lambda
		/Zc:noexceptTypes	# C++17 noexcept rules
		/Zc:preprocessor	# Enable preprocessor conformance mode
		/Zc:referenceBinding	# Enforce reference binding rules
		/Zc:rvalueCast	# Enforce type conversion rules
		/Zc:sizedDealloc	# Enable Global Sized Deallocation Functions
		/Zc:strictStrings	# Disable string literal type conversion
		/Zc:ternary	# Enforce conditional operator rules
		/Zc:threadSafeInit	# Thread-safe Local Static Initialization
		/Zc:tlsGuards
		/Zc:trigraphs	# Trigraphs Substitution
		/Zc:wchar_t	# wchar_t Is Native Type
		
		/experimental:external
		/external:anglebrackets
		/external:W0
		
		/W4	# Warning level (all warnings)
	#	/WX	# Warning level (warnings are errors)
		
		"$<$<CONFIG:Debug>:${COMPILE_OPTIONS_DEBUG}>"
		"$<$<CONFIG:Release>:${COMPILE_OPTIONS_RELEASE}>"
	)

	set(LINK_OPTIONS_DEBUG
		/INCREMENTAL	# Link Incrementally
		/OPT:NOREF	# Optimizations (keep functions/data never referenced)
		/OPT:NOICF	# Optimizations (prevent identical COMDAT folding)
	)
	
	set(LINK_OPTIONS_RELEASE
		/INCREMENTAL:NO	# Link Incrementally
		/OPT:REF	# Optimizations (eliminate functions/data never referenced)
		/OPT:ICF	# Optimizations (perform identical COMDAT folding)
	)

	add_link_options(
		"$<$<CONFIG:Debug>:${LINK_OPTIONS_DEBUG}>"
		"$<$<CONFIG:Release>:${LINK_OPTIONS_RELEASE}>"
	)
endif()

add_subdirectory("extern/CommonLibSSE" CommonLibSSE)
# add_subdirectory("extern/LuaJIT" LuaJIT)

find_package(spdlog REQUIRED)

#include(cmake/headerlist.cmake)
#include(cmake/sourcelist.cmake)


set(headers
	src/PCH.h
	src/Lua/lua_common.h
	src/Lua/lua_skyrim.h
	src/Lua/skylua_include.h
	src/Lua/Classes/Actor.h
	src/Lua/Classes/Cell.h
	src/Lua/Classes/ObjectReference.h
	src/Lua/Classes/Player.h
	src/Lua/Classes/Vector.h
	src/Lua/Commands/CommandPipe.h
	src/Lua/Commands/RunLua.h
	src/Lua/Events/CellChangeEventHandler.h
	src/Lua/Events/CrosshairRefEventHandler.h
	src/Lua/Events/LoadGameEventHandler.h
)

set(sources
	src/main.cpp
	src/PCH.cpp
	src/Lua/lua_common.cpp
	src/Lua/lua_skyrim.cpp
	src/Lua/skylua_include.cpp
	src/Lua/Classes/Actor.cpp
	src/Lua/Classes/Cell.cpp
	src/Lua/Classes/ObjectReference.cpp
	src/Lua/Classes/Player.cpp
	src/Lua/Classes/Vector.cpp
	src/Lua/Commands/CommandPipe.cpp
	src/Lua/Commands/RunLua.cpp
	src/Lua/Events/CellChangeEventHandler.cpp
	src/Lua/Events/CrosshairRefEventHandler.cpp
	src/Lua/Events/LoadGameEventHandler.cpp
)

# ---- Build Lua ----

execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/build_lua.bat" RESULT_VARIABLE CMD_ERROR)


# ---- Add source files ----

source_group(
	TREE ${CMAKE_CURRENT_SOURCE_DIR}
	FILES
		${headers}
		${sources}
)


# ---- Create DLL ----

add_library(${PROJECT_NAME} SHARED
	${headers}
	${sources}
	${CMAKE_CURRENT_BINARY_DIR}/version.rc
	.clang-format
)

target_compile_features(${PROJECT_NAME}
	PUBLIC
		cxx_std_20
)

target_compile_options(${PROJECT_NAME}
	PRIVATE
		"$<$<BOOL:${MSVC}>:/TP>"
)

list(APPEND build_incldirs "${CMAKE_CURRENT_SOURCE_DIR}/Extern/LuaJIT/src" "${CMAKE_CURRENT_SOURCE_DIR}/src" )

target_include_directories(${PROJECT_NAME}
	PRIVATE 
		"$<BUILD_INTERFACE:${build_incldirs}>"
        $<INSTALL_INTERFACE:src>
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		CommonLibSSE::CommonLibSSE
		spdlog::spdlog
		${CMAKE_CURRENT_SOURCE_DIR}/libs/lua51.lib
		${CMAKE_CURRENT_SOURCE_DIR}/libs/luajit.lib
)

target_link_options(${PROJECT_NAME}
	PUBLIC
		${LINK_OPTIONS_${CONFIG}}
)

target_precompile_headers(${PROJECT_NAME}
	PRIVATE
		src/PCH.h
)