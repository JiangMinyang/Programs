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
    int l2 = s2.length();
    while (j < l2) {
        if (k == -1 || s2[j] == s2[k]) {
            k++; j++;
            fail[j] = k;
        }
        else k = fail[k];
    }

    int i = 0;
    j = 0;
    int l1 = s1.length();
    while (i < l1) {
        if (j == -1 || s1[i] == s2[j]) {
            i++;    j++;
        }
        else j = fail[j];
        if (j == l2) cout << i - s2.length() << " ";
    }
    cout << endl;
}

int main() {
    cin >> s1 >> s2;
    KMP(s1, s2);
    return 0;
}
