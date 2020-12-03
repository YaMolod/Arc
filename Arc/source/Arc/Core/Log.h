#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace ARC {

	class ARC_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

//Core log macros
#define ARC_CORE_TRACE(...)    ::ARC::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ARC_CORE_INFO(...)     ::ARC::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ARC_CORE_WARN(...)     ::ARC::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ARC_CORE_ERROR(...)    ::ARC::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ARC_CORE_FATAL(...)    ::ARC::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define ARC_TRACE(...)         ::ARC::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ARC_INFO(...)          ::ARC::Log::GetClientLogger()->info(__VA_ARGS__)
#define ARC_WARN(...)          ::ARC::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ARC_ERROR(...)         ::ARC::Log::GetClientLogger()->error(__VA_ARGS__)
#define ARC_FATAL(...)         ::ARC::Log::GetClientLogger()->fatal(__VA_ARGS__)