#pragma once

#include <string>
#include <vector>

namespace MM2YuzuFrontend {
	namespace Parser {
		std::vector<uint8_t> DecryptSaveDat(std::vector<uint8_t> input);
	}

	namespace Debug {
		std::string SaveDatInfo(std::vector<uint8_t> input);
	}
}