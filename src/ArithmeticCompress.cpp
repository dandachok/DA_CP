#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
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
	SimpleFrequencyTable freqs(std::vector<uint32_t>(257, 0));
	freqs.increment(256);
	while (true) {
		int b = in.get();
		if (b == EOF)
			break;
		if (b < 0 || b > 255)
			throw std::logic_error("Assertion error");
		freqs.increment(static_cast<uint32_t>(b));
	}
	
	in.clear();
	in.seekg(0);
	std::ofstream out(outputFile, std::ios::binary);
	BitOutputStream bout(out);
	try {
		
		for (uint32_t i = 0; i < 256; i++) {
			uint32_t freq = freqs.get(i);
			for (int j = 31; j >= 0; j--)
				bout.write(static_cast<int>((freq >> j) & 1));  // Big endian
		}
		
		ArithmeticEncoder enc(32, bout);
		while (true) {
			int symbol = in.get();
			if (symbol == EOF)
				break;
			if (symbol < 0 || symbol > 255)
				throw std::logic_error("Assertion error");
			enc.write(freqs, static_cast<uint32_t>(symbol));
		}
		
		enc.write(freqs, 256);
		enc.finish();
		bout.finish();
		return EXIT_SUCCESS;
		
	} catch (const char *msg) {
		std::cerr << msg << std::endl;
		return EXIT_FAILURE;
	}
}
