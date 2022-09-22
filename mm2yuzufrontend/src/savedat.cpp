#include <iostream>
#include <iterator>
#include <mm2yuzufrontend.hpp>
#include <mm2yuzufrontend/keys.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include <aes.h>
}

#define STATE_SIZE 4
#define NUM_ROUNDS 4

#define SWAP(x)                                                                                    \
	((x >> 24) & 0xff | (x >> 8) & 0xff00 | (x << 8) & 0xff0000 | (x << 24) & 0xff000000)

void rand_init(uint32_t* rand_state, uint32_t in1, uint32_t in2, uint32_t in3, uint32_t in4) {
	int cond = in1 | in2 | in3 | in4;

	rand_state[0] = cond ? in1 : 1;
	rand_state[1] = cond ? in2 : 0x6C078967;
	rand_state[2] = cond ? in3 : 0x714ACB41;
	rand_state[3] = cond ? in4 : 0x48077044;
}

uint32_t rand_gen(uint32_t* rand_state) {
	uint32_t n    = rand_state[0] ^ rand_state[0] << 11;
	rand_state[0] = rand_state[1];
	n ^= n >> 8 ^ rand_state[3] ^ rand_state[3] >> 19;
	rand_state[1] = rand_state[2];
	rand_state[2] = rand_state[3];
	rand_state[3] = n;
	return n;
}

void gen_key(uint32_t* key_table, uint32_t* out_key, uint32_t* rand_state) {
	out_key[0] = 0;

	for(int i = 0; i < STATE_SIZE; i++) {
		for(int j = 0; j < NUM_ROUNDS; j++) {
			out_key[i] <<= 8;
			out_key[i]
				|= (key_table[rand_gen(rand_state) >> 26] >> ((rand_gen(rand_state) >> 27) & 24))
				   & 0xFF;
		}
	}
}

namespace MM2YuzuFrontend {
	namespace Parser {
		std::vector<uint8_t> DecryptSaveDat(std::vector<uint8_t> input) {
			// Correct size
			if(input.size() == 0xC000) {
				std::vector<uint8_t> dest;
				dest.reserve(input.size());
				std::copy(input.begin(), input.end(), std::back_inserter(dest));

				AES_ctx ctx;
				uint32_t rand_state[STATE_SIZE];
				uint32_t key_state[STATE_SIZE];

				uint8_t* end = dest.data() + 0xC000 - 0x30;

				rand_init(rand_state, *(uint32_t*)&end[0x10], *(uint32_t*)&end[0x14],
					*(uint32_t*)&end[0x18], *(uint32_t*)&end[0x1C]);
				gen_key(save_key_table, key_state, rand_state);

				AES_init_ctx_iv(&ctx, (uint8_t*)key_state, end);
				AES_CBC_decrypt_buffer(&ctx, dest.data(), 0xC000 - 0x30);

				return dest;
			}

			return {};
		}
	}

	namespace Debug {
		std::string SaveDatInfo(std::vector<uint8_t> input) {
			static const int SAVE_COURSE_OFFSET = 0xB920;

			std::string output;
			for(int index = 0; index <= 180; index++) {
				int loc = SAVE_COURSE_OFFSET + 0x11 + index * 8;

				std::string index_string = std::to_string(index);
				index_string.insert(0, 3 - index_string.length(), '0');

				output += "    " + index_string + (input[loc] ? ": Found" : ": Not found") + "\n";
			}
			return output;
		}
	}
}