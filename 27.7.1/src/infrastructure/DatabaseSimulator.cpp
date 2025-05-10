#include "infrastructure/DatabaseSimulator.h"
void infrastructure::DatabaseSimulator::save(const entities::LogEntry &entry)
{
    std::lock_guard<std::mutex> guard(mutex_);
    storage_.push_back(entry);
}
std::vector<entities::LogEntry> infrastructure::DatabaseSimulator::fetchAll()
{
    std::lock_guard<std::mutex> guard(mutex_);
    return storage_;
}
