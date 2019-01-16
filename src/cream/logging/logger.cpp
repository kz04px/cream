#include <iostream>
#include "logging.hpp"
#include "../utilities/utilities.hpp"

namespace cream
{
    Logger::Logger(const std::string filename)
    {
        file_.open(filename, std::ofstream::out | std::ofstream::app);
        file_ << "**** BEGIN LOGGING ON " << utilities::current_date() << " " << utilities::current_time() << std::endl;
    }

    Logger::~Logger()
    {
        file_ << "**** END LOGGING ON " << utilities::current_date() << " " << utilities::current_time() << std::endl << std::endl;
    }

    void Logger::debug(const std::string text)
    {
        file_ << "[" << utilities::current_time() << "]  [DEBUG]  " << text << std::endl;
    }

    void Logger::info(const std::string text)
    {
        file_ << "[" << utilities::current_time() << "]  [INFO]  " << text << std::endl;
    }

    void Logger::warning(const std::string text)
    {
        file_ << "[" << utilities::current_time() << "]  [WARNING]  " << text << std::endl;
    }

    void Logger::error(const std::string text)
    {
        file_ << "[" << utilities::current_time() << "]  [ERROR]  " << text << std::endl;
    }
}
