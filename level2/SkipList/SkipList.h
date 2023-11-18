#ifndef C2023_CHALLENGE_SKIPLIST_H
#define C2023_CHALLENGE_SKIPLIST_H

#include <random>

class SkipList {
    private:
        struct Node {
            explicit Node(int val = INT_MIN) :Value(val), Up(nullptr), Down(nullptr), Left(nullptr), Right(nullptr) {}
            int Value;
            struct Node* Up;
            struct Node* Down;
            struct Node* Left; 
            struct Node* Right;
        };
    private:
        Node* Head; // 头节点，查询起始点
        int Level;
        static bool RandomVal();
    public:
        SkipList(): Level(1) {
            Head = new Node();
        }
        
        void insert(int val);
        
        bool search(int val);
        
        void remove(int val);
};

#endif //C2023_CHALLENGE_SKIPLIST_H
