#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;
string s1, s2;

void KMP(string s1, string s2) {
    int fail[s2.length() + 1];
    int n[s1.length() + 1];
    fail[0] = -1;
    int k = -1;
    int j = 0;
    while (j < s2.length()) {
        if (k == -1 || s2[j] == s2[k]) {
            k++; j++;
            fail[j] = k;
        }
        else k = fail[k];
    }

    int i = 0;
    j = 0;
    while (i < s1.length()) {
        if (j == -1 || s1[i] == s2[j]) {
            i++;    j++;
        }
        else j = fail[j];
        if (j == s2.length()) cout << i - s2.length() << " ";
    }
    cout << endl;
}

int main() {
    cin >> s1 >> s2;
    KMP(s1, s2);
    return 0;
}
