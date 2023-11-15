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

		const T &get() const { return m_current; }
		T &get() { return m_current; }

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

			std::string counter = fmt::format("{}/{}", m_current, m_end);

			float progress = float(m_current) / float(m_end);

			std::string percentStr =
			  fmt::format(detail::colors::percent, "{:>6.2f}%", progress * 100.0f);

			int barWidth = size.cols - elapsedWidth - remainingTimeWidth - counter.length() - 6 - 8;
			if (barWidth < 0) barWidth = 1;
			std::string bar = m_charset.bar(progress, barWidth);

			return fmt::format(
			  detail::colors::separator, "{}|{}| {} {}", percentStr, bar, counter, info);
		}

	private:
		T m_current;
		T m_end;
		double m_prevUpdate = 0;
		double m_start		= 0;

		CharSet m_charset = defaultCharSet();
	};
} // namespace prog
