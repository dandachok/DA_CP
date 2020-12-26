#pragma once

#include <istream>
#include <ostream>

class BitInputStream final {
public:
	explicit BitInputStream(std::istream &in);
	int read();
	int readNoEof();

private:	
	std::istream &input;
	int currentByte;
	int numBitsRemaining;
};


class BitOutputStream final {
public: 
	explicit BitOutputStream(std::ostream &out);
	void write(int b);
	void finish();
	
private: 
	std::ostream &output;
	int currentByte;
	int numBitsFilled;
};
