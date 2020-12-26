import random
import sys

if __name__ == "__main__":
    inputFile = sys.argv[1]
    numSymbols = int(sys.argv[2])

    with open(inputFile, 'wb') as fout:
        for i in range(numSymbols):
            fout.write(bytes([random.randint(0, 255)]))

