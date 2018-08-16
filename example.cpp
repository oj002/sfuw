#include "sfuw/general/Timer.hpp"
#include "sfuw/general/Rng_std.hpp"

int main()
{
    sfuw::Timer t;

    {
        sfuw::Rng_std<> rng;
        std::printf("testing random real between 0 and 1: %f\n", rng.next<double>(0.0, 1.0));
    }

    std::printf("\nExecution took %f nanoseconds\n", t.getElapsedTime<double, std::nano>());
    return 0;
}