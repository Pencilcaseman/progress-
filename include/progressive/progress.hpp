#pragma once

#include <iostream>

namespace prog {
	template<typename T>
	class Progress {
	public:
		Progress() : m_start(detail::time()) {}
		Progress(const Progress &) = default;
		Progress(Progress &&)	   = default;

		Progress &operator=(const Progress &) = default;
		Progress &operator=(Progress &&)	  = default;

		explicit Progress(T initial) : m_current(initial), m_start(detail::time()) {}

		~Progress() {
			update(true);
			std::cout << std::endl;
		}

		bool operator<(const T &other) {
			m_end = other;
			return m_current < other;
		}

		bool operator>(const T &other) {
			m_end = other;
			return m_current > other;
		}

		bool operator<=(const T &other) {
			m_end = other;
			return m_current <= other;
		}

		bool operator>=(const T &other) {
			m_end = other;
			return m_current >= other;
		}

		bool operator==(const T &other) {
			m_end = other;
			return m_current == other;
		}

		bool operator!=(const T &other) {
			m_end = other;
			return m_current != other;
		}

		Progress &operator++() {
			++m_current;
			update();
			return *this;
		}

		Progress &operator++(int) {
			++m_current;
			update();
			return *this;
		}

		void update(bool force = false) {
			double now = detail::time();

			// Update every 25ms
			if (force || now - m_prevUpdate > 0.025) {
				m_prevUpdate = now;
				fmt::print("{}\r", generateBar());
				std::fflush(nullptr);
			}
		}

		[[nodiscard]] std::string generateBar() const {
			detail::ConsoleSize size = detail::consoleSize();
			double now				 = detail::time();
			double elapsed			 = now - m_start;
			double remainingTime	 = elapsed / float(m_current) * float(m_end - m_current);

			int elapsedWidth	   = 0;
			int remainingTimeWidth = 0;

			std::string elapsedStr	 = detail::formatTime(elapsed, elapsedWidth);
			std::string remainingStr = detail::formatTime(remainingTime, remainingTimeWidth);

			std::string info =
			  fmt::format(detail::colors::separator, "[{} | {}]", elapsedStr, remainingStr);

			float progress = float(m_current) / float(m_end);
			int barWidth   = size.cols - elapsedWidth - remainingTimeWidth - 4;
			if (barWidth < 0) barWidth = 1;
			std::string bar = m_charset.bar(progress, barWidth);

			return fmt::format("{} {}", bar, info);
		}

	private:
		T m_current;
		T m_end;
		double m_prevUpdate = 0;
		double m_start		= 0;

		CharSet m_charset = defaultCharSet();
	};
} // namespace prog
