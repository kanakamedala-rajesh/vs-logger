#ifndef VS_LOGGER_HPP
#define VS_LOGGER_HPP

#include <atomic>
#include <string>

namespace vs
{

    /**
     * @enum LogLevel
     * @brief Defines the severity levels for log messages.
     *
     * The log levels are ordered by severity, from least to most severe. This ordering is
     * crucial for efficient filtering.
     */
    enum class LogLevel : uint8_t
    {
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        Critical,
        Off
    };

    /**
     * @class Logger
     * @brief The main logger class responsible for handling log messages.
     *
     * Each Logger instance can be configured with its own log level and sinks.
     * It is designed for high performance and thread-safety.
     */
    class Logger
    {
    public:
        /**
         * @brief Constructs a logger with a given name and default log level.
         * @param name The name of the logger instance.
         * @param level The initial minimum log level to process.
         */
        explicit Logger(std::string name, LogLevel level = LogLevel::Info);

        /**
         * @brief Destructor.
         */
        ~Logger();

        // Disable copy operations to prevent accidental slicing and ensure unique ownership.
        Logger(const Logger &) = delete;
        Logger &operator=(const Logger &) = delete;

        // Custom move operations to handle atomic member
        Logger(Logger &&other) noexcept
            : m_name(std::move(other.m_name)),
              m_level(other.m_level.load(std::memory_order_relaxed))
        {
        }

        Logger &operator=(Logger &&other) noexcept
        {
            if (this != &other)
            {
                m_name = std::move(other.m_name);
                m_level.store(other.m_level.load(std::memory_order_relaxed),
                              std::memory_order_relaxed);
            }
            return *this;
        }

        /**
         * @brief Sets the minimum log level for this logger instance.
         *
         * Messages with a severity lower than this level will be filtered out.
         * This operation is thread-safe.
         *
         * @param level The new minimum log level.
         */
        void set_level(LogLevel level);

        /**
         * @brief Gets the current minimum log level for this logger.
         * @return The current LogLevel.
         */
        LogLevel level() const;

        /**
         * @brief Returns the name of the logger instance.
         * @return The logger's name.
         */
        const std::string &name() const;

    private:
        std::string m_name;
        std::atomic<LogLevel> m_level;
    };

} // namespace vs

#endif // VS_LOGGER_HPP