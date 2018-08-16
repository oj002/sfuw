#ifndef _SFUW_TIMER_HPP
#define _SFUW_TIMER_HPP
#include <chrono>

namespace svuw
{
	class Timer
	{
	public:
		using internal_clock = std::conditional<std::chrono::high_resolution_clock::is_steady,
												std::chrono::high_resolution_clock,
												std::chrono::steady_clock>::type;

	public:
		Timer() noexcept
			: m_start(internal_clock::now())
		{}

		void restart() noexcept { m_start = internal_clock::now(); }

		template<typename T, typename T_duration = std::ratio<1>>
		T restart() noexcept
		{
			const internal_clock::time_point old = m_start;
			m_start = internal_clock::now();
			const std::chrono::duration<T, T_duration> elapsedTime = m_start - old;
			return elapsedTime.count();
		}

		template<typename T, typename T_duration = std::ratio<1>>
		T getElapsedTime() noexcept
		{
			const std::chrono::duration<T, T_duration> elapsedTime = internal_clock::now() - m_start;
			return elapsedTime.count();
		}

	private:
		internal_clock::time_point m_start;
	};
}  // namespace svuw
#endif // _SFUW_TIMER_HPP