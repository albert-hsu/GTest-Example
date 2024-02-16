#include "methods.hpp"
#include <string>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <chrono>

void usage() {
    char message[] = 
        "Usage:\n"
        "   $ cat test.txt\n"
        "   3\n"
        "   17\n"
        "   42\n"
        "   1\n"
        "   26\n"
        "   8\n"
        "   0\n"
        "   63\n"
        "   $ peak 80 test.txt\n"
        "   17 42 1 26\n"
        "   26 8 0 63\n"
        "   duration: 1130 ns\n";

    std::cerr << message;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        usage();
        return EXIT_FAILURE;
    }

    Sequence sequence;
    Type threshold;
    Candidates candidates;

    try {
        threshold = std::stoi(argv[1]);
    } catch (...) {
        usage();
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[2], "r");
    if (fp == NULL) {
        usage();
        return EXIT_FAILURE;
    }
    int val;
    while (fscanf(fp, "%d", &val) != EOF) {
        sequence.push_back(val);
    }
    fclose(fp);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    shortestSequences(sequence, threshold, candidates);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    for (auto it = candidates.begin(); it != candidates.end(); ++it) {
        for (Index i = it->first; i <= it->second; ++i) {
            std::cout << sequence[i];
            if (i < it->second) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "duration: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ns" << std::endl;

    return EXIT_SUCCESS;
}
