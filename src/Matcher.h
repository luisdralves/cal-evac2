#ifndef MATCHER_H
#define MATCHER_H

#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include "menus.h"
#include "Street.h"

using namespace std;

size_t levenshtein_distance(string s, string t);
size_t levenshtein_distance_aux(const char* s, size_t n, const char* t, size_t m);

string closestStreet(set<pair<Street, pair<int, int>>> streets, string street);

#endif
