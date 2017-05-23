#ifndef MATCHER_H
#define MATCHER_H

#include <iostream>
#include <cstring>

using namespace std;

size_t levenshtein_distance(string s, string t);
size_t levenshtein_distance_aux(const char* s, size_t n, const char* t, size_t m);

#endif //CAL_URGENCIAS_MATCHER_H
