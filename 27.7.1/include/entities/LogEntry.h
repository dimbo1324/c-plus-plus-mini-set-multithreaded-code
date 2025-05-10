#pragma once
#include <string>
#include <chrono>
namespace entities
{
    struct LogEntry
    {
        std::string author;
        std::string message;
        std::chrono::system_clock::time_point timestamp;
    };
}
