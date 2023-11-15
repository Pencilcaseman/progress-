#pragma once

#include <vector>
#include <string>

namespace prog {
	class CharSet {
	public:
		CharSet()				 = default;
		CharSet(const CharSet &) = default;
		CharSet(CharSet &&)		 = default;

		CharSet &operator=(const CharSet &) = default;
		CharSet &operator=(CharSet &&)		= default;

		[[nodiscard]] const std::string &empty() const { return m_emptyChar; }
		[[nodiscard]] std::string &empty() { return m_emptyChar; }

		[[nodiscard]] const std::vector<std::string> &intermediate() const {
			return m_intermediate;
		}
		[[nodiscard]] std::vector<std::string> &intermediate() { return m_intermediate; }

		[[nodiscard]] const std::string &full() const { return m_fullChar; }
		[[nodiscard]] std::string &full() { return m_fullChar; }

		[[nodiscard]] std::string bar(float percent, int width) const {
			int fullBars  = static_cast<int>(percent * float(width));
			int emptyBars = width - fullBars - 1;

			float percentPerChar = 1.0f / float(width);
			percent -= percentPerChar * float(fullBars);
			int intermediateIndex = int(m_intermediate.size() * (percent / percentPerChar));

			std::string result;
			for (int i = 0; i < fullBars; ++i) { result += m_fullChar; }
			if (emptyBars > 0) result += m_intermediate[intermediateIndex];
			for (int i = 0; i < emptyBars; ++i) { result += m_emptyChar; }

			return result;
		}

	private:
		std::string m_emptyChar;
		std::vector<std::string> m_intermediate;
		std::string m_fullChar;
	};

	CharSet charsetDefault() {
		CharSet result;
		result.empty()		  = fmt::format("{}", " ");
		result.intermediate() = {
		  fmt::format(" "),
		  fmt::format("▏"),
		  fmt::format("▎"),
		  fmt::format("▍"),
		  fmt::format("▌"),
		  fmt::format("▋"),
		  fmt::format("▊"),
		  fmt::format("▉"),
		  fmt::format("█"),
		};
		result.full() = fmt::format("█");

		return result;
	}

	CharSet charsetFade() {
		CharSet result;
		result.empty()		  = fmt::format("{}", " ");
		result.intermediate() = {
		  fmt::format(" "),
		  fmt::format("░"),
		  fmt::format("▒"),
		  fmt::format("▓"),
		  fmt::format("█"),
		};
		result.full() = fmt::format("█");

		return result;
	}

	CharSet charsetAscii() {
		CharSet result;
		result.empty()		  = fmt::format("{}", " ");
		result.intermediate() = {
		  fmt::format(" "),
		  fmt::format("."),
		  fmt::format("o"),
		  fmt::format("O"),
		  fmt::format("0"),
		  fmt::format("@"),
		  fmt::format("#"),
		};
		result.full() = fmt::format("#");

		return result;
	}
} // namespace prog
