#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace VOIP {

	class Logger
	{
	public:
		static void Init();

		 FORCEINLINE static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		 FORCEINLINE static std::shared_ptr<spdlog::logger>& GetServerLogger() { return s_ServerLogger; }
		 FORCEINLINE static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:

		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ServerLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define VOIP_CORE_TRACE(...)    ::VOIP::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define VOIP_CORE_INFO(...)     ::VOIP::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define VOIP_CORE_WARN(...)     ::VOIP::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define VOIP_CORE_ERROR(...)    ::VOIP::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define VOIP_CORE_FATAL(...)    ::VOIP::Logger::GetCoreLogger()->fatal(__VA_ARGS__)

// Server log macros
#define VOIP_SERVER_TRACE(...)	      ::VOIP::Logger::GetServerLogger()->trace(__VA_ARGS__)
#define VOIP_SERVER_INFO(...)	      ::VOIP::Logger::GetServerLogger()->info(__VA_ARGS__)
#define VOIP_SERVER_WARN(...)	      ::VOIP::Logger::GetServerLogger()->warn(__VA_ARGS__)
#define VOIP_SERVER_ERROR(...)	      ::VOIP::Logger::GetServerLogger()->error(__VA_ARGS__)
#define VOIP_SERVER_FATAL(...)	      ::VOIP::Logger::GetServerLogger()->fatal(__VA_ARGS__)

// Client log macros
#define VOIP_CLIENT_TRACE(...)	      ::VOIP::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define VOIP_CLIENT_INFO(...)	      ::VOIP::Logger::GetClientLogger()->info(__VA_ARGS__)
#define VOIP_CLIENT_WARN(...)	      ::VOIP::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define VOIP_CLIENT_ERROR(...)	      ::VOIP::Logger::GetClientLogger()->error(__VA_ARGS__)
#define VOIP_CLIENT_FATAL(...)	      ::VOIP::Logger::GetClientLogger()->fatal(__VA_ARGS__)
