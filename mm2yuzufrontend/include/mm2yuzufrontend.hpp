#pragma once

#include <string>
#include <vector>

namespace MM2YuzuFrontend {
	namespace Parser {
		std::vector<uint8_t> DecryptSaveDat(std::vector<uint8_t>& input);
		std::vector<uint8_t> EncryptSaveDat(std::vector<uint8_t>& input);
		void EnableLevel(std::vector<uint8_t>& input, int level);
		void DisableLevel(std::vector<uint8_t>& input, int level);
	}

	namespace Debug {
		std::string SaveDatInfo(std::vector<uint8_t>& input);
	}
}