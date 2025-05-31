#include "vs/logger.hpp"

namespace vs
{

    Logger::Logger(std::string name, LogLevel level) : m_name(std::move(name)), m_level(level)
    {
        // Initialization logic will go here.
    }

    Logger::~Logger()
    {
        // Cleanup logic will go here.
    }

    void Logger::set_level(LogLevel level)
    {
        m_level.store(level, std::memory_order_release);
    }

    LogLevel Logger::level() const
    {
        return m_level.load(std::memory_order_acquire);
    }

    const std::string &Logger::name() const
    {
        return m_name;
    }

} // namespace vs