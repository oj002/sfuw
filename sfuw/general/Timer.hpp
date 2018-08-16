#ifndef _SFUW_TIMER_HPP
#define _SFUW_TIMER_HPP
#include <chrono>

namespace sfuw
{
	struct Timer
	{
		using Clock = std::conditional<std::chrono::high_resolution_clock::is_steady,
												std::chrono::high_resolution_clock,
												std::chrono::steady_clock>::type;
		Clock::time_point m_start;
		
		Timer() noexcept
			: m_start(Clock::now())
		{}

		void restart() noexcept { m_start = Clock::now(); }

		template<typename T, typename T_duration = std::ratio<1>>
		T restart() noexcept
		{
			const Clock::time_point old = m_start;
			m_start = Clock::now();
			const std::chrono::duration<T, T_duration> elapsedTime = m_start - old;
			return elapsedTime.count();
		}

		template<typename T, typename T_duration = std::ratio<1>>
		T getElapsedTime() noexcept
		{
			const std::chrono::duration<T, T_duration> elapsedTime = Clock::now() - m_start;
			return elapsedTime.count();
		}
	};
}  // namespace sfuw
#endif // _SFUW_TIMER_HPP