#ifndef __METHODS_H__
#define __METHODS_H__

#include <cstdint>
#include <algorithm>
#include <vector>
#include <list>
#include <utility>

typedef int_fast32_t Type;
typedef uint_fast32_t Index;
typedef uint_fast32_t Length;
typedef std::vector<Type> Sequence;
typedef std::list<std::pair<Index, Index>> Candidates;

void shortestSequences(const Sequence& sequence, Type threshold, Candidates& candidates);
void shortestSequencesBruteForce(const Sequence& sequence, Type threshold, Candidates& candidates);

#endif
