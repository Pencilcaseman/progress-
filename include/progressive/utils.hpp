#pragma once

#include <chrono>

namespace prog::detail {
	namespace colors {
		inline auto number	  = fmt::fg(fmt::color::orange) | fmt::emphasis::bold;
		inline auto separator = fmt::fg(fmt::color::dark_gray) | fmt::emphasis::bold;
	} // namespace colors

	double time() {
		auto ns = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		return double(ns) * 1e-9;
	}

	void sleep(double seconds) {
		double start = time();
		while (time() - start < seconds) {}
	}

	std::string formatTime(double seconds, int &width) {
		int hours = int(seconds / 3600.0);
		seconds -= hours * 3600.0;
		int minutes = int(seconds / 60.0);
		seconds -= minutes * 60.0;

		std::string result;

		result += fmt::format(colors::number, "{:02}", hours);
		result += fmt::format(colors::separator, ":");
		result += fmt::format(colors::number, "{:02}", minutes);
		result += fmt::format(colors::separator, ":");
		result += fmt::format(colors::number, "{:0>6.3f}", seconds);

		width = 2 + 1 + 2 + 1 + 7;

		return result;

		return fmt::format("{:02}:{:02}:{:02.3f}", hours, minutes, seconds);
	}
} // namespace prog::detail