#ifndef _SFUW_RNG_STD_HPP
#define _SFUW_RNG_STD_HPP

#include <cstdio>
#include <chrono>
#include <random>

namespace sfuw
{
	template<typename T_RandomEngine = std::mt19937>
	class Rng_std
	{
	public:
		T_RandomEngine				   engine;

	public:
		Rng_std() noexcept
			: engine(static_cast<unsigned int>(
				std::chrono::steady_clock::now().time_since_epoch().count()))
		{}

		explicit Rng_std(unsigned int seed) noexcept
			: engine(seed)
		{}

		template<typename T, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
		T next(T min = std::numeric_limits<T>::min(),
			   T max = std::numeric_limits<T>::max()) noexcept
		{
			try
			{
				static std::uniform_int_distribution<T> dist(min, max);
				return dist(engine);
			}
			catch (...)
			{
				std::fprintf(stderr, "exception caught in rng_std::next, returning min");
				return min;
			}
		}
		template<typename T,
				 typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
		T next(T min = std::numeric_limits<T>::min(),
			   T max = std::numeric_limits<T>::max()) noexcept
		{
			try
			{
				static std::uniform_real_distribution<T> dist(min, max);
				return dist(engine);
			}
			catch (...)
			{
				std::fprintf(stderr, "exception caught in rng_std::next, returning min");
				return min;
			}
		}
	};
} // namespace sfuw
#endif // _SFUW_RNG_STD_HPP