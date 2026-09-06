//
// Created by alex1 on 06.09.2026.
//
#include "stats.h"

#include <vector>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    if (argc == 0) {
        std::cout << "Please pass csv file with readings as a first argument" << "\n";
    }

    const auto filename = argv[0];
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    bool first = true;
    while (std::getline(file, line)) {
        if (first)
            first = false;
        else {

        }
    }
}
