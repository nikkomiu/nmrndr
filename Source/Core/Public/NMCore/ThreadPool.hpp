#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool
{
public:

    ThreadPool(std::size_t numThreads) : stop(false)
    {
        for (std::size_t i = 0; i < numThreads; ++i)
        {
            workers.emplace_back([this] { this->RunTask(); });
        }
    }

    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& worker : workers)
        {
            worker.join();
        }
    }

    template <class F> void Enqueue(F&& f)
    {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            tasks.emplace(std::forward<F>(f));
        }
        condition.notify_one();
    }

    void Cancel()
    {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            cancel = true;
        }
        condition.notify_all();
    }

protected:

    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::mutex stopMutex;
    std::condition_variable condition;
    std::condition_variable stopCondition;
    bool cancel = false;
    bool stop = false;

    void RunTask()
    {
        while (true)
        {
            std::function<void()> task;

            {
                std::unique_lock<std::mutex> lock(queueMutex);
                condition.wait(lock, [this] { return stop || cancel || !tasks.empty(); });

                if ((stop && tasks.empty()) || cancel)
                {
                    return;
                }

                task = std::move(tasks.front());
                tasks.pop();
            }

            task();
        }
    }

    void WaitForStop()
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stopCondition.wait(lock, [this] { return stop || cancel; });
    }
};
