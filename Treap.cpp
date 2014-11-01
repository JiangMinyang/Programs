#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;

class Node{
public:
    int num, weight;
    Node *Left, *Right, *Father;
    Node(int n, int k) {
        num = n; weight = k;
        Left = Right = Father = NULL;
    }
    
    Node(int n, int k, Node F) {
        num = n; weight = k;
        Left = Right = NULL;
        *Father = F;
    }
    
    Node(const Node& a) {
        num = a.num; weight = a.weight; Left = a.Left;
        Right = a.Right; Father = a.Father;
    }
    
    int compareNum(Node b) {
        if (num > b.num) return 1;
        if (num == b.num) return 0;
        return -1;
    }
    
    int compareWeight(Node b) {
        if (weight > b.weight) return 1;
        if (weight == b.weight) return 0;
        return -1;
    }
};

class Tree {
private:
    Node *Head;
    int size;
public:
    Tree() {
        Head = NULL;
        size = 0;
    }
    
    void printDLR(Node *now) {
        if (now == NULL) return;
        cout << now->num << " ";
        printDLR(now->Left);
        printDLR(now->Right);
    }
    
    void printLDR(Node *now) {
        if (now == NULL) return;
        printLDR(now->Left);
        cout << now->num << " ";
        printLDR(now->Right);
    }
private:
    void rotateLeft(Node *a) {
        if (a->Right == NULL) return;
        Node* temp;
        if (a->Father == NULL) {
            Head = a->Right;
        }
        else {
            if (a->Father->Left == a) a->Father->Left = a->Right;
            else	a->Father->Right = a->Right;
        }
        a->Right->Father = a->Father;
        a->Father = a->Right;
        temp = a->Right;
        a->Right = a->Right->Left;
        if (temp->Left != NULL) temp->Left->Father = a;
        temp->Left = a;
    }
    
    void rotateRight(Node *a) {
        if (a->Left == NULL) return;
        Node* temp;
        if (a->Father == NULL) {
            Head = a->Left;
        }
        else {
            if (a->Father->Left == a) a->Father->Left = a->Left;
            else	a->Father->Right = a->Left;
        }
        a->Left->Father = a->Father;
        a->Father = a->Left;
        temp = a->Left;
        a->Left = a->Left->Right;
        if (temp->Right != NULL) temp->Right->Father = a;
        temp->Right = a;
    }
    
    void insert(Node *a, Node *now) {
        if (now->num > a->num) {
            if (now->Left == NULL) {
                now->Left = a;
                a->Father = now;
            }
            else insert(a, now->Left);
            if (now->weight > now->Left->weight)
                rotateRight(now);
        }
        else {
            if (now->Right == NULL) {
                now->Right = a;
                a->Father = now;
            }
            else insert(a, now->Right);
            if (now->weight > now->Right->weight)
                rotateLeft(now);
        }
    }
    
    
    void push(Node *a) {
        size++;
        Node *now = a;
        if (Head == NULL) {
            Head = now;
            return;
        }
        insert(a, Head);
    }
    
    Node* getDirection(Node *a, Node *b) {
        if (a == NULL) return b;
        if (b == NULL) return a;
        return (a->weight < b->weight ? a : b);
    }
    
    Node* find(int key, Node *now) {
        if (now == NULL) return NULL;
        if (now->num == key) return now;
        if (key < now->num) return find(key, now->Left);
        else return find(key, now->Right);
    }
    
    void pop(Node *now) {
        while (true) {
            if (now->Left == NULL && now->Right == NULL) {
                if (now->Father == NULL) Head = NULL;
                else
                    if (now->Father->Left == now) now->Father->Left = NULL;
                    else now->Father->Right = NULL;
                break;
            }
        if (getDirection(now->Left, now->Right) == now->Left) rotateRight(now);
        else rotateLeft(now);
        }
    }
    
public:
    void Push(int key, int weight) {
        push(new Node(key, weight));
    }
    int getSize() {
        return size;
    }
    
    void Delete(int key) {
        Node *now = find(key, Head);
        pop(now);
    }
    
    void print(Node *now) {
        if (now == NULL) return;
        cout << now->num << " " << (now->Left == NULL?0:now->Left->num) << " " << (now->Right == NULL?0:now->Right->num) << endl;
        print(now->Left);
        print(now->Right);
    }

    void test() {
        print(Head);
    }
};


int main() {
    Tree tree;
    int n,x;
    cin >> n;
    srand((unsigned int)time(0));
    for(int i = 0; i < n; i++) {
        cin >> x;
        tree.Push(x, rand());
    }
    tree.test();
    cout << endl;
    tree.test();
    return 0;
}