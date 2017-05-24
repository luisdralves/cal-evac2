#include "Matcher.h"

bool kmp(string pattern, string target)
{
    int m = pattern.length();
    int n = target.length();
    int f[m];
    int o = pattern.length(), k;
    f[0] = -1;
    for (int i = 1; i < o; i++)
    {
        k = f[i - 1];
        while (k >= 0)
        {
            if (pattern[k] == pattern[i - 1])
                break;
            else
                k = f[k];
        }
        f[i] = k + 1;
    }
    int i = 0;
    int l = 0;
    while (i < n)
    {
        if (l == -1)
        {
            i++;
            l = 0;
        }
        else if (target[i] == pattern[l])
        {
            i++;
            l++;
            if (l == m)
                return 1;
        }
        else
            l = f[l];
    }
    return 0;
}

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

string exactStreet(set<pair<Street, pair<int, int>>> streets, string street) {
    set<string> streetsstr;
    for(auto i = streets.begin(); i != streets.end(); i++) {
        streetsstr.insert(i->first.getName());
    }
    if (streetsstr.find(street) != streetsstr.end())
        return street;

    vector<string> streetsContaining;
    for(string st : streetsstr) {
        if (kmp(street, st))
        streetsContaining.push_back(st);
    }

    string menuList = "";
    if(streetsContaining.size() > 0) {
        for (int i = 0; i < streetsContaining.size(); i++) {
            menuList += streetsContaining[i];
            menuList +=',';
        }
        menuList.erase(menuList.end() - 1, menuList.end());
        cout << "\nDid you mean...\n";
        int menu = getMenu(menuList);
        cin.ignore(1000, '\n');
        return streetsContaining[menu-1];
    } else {
        return "Unknown Location";
    }
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
    int veryCloseCounter = 0;
    int min = 20, max = 0;
    for (int i = 0; i < streetsInOrder.size(); i++) {
        if (closeness[i] < min) {
            min = closeness[i];
        }
        if (closeness[i] > max) {
            max = closeness[i];
        }
    }
    int med = (min + max) / 2;
    for (int i = 0; i < streetsInOrder.size(); i++) {
        if (closeness[i] < med) {
            veryCloseCounter++;
        }
    }
    veryCloseCounter++;
    if(veryCloseCounter > streetsInOrder.size()) {
        veryCloseCounter = streetsInOrder.size();
    }
    if(veryCloseCounter == 0) {
        veryCloseCounter = streetsInOrder.size();
        cout << "No similar streets found. ";
    }
    for (int i = 0; i < veryCloseCounter; i++) {
        menuList += streetsInOrder[i];
        menuList += to_string(closeness[i]);
        menuList +=',';
    }
    menuList.erase(menuList.end() - 1, menuList.end());
    cout << "Did you mean...\n";
    int menu = getMenu(menuList);
    cin.ignore(1000, '\n');
    return streetsInOrder[menu-1];
}