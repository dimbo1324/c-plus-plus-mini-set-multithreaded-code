#include "domain/Logger.h"
#include <stdexcept>
#include <iomanip>
#include <ctime>
#include <mutex>
#include <shared_mutex>
using namespace domain;
Logger::Logger(const std::string &filename)
    : file_(filename, std::ios::in | std::ios::out | std::ios::app)
{
    if (!file_.is_open())
        throw std::runtime_error("Не удалось открыть файл логов");
}
Logger::~Logger()
{
    file_.close();
}
void Logger::write(const entities::LogEntry &entry)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    auto t = std::chrono::system_clock::to_time_t(entry.timestamp);
    file_ << "[" << std::put_time(std::localtime(&t), "%F %T") << "] "
          << entry.author << ": " << entry.message << "\n";
    file_.flush();
}
bool Logger::readLine(std::string &out_line)
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return static_cast<bool>(std::getline(file_, out_line));
}
