#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>
#include "ArithmeticCoder.hpp"
#include "BitIoStream.hpp"
#include "FrequencyTable.hpp"

using std::uint32_t;


int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " InputFile OutputFile" << std::endl;
		return EXIT_FAILURE;
	}
	const char *inputFile  = argv[1];
	const char *outputFile = argv[2];
	
	std::ifstream in(inputFile, std::ios::binary);
	std::ofstream out(outputFile, std::ios::binary);
	BitInputStream bin(in);
	try {
		
		SimpleFrequencyTable freqs(std::vector<uint32_t>(257, 0));
		for (uint32_t i = 0; i < 256; i++) {
			uint32_t freq = 0;
			for (int j = 0; j < 32; j++)
				freq = (freq << 1) | bin.readNoEof();
			freqs.set(i, freq);
		}
		freqs.increment(256);
		
		ArithmeticDecoder dec(32, bin);
		while (true) {
			uint32_t symbol = dec.read(freqs);
			if (symbol == 256)
				break;
			int b = static_cast<int>(symbol);
			if (std::numeric_limits<char>::is_signed)
				b -= (b >> 7) << 8;
			out.put(static_cast<char>(b));
		}
		return EXIT_SUCCESS;
		
	} catch (const char *msg) {
		std::cerr << msg << std::endl;
		return EXIT_FAILURE;
	}
}
