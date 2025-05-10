#pragma once
#include "../entities/LogEntry.h"
#include <vector>
#include <mutex>
namespace infrastructure
{
    class DatabaseSimulator
    {
    public:
        void save(const entities::LogEntry &entry);
        std::vector<entities::LogEntry> fetchAll();

    private:
        std::vector<entities::LogEntry> storage_;
        std::mutex mutex_;
    };
}
