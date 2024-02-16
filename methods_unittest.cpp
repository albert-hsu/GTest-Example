#include "methods.hpp"
#include <gtest/gtest.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <chrono>

namespace {

TEST(Test, TestCase1Linear) {
    const Sequence seq = { 3, 17, 42, 1, 26, 8, 0 ,63 };
    Candidates cand;

    shortestSequences(seq, 80, cand);

    ASSERT_EQ(cand.size(), 2);
    ASSERT_EQ(cand.front().first, 1);
    ASSERT_EQ(cand.front().second, 4);
    ASSERT_EQ(cand.back().first, 4);
    ASSERT_EQ(cand.back().second, 7);
}

TEST(Test, TestCase1BruteForce) {
    const Sequence seq = { 3, 17, 42, 1, 26, 8, 0 ,63 };
    Candidates cand;

    shortestSequencesBruteForce(seq, 80, cand);

    ASSERT_EQ(cand.size(), 2);
    ASSERT_EQ(cand.front().first, 1);
    ASSERT_EQ(cand.front().second, 4);
    ASSERT_EQ(cand.back().first, 4);
    ASSERT_EQ(cand.back().second, 7);
}

TEST(Test, TestCase2Linear) {
    const Sequence seq = { 3, 17, 42, 1, 26, 8, 0 ,63 };
    Candidates cand;

    shortestSequences(seq, 76, cand);

    ASSERT_EQ(cand.size(), 3);
    ASSERT_EQ(cand.front().first, 1);
    ASSERT_EQ(cand.front().second, 4);
    cand.pop_front();
    ASSERT_EQ(cand.front().first, 2);
    ASSERT_EQ(cand.front().second, 5);
    ASSERT_EQ(cand.back().first, 4);
    ASSERT_EQ(cand.back().second, 7);
}

TEST(Test, TestCase2BruteForce) {
    const Sequence seq = { 3, 17, 42, 1, 26, 8, 0 ,63 };
    Candidates cand;

    shortestSequencesBruteForce(seq, 76, cand);

    ASSERT_EQ(cand.size(), 3);
    ASSERT_EQ(cand.front().first, 1);
    ASSERT_EQ(cand.front().second, 4);
    cand.pop_front();
    ASSERT_EQ(cand.front().first, 2);
    ASSERT_EQ(cand.front().second, 5);
    ASSERT_EQ(cand.back().first, 4);
    ASSERT_EQ(cand.back().second, 7);
}

TEST(Test, TestCase3Linear) {
    const Sequence seq = { 3, 17, 42, 1, 26, 8, 0 ,63 };
    Candidates cand;

    shortestSequences(seq, 70, cand);

    ASSERT_EQ(cand.size(), 1);
    ASSERT_EQ(cand.front().first, 5);
    ASSERT_EQ(cand.front().second, 7);
}

TEST(Test, TestCase3BruteForce) {
    const Sequence seq = { 3, 17, 42, 1, 26, 8, 0 ,63 };
    Candidates cand;

    shortestSequencesBruteForce(seq, 70, cand);

    ASSERT_EQ(cand.size(), 1);
    ASSERT_EQ(cand.front().first, 5);
    ASSERT_EQ(cand.front().second, 7);
}

TEST(Test, TestCase4Linear) {
    const Sequence seq(1E7, 1);
    Candidates cand;

    shortestSequences(seq, 1, cand);

    ASSERT_EQ(cand.size(), 1E7);
    Index i = 0;
    for (auto it = cand.begin(); it != cand.end(); ++it) {
        ASSERT_EQ(it->first, i);
        ASSERT_EQ(it->second, i);
        ++i;
    }
}

TEST(Test, TestCase4BruteForce) {
    const Sequence seq(1E7, 1);
    Candidates cand;

    shortestSequencesBruteForce(seq, 1, cand);

    ASSERT_EQ(cand.size(), 1E7);
    Index i = 0;
    for (auto it = cand.begin(); it != cand.end(); ++it) {
        ASSERT_EQ(it->first, i);
        ASSERT_EQ(it->second, i);
        ++i;
    }
}

TEST(Test, TestCase5Linear) {
    const Sequence seq(1E3, 1);
    Candidates cand;

    shortestSequences(seq, 1E3 + 1, cand);

    ASSERT_TRUE(cand.empty());
}

TEST(Test, TestCase5BruteForce) {
    const Sequence seq(1E3, 1);
    Candidates cand;

    shortestSequencesBruteForce(seq, 1E3 + 1, cand);

    ASSERT_TRUE(cand.empty());
}

TEST(Test, TestCase6Linear) {
    const Sequence seq(1E4, 1);
    Candidates cand;

    shortestSequences(seq, 4, cand);

    ASSERT_EQ(cand.size(), 1E4 - 3);
    Index i = 0;
    for (auto it = cand.begin(); it != cand.end(); ++it) {
        ASSERT_EQ(it->first, i);
        ASSERT_EQ(it->second, i + 3);
        ++i;
    }
}

TEST(Test, TestCase6BruteForce) {
    const Sequence seq(1E4, 1);
    Candidates cand;

    shortestSequencesBruteForce(seq, 4, cand);

    ASSERT_EQ(cand.size(), 1E4 - 3);
    Index i = 0;
    for (auto it = cand.begin(); it != cand.end(); ++it) {
        ASSERT_EQ(it->first, i);
        ASSERT_EQ(it->second, i + 3);
        ++i;
    }
}

TEST(Test, RandomTestCases) {
    std::srand(std::time(nullptr));

    for (int trial = 0; trial < 1E6; ++trial) {
        Sequence seq;

        for (Index i = 0; i < 50; ++i) {
            seq.push_back(std::rand() % 80);
        }

        Candidates cand1, cand2;
        const Type threshold = std::rand() % 2000;

        shortestSequences(seq, threshold, cand1);
        shortestSequencesBruteForce(seq, threshold, cand2);

        ASSERT_EQ(cand1.size(), cand2.size());
        for (auto it1 = cand1.begin(), it2 = cand2.begin(); it1 != cand1.end() && it2 != cand2.end(); ++it1, ++it2) {
            ASSERT_EQ(it1->first, it2->first);
            ASSERT_EQ(it1->second, it2->second);
            ASSERT_LE(it1->first, it1->second);
            Type sum = 0;
            for (Index i = it1->first; i <= it1->second; ++i) {
                sum += seq[i];
            }
            ASSERT_GE(sum, threshold);
        }
    }
}

}
