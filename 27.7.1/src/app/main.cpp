#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <random>
#include <domain/Logger.h>
#include <infrastructure/DatabaseSimulator.h>
#include <entities/LogEntry.h>
#include <windows.h>
using namespace std::chrono;
using domain::Logger;
using entities::LogEntry;
void userThread(Logger &logger, infrastructure::DatabaseSimulator &db, int id)
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    std::mt19937 rng(id);
    std::uniform_int_distribution<int> dist(100, 500);
    for (int i = 0; i < 5; ++i)
    {
        LogEntry entry;
        entry.author = "User" + std::to_string(id);
        entry.message = "Message " + std::to_string(i);
        entry.timestamp = system_clock::now();
        logger.write(entry);
        db.save(entry);
        std::this_thread::sleep_for(milliseconds(dist(rng)));
    }
}
void readerThread(Logger &logger)
{
    std::string line;
    while (logger.readLine(line))
    {
        std::cout << "LogReader: " << line << std::endl;
        std::this_thread::sleep_for(milliseconds(200));
    }
}
int main()
{
    Logger logger("log.txt");
    infrastructure::DatabaseSimulator db;
    std::vector<std::thread> threads;
    for (int i = 1; i <= 5; ++i)
        threads.emplace_back(userThread, std::ref(logger), std::ref(db), i);
    threads.emplace_back(readerThread, std::ref(logger));
    for (auto &t : threads)
        t.join();
    auto all = db.fetchAll();
    std::cout << "Всего сообщений в БД: " << all.size() << std::endl;
    return 0;
}
