#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>


int main(int argc, char** argv) {
    const char* outputFile = argv[1];
    int numSymbols = atoi(argv[2]);

    std::ofstream fout(outputFile, std::ios::binary);

    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < numSymbols; ++i) {
        fout << char(65 + rand() % 25);
    }

    return 0;
}
