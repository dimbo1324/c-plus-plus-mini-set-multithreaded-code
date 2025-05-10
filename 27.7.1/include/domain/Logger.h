#pragma once
#include <fstream>
#include <shared_mutex>
#include <string>
#include <entities/LogEntry.h>
namespace domain
{
    class Logger
    {
    public:
        explicit Logger(const std::string &filename);
        ~Logger();
        void write(const entities::LogEntry &entry);
        bool readLine(std::string &out_line);

    private:
        std::fstream file_;
        mutable std::shared_mutex mutex_;
    };
}
