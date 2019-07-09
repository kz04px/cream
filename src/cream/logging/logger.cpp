#include <iostream>
#include <mutex>
#include "../utilities/utilities.hpp"
#include "logging.hpp"

std::mutex mtx;

namespace cream {

Logger::Logger(const std::string filename) {
    file_.open(filename, std::ofstream::out | std::ofstream::app);
    file_ << "**** BEGIN LOGGING ON " << utilities::current_date() << " "
          << utilities::current_time() << std::endl;
}

Logger::~Logger() {
    file_ << "**** END LOGGING ON " << utilities::current_date() << " " << utilities::current_time()
          << std::endl
          << std::endl;
}

Logger &Logger::get_instance() {
    static Logger log("log.txt");
    return log;
}

void Logger::debug(const std::string text) {
    mtx.lock();
    std::cout << "DEBUG: " << text << std::endl;
    file_ << "[" << utilities::current_time() << "]  [DEBUG]  " << text << std::endl;
    mtx.unlock();
}

void Logger::info(const std::string text) {
    mtx.lock();
    std::cout << "INFO: " << text << std::endl;
    file_ << "[" << utilities::current_time() << "]  [INFO]  " << text << std::endl;
    mtx.unlock();
}

void Logger::warning(const std::string text) {
    mtx.lock();
    std::cout << "WARNING: " << text << std::endl;
    file_ << "[" << utilities::current_time() << "]  [WARNING]  " << text << std::endl;
    mtx.unlock();
}

void Logger::error(const std::string text) {
    mtx.lock();
    std::cout << "ERROR: " << text << std::endl;
    file_ << "[" << utilities::current_time() << "]  [ERROR]  " << text << std::endl;
    mtx.unlock();
}

}  // namespace cream
