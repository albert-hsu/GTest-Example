#include "methods.hpp"

// A varient of sliding window method (with bounds `left' and `right'). O(n) time and space complexities.
void shortestSequences(const Sequence& sequence, Type threshold, Candidates& candidates) {
#ifdef LEN
#error "multiple definition of `LEN'"
#endif
#define LEN(left, right) ((right) - (left) + 1)
    candidates.clear();

    Length minLen = sequence.size() + 1;
    Index left = 0, right = 0;
    Type sum = 0;

    // Advancing the `right' bound of the sliding window.
    for (; right < sequence.size(); ++right) {
        sum += sequence[right];
        if (sum >= threshold) {
            // Advancing the `left' bound if possible.
            for (; left < right && (LEN(left, right) > minLen || sum - sequence[left] >= threshold); ++left) {
                sum -= sequence[left];
            }
            if (sum >= threshold) {
                if (LEN(left, right) < minLen) {
                    // Expunging possible solutions that are not shortest.
                    minLen = LEN(left, right);
                    candidates.clear();
                }
                candidates.push_back(std::make_pair(left ,right));
            }
        }
    }
#undef LEN
}

// A brute-force method for examining the correctness of the LINEAR implementation above.
void shortestSequencesBruteForce(const Sequence& sequence, Type threshold, Candidates& candidates) {
    candidates.clear();

    for (Length len = 1; len <= sequence.size(); ++len) {
        for (Index left = 0; left + len - 1 < sequence.size(); ++left) {
            Type sum = 0;
            for (Index i = 0; i < len; ++i) {
                sum += sequence[left + i];
            }
            if (sum >= threshold) {
                if (candidates.back().second - candidates.back().first + 1 > len) {
                    candidates.clear();
                }
                candidates.push_back(std::make_pair(left, left + len - 1));
            }
        }
        if (!candidates.empty()) {
            return;
        }
    }
}
