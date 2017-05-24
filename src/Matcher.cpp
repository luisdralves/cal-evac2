#include "Matcher.h"

size_t levenshtein_distance(string s, string t) {
    return levenshtein_distance_aux(s.c_str(), s.size(), t.c_str(), t.size());
}
size_t levenshtein_distance_aux(const char* s, size_t n, const char* t, size_t m) {
    ++n; ++m;
    size_t* d = new size_t[n * m];

    memset(d, 0, sizeof(size_t) * n * m);

    for (size_t i = 1, im = 0; i < m; ++i, ++im)
    {
        for (size_t j = 1, jn = 0; j < n; ++j, ++jn)
        {
            if (s[jn] == t[im])
            {
                d[(i * n) + j] = d[((i - 1) * n) + (j - 1)];
            }
            else
            {
                d[(i * n) + j] = min(d[(i - 1) * n + j] + 1, /* A deletion. */
                                     min(d[i * n + (j - 1)] + 1, /* An insertion. */
                                         d[(i - 1) * n + (j - 1)] + 1)); /* A substitution. */
            }
        }
    }

    size_t r = d[n * m - 1];

    delete [] d;

    return r;
}

string closestStreet(set<pair<Street, pair<int, int>>> streets, string street) {
    set<string> streetsstr;
    for(auto i = streets.begin(); i != streets.end(); i++) {
        streetsstr.insert(i->first.getName());
    }
    if (streetsstr.find(street) != streetsstr.end())
        return street;

    vector<size_t> closeness;
    vector<string> streetsInOrder;
    for(string st : streetsstr) {
        closeness.push_back(levenshtein_distance(street, st));
        streetsInOrder.push_back(st);
    }

    string strtmp;
    size_t cltmp;
    for (int i = 0 ; i < streetsInOrder.size(); i++)
    {
        for (int j = 0 ; j < streetsInOrder.size() - 1; j++)
        {
            if (closeness[j] > closeness[j+1]) /* For decreasing order use < */
            {
                cltmp = closeness[j];
                closeness[j] = closeness[j+1];
                closeness[j+1] = cltmp;

                strtmp = streetsInOrder[j];
                streetsInOrder[j] = streetsInOrder[j+1];
                streetsInOrder[j+1] = strtmp;
            }
        }
    }
    string menuList = "";
    for (int i = 0; i < 3; i++) {
        menuList += streetsInOrder[i];
        menuList +=',';
    }
    menuList.erase(menuList.end() - 1, menuList.end());
    cout << "\nDid you mean...\n";
    int menu = getMenu(menuList);
    cin.ignore(1000, '\n');
    return streetsInOrder[menu-1];
}