GXX = g++
FLAGS = -O2 --std=c++11
FILES = BitIoStream.cpp FrequencyTable.cpp ArithmeticCoder.cpp

encoder:
	$(GXX) $(FLAGS) $(FILES) AdaptiveArithmeticCompress.cpp -o encoder

decoder:
	$(GXX) $(FLAGS) $(FILES) AdaptiveArithmeticDecompress.cpp -o decoder
