#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#include <stack>
#include <string>
#include <queue>
#include <iostream>


using namespace std;

struct Node{
    int EndSign;
    char Value;
    Node *fail;
    map<char, Node*> Child;
    Node(char c) {
        EndSign = 0;
        Value = c;
        fail = NULL;
        Child.clear();
    }
    Node() {
        EndSign = 0;
        Value = 0;
        fail = NULL;
        Child.clear();
    }
};

class AC_Machine {
public:
    Node *root;
    AC_Machine() {
        root = new Node();
    }
    void insert(char *s) {
        int L = strlen(s);
        Node *now = root;
        Node *Temp;
        for(int i = 0; i < L; i++) {
            if (now->Child.find(s[i]) != now->Child.end()) {
                now = now->Child[s[i]];
                continue;
            }
            Temp = new Node(s[i]);
//            now->Child.insert(pair<char, Node*>(s[i], Temp));
            now->Child[s[i]] = Temp;
            now = now->Child[s[i]];
        }
        now->EndSign += 1;
    }

    void buildFailPointer() {
        Node *now = root;
        Node *p;
        queue<Node*> Q;
        map<char, Node*>::iterator I;
        for(I = root->Child.begin(); I != root->Child.end(); I++) {
            Q.push(I->second);
            I->second->fail = root;
        }
        while (!Q.empty()) {
            now = Q.front();
            Q.pop();
            for(I = now->Child.begin(); I != now->Child.end(); I++) {
                p = now;
                while (p->fail != NULL) {
                    if (p->fail->Child.find(I->second->Value) != p->fail->Child.end()) {
                        I->second->fail = p->fail->Child[I->second->Value];
                        break;
                    }
                    p = p->fail;
                }
                if (p->fail == NULL)
                    I->second->fail = root;
                Q.push(I->second);
            }
        }
    }

    void find(char *s) {
        int L = strlen(s);
        Node *now = root;
        int ans = 0;
        int i = 0;
        while (i < L) {
            if (now->Child.find(s[i]) != now->Child.end()) {
                now = now->Child[s[i]];
                Node *temp = now;
                if (now != NULL && now->EndSign > 0) {
                    ans += now->EndSign;
                    now->EndSign = 0;
                }
                while (temp->fail != NULL && temp->fail->EndSign > 0) {
                    ans += temp->fail->EndSign;
                    temp->fail->EndSign = 0;
                    temp = temp->fail;
                }
                i++;
            }
            else {
                now = now->fail;
                if (now == NULL) {
                    now = root;
                    i++;
                }
            }
        }
        cout << ans << endl;
    }

    void print(Node *now) {
        cout << now->Value << " " << now->fail << " ";
        if (now->fail == NULL || now->fail == root) cout << "zzz" << endl;
        else cout << now->fail->Value << endl;
        map<char, Node*>::iterator I;
        for(I = now->Child.begin(); I != now->Child.end(); I++)
            print(I->second);
    }
};
char s1[1000001];

int main() {
    int n;
    int k;
    char s[51];
    cin >> k;
    for(int j = 0; j < k; j++) {
        AC_Machine A;
        cin >> n;
        for(int i = 0; i < n; i++) {
            scanf("%s", s);
            A.insert(s);
        }
        A.buildFailPointer();
        scanf("%s", s1);
        A.find(s1);
    }
    return 0;
}
