#pragma once

#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"

#ifdef NDEBUG
#include <spdlog/sinks/basic_file_sink.h>
#else
#include <spdlog/sinks/msvc_sink.h>
#endif

using namespace std::literals;

namespace logger = SKSE::log;

#define DLLEXPORT __declspec(dllexport)

#define ABSTRACT class __declspec( novtable )

[[nodiscard]] constexpr std::string_view safe_string(const char* a_str) noexcept
{
	return a_str ? a_str : "";
}