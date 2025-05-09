## 🚀 c-plus-plus-mini-set-multithreaded-code

Этот репозиторий демонстрирует основные приёмы многопоточного программирования на примере нескольких алгоритмов и структур данных.

---

## 📂 Структура репозитория

- `28.9.1/` — **Parallel Merge Sort**

  - `app/main.cpp` — генерация случайного массива и вызов `parallelMergeSort`
  - `lib/merge_sort.hpp`, `lib/merge_sort.cpp` — реализация многопоточной и последовательной сортировки слиянием

- `29.7.1/` — **Fine-Grained Concurrent Queue**

  - `app/main.cpp` — демонстрация вставки элементов в середину очереди
  - `lib/FineGrainedQueue.hpp`, `lib/FineGrainedQueue.cpp` — реализация очереди с блокировками на узлах (fine-grained locking)

- `30.7.1/` — **Parallel QuickSort с ThreadPool**

  - `src/app/main.cpp` — сравнение скорости параллельного QuickSort и `std::sort`
  - `src/lib/QuickSort.hpp`, `src/lib/QuickSort.cpp` — асинхронная и синхронная реализация QuickSort
  - `src/lib/ThreadPool.hpp`, `src/lib/ThreadPool.cpp` — простой пул потоков для выполнения задач

---

## ✨ Основные возможности и фишки

### 🛠 Многопоточная сортировка слиянием

- Автоматическое создание потоков через `std::async` до уровня `hardware_concurrency()`
- Управление максимальным количеством активных потоков через `std::atomic`
- Спортивная скорость на больших наборах данных

### 🔒 Fine-Grained Concurrent Queue

- Вставка в произвольную позицию без глобальной блокировки
- Блокировка каждого узла (`std::mutex node_mutex`), минимизация зон критических секций
- Лёгкая и безопасная работа в конкурентной среде

### 🌀 Параллельный QuickSort + ThreadPool

- Асинхронные рекурсивные задачи с порогом `ASYNC_THRESHOLD` для переключения между синхронным и асинхронным разделением
- Пул потоков (`ThreadPool`) с возможностью конфигурирования числа рабочих
- Выбор между `std::sort` и собственной реализацией на базе пула

---

## 📝 Как собрать и запустить

### Требования

- Компилятор с поддержкой C++17 или выше
- Windows (для `SetConsoleCP`/`SetConsoleOutputCP`) или удаление вызовов на других платформах

### Сборка

```bash
# Перейдите в нужную папку и выполните сборку (пример для CMake)
mkdir build && cd build
cmake ..
cmake --build .
```

### Запуск

```bash
# Например, для Parallel Merge Sort
./app/ParallelMergeSort.exe
```

---

## 💡 Контакты

Если у вас есть вопросы или предложения, свяжитесь со мной:

- Email: [dim4dmi7rij@yandex.ru](dim4dmi7rij@yandex.ru)
- Telegram: @dimbo1324

---

## 📜 Лицензия

MIT License © dimbo1324
