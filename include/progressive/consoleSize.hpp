#pragma once

#include <progressive/common.hpp>

namespace prog::detail {
	struct ConsoleSize {
		int rows;
		int cols;
	};

	ConsoleSize consoleSize() {
#if defined(PROG_OSX)
		struct winsize w {};
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		return {w.ws_row, w.ws_col};
#elif defined(PROG_LINUX)
		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		return {w.ws_row, w.ws_col};
#elif defined(PROG_WINDOWS)
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return {csbi.srWindow.Bottom - csbi.srWindow.Top + 1,
				csbi.srWindow.Right - csbi.srWindow.Left + 1};
#else
		return {24, 80};
#endif
	}
}
