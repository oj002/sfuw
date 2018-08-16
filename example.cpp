#include "sfuw/general/Timer.hpp"
#include "sfuw/general/Rng_std.hpp"
#include "sfuw/threading/ThreadPool.hpp"

int main()
{
    sfuw::Timer t;

    {
        sfuw::Rng_std<> rng;
        std::printf("testing random real between 0 and 1: %f\n", rng.next<double>(0.0, 1.0));
    }
    {
        sfuw::ThreadPool pool{5};
        
        auto f1 = pool.push([]{
            return 1;
        });
        auto f2 = pool.push([]{
            return 2;
        });

        std::printf("testing ThreadPool %d\n", f1.get() + f2.get());
    }

    std::printf("\nExecution took %f nanoseconds\n", t.getElapsedTime<double, std::nano>());
    return 0;
}