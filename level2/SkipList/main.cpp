#include <iostream>

using namespace std;

struct NODE {
    int Data;
    NODE * Next;
    NODE * Down;
    NODE() {
        this -> Data = 0;
        this -> Next = nullptr;
        this -> Down = nullptr;
    }
    NODE(int Data, NODE * Next, NODE * Down) {
        this -> Data = Data;
        this -> Next = Next;
        this -> Down = Down;
    }
};

class SKIPLIST {
    public:
        int LISTLENGTH = 0;

    private:
        NODE * HEAD;
        int MaxLevel = 16;

    public:
        SKIPLIST() {
            HEAD = (NODE *)malloc(sizeof(NODE));
        }

        void insert() {

        }



};

int main() {

    return 0;
}