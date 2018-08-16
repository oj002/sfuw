#ifndef _SFUW_THREAD_POOL_HPP
#define _SFUW_THREAD_POOL_HPP

#include <condition_variable>
#include <functional>
#include <future>
#include <queue>
#include <thread>
#include <vector>

namespace sfuw
{
    class ThreadPool
    {
    public:
        using Task = std::function<void()>;
        
        explicit ThreadPool(std::size_t numThreads)
        {
            start(numThreads);
        }
        ~ThreadPool()
        {
            stop();
        }

        template <typename T>
        auto push(T task) -> std::future<decltype(task())>
        {
            auto wrapper = std::make_shared<std::packaged_task<decltype(task()) ()>>(std::move(task));
            {
                std::unique_lock<std::mutex> lock{eventMutex};
                tasks.emplace([=]{
                    (*wrapper)();
                });
            }
            eventVar.notify_one();
            return wrapper->get_future();
        }
    private:
        std::vector<std::thread> threads;

        std::condition_variable eventVar;
        std::mutex eventMutex;
        bool stopping{ false };

        std::queue<Task> tasks;

        void start(std::size_t numThreads)
        {
            threads.clear();
            for(std::size_t i{ 0 }; i < numThreads; ++i)
            {
                threads.emplace_back([=]{
                    while (true)
                    {
                        Task task;

                        {
                            std::unique_lock<std::mutex> lock{eventMutex};

                            eventVar.wait(lock, [=]{ return stopping || !tasks.empty(); });
                            if(stopping && tasks.empty()) break;
                            
                            task = std::move(tasks.front());
                            tasks.pop();
                        }

                        task();
                    }
                });
            }
        }
        void stop() noexcept
        {
            {
                std::unique_lock<std::mutex> lock{eventMutex};
                stopping = true;
            }

            eventVar.notify_all();

            for(auto &thread : threads)
            {
                thread.join();
            }
        }
    };
}
#endif // _SFUW_THREAD_POOL_HPP