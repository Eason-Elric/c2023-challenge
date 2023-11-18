#include "SkipList.h"

std::random_device RandomDevice;

bool SkipList::RandomVal() {
    int Ret = RandomDevice() % 2;
    return Ret == 0;
}

void SkipList::insert(int Val) {
    Node* Cursor = Head;
    Node* NewNode = nullptr;

    while (Cursor -> Down != nullptr)
        Cursor = Cursor -> Down;

    Node* CurrentHead = Cursor;
    while (Cursor -> Right != nullptr) {
        if (Val < Cursor -> Right -> Value && NewNode == nullptr) {
            NewNode = new Node(Val);
            NewNode -> Right = Cursor -> Right;
            Cursor -> Right = NewNode;
        }
        Cursor = Cursor -> Right;
    }
    
    if (NewNode == nullptr) {
        NewNode = new Node(Val);
        Cursor -> Right = NewNode;
    }
    
    int CurrentLevel = 1;
    while (RandomVal()) {
        CurrentLevel++;
        if (Level < CurrentLevel) {
            Level++;
            Node* NewHead = new Node();
            NewHead -> Down = Head;
            Head -> Up = NewHead;
            Head = NewHead;
        }
        CurrentHead = CurrentHead -> Up;
        Cursor = CurrentHead;
        Node* SkipNode = nullptr;
        while (Cursor -> Right != nullptr) {
            if (Val < Cursor -> Right -> Value && SkipNode == nullptr) {
                SkipNode = new Node(Val);
                SkipNode -> Right = Cursor -> Right;
            }
            Cursor = Cursor -> Right;
        }
        if (SkipNode == nullptr) {
            SkipNode = new Node(Val);
            Cursor -> Right = SkipNode;
        }
        while (NewNode -> Up != nullptr)
            NewNode = NewNode -> Up;
        SkipNode -> Down = NewNode;
        NewNode -> Up = SkipNode;
    }
}

bool SkipList::search(int Val) {
    Node* Cursor = nullptr;

    if (Head == nullptr)
        return false;
    
    Cursor = Head;
    while (Cursor -> Down != nullptr) {
        while (Cursor -> Right != nullptr) {
            if (Val <= Cursor -> Right -> Value)
                break;
            Cursor = Cursor -> Right;
        }
        Cursor = Cursor -> Down;
    }
    while (Cursor -> Right != nullptr) {
        if (Val > Cursor -> Right -> Value)
            Cursor = Cursor -> Right;
        else if (Val == Cursor -> Right -> Value)
            return true;
        else if (Val < Cursor -> Right -> Value)
            return false;
    }
    return false;
}

void SkipList::remove(int Val) {
    Node* Cursor = Head;
    Node* PreHead = nullptr;
    while (true) {
        Node* CurrentHead = Cursor;
        if (PreHead != nullptr) {
            CurrentHead -> Up = nullptr;
            PreHead -> Down = nullptr;
            delete PreHead;
            PreHead = nullptr;
            Level--;
            Head = CurrentHead;
        }
        while (Cursor != nullptr && Cursor -> Right != nullptr) {
            if (Val == Cursor -> Right -> Value) {
                Node* delptr = Cursor -> Right;
                Cursor -> Right = Cursor -> Right -> Right;
                delete delptr;
            }
            Cursor = Cursor -> Right;
        }
        if (CurrentHead -> Right == nullptr)
            PreHead = CurrentHead;
        if (CurrentHead -> Down == nullptr)
            break;
        else
            Cursor = CurrentHead -> Down;
    }
}