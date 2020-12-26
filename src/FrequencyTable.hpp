#pragma once

#include <cstdint>
#include <vector>

class FrequencyTable {
public:
	virtual ~FrequencyTable() = 0;

	virtual std::uint32_t getSymbolLimit() const = 0;
	virtual std::uint32_t get(std::uint32_t symbol) const = 0;
	virtual std::uint32_t getTotal() const = 0;
	virtual std::uint32_t getLow(std::uint32_t symbol) const = 0;
	virtual std::uint32_t getHigh(std::uint32_t symbol) const = 0;

	virtual void set(std::uint32_t symbol, std::uint32_t freq) = 0;
	virtual void increment(std::uint32_t symbol) = 0;
};



class FlatFrequencyTable final : public FrequencyTable {
public:
	explicit FlatFrequencyTable(std::uint32_t numSyms);
	
	std::uint32_t getSymbolLimit() const override;
	std::uint32_t get(std::uint32_t symbol) const override;
	std::uint32_t getTotal() const override;
	std::uint32_t getLow(std::uint32_t symbol) const override;
	std::uint32_t getHigh(std::uint32_t symbol) const override;

	void set(std::uint32_t symbol, std::uint32_t freq) override;
	void increment(std::uint32_t symbol) override;

private:
	std::uint32_t numSymbols;

	void checkSymbol(std::uint32_t symbol) const;
};


class SimpleFrequencyTable final : public FrequencyTable {
public: 
	explicit SimpleFrequencyTable(const std::vector<std::uint32_t> &freqs);
	explicit SimpleFrequencyTable(const FrequencyTable &freqs);

	std::uint32_t getSymbolLimit() const override;
	std::uint32_t get(std::uint32_t symbol) const override;
	std::uint32_t getTotal() const override;
	std::uint32_t getLow(std::uint32_t symbol) const override;
	std::uint32_t getHigh(std::uint32_t symbol) const override;

	void set(std::uint32_t symbol, std::uint32_t freq) override;
	void increment(std::uint32_t symbol) override;
	
private: 
	std::vector<std::uint32_t> frequencies;
	mutable std::vector<std::uint32_t> cumulative;
	std::uint32_t total;

	void initCumulative(bool checkTotal=true) const;
	
	static std::uint32_t checkedAdd(std::uint32_t x, std::uint32_t y);	
};
