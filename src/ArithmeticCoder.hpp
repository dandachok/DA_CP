#pragma once

#include <algorithm>
#include <cstdint>
#include "BitIoStream.hpp"
#include "FrequencyTable.hpp"

class ArithmeticCoderBase {
public: 
	explicit ArithmeticCoderBase(int numBits);
	virtual ~ArithmeticCoderBase() = 0;

protected: 

	int numStateBits;
	std::uint64_t fullRange;
	std::uint64_t halfRange;
	std::uint64_t quarterRange;
	std::uint64_t minimumRange;
	std::uint64_t maximumTotal;
	std::uint64_t stateMask;
	std::uint64_t low;
	std::uint64_t high;	
	
	virtual void update(const FrequencyTable &freqs, std::uint32_t symbol);
	virtual void shift() = 0;
	virtual void underflow() = 0;
};


class ArithmeticDecoder final : private ArithmeticCoderBase {
public: 
	explicit ArithmeticDecoder(int numBits, BitInputStream &in);
	std::uint32_t read(const FrequencyTable &freqs);

protected:
	void shift() override;
	void underflow() override;

private:
	BitInputStream &input;
	std::uint64_t code;

	int readCodeBit();
};


class ArithmeticEncoder final : private ArithmeticCoderBase {

public: 
	explicit ArithmeticEncoder(int numBits, BitOutputStream &out);
	void write(const FrequencyTable &freqs, std::uint32_t symbol);
	void finish();

protected: 
	void shift() override;
	void underflow() override;

private: 
	BitOutputStream &output;
	unsigned long numUnderflow;
};
