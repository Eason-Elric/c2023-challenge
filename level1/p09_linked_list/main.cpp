#include <iostream>
#include <vector>
using namespace std;

struct ListPoint{
    int Data;
    ListPoint * Next;
};

void CreateList(ListPoint * Point);
void ShowList(ListPoint * Point);
int ListLength(ListPoint * Point);
void ClearList(ListPoint * Point);
void ReverseList(ListPoint * Point);
vector<int> FindList(ListPoint * Point, int FindNum);

int main() {
    //ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ListPoint * Head = (ListPoint * ) malloc(sizeof(ListPoint));
    Head -> Next = NULL;
    cout << "Please input a list: ";
    CreateList(Head);

    cout << "\n\nTraverse the list: ";
    ShowList(Head);

    cout << "\n\nReverse the list: ";
    ReverseList(Head);
    ShowList(Head);

    cout << "\n\nPlease input a number: ";
    int Num = 0;
    cin >> Num;
    vector<int> Order = FindList(Head, Num);
    cout << "\n\nQuery results: ";
    for(vector<int>::iterator point = Order.begin(); point != Order.end(); point++)
        cout << *point << " ";
    cout << endl;
    ClearList(Head);
    free(Head);
    system("pause");
    return 0;
}

void CreateList(ListPoint * Point){
    int num = 0;
    cin >> num;
    while(num != -1){
        ListPoint * point = (ListPoint * ) malloc(sizeof(ListPoint)); // 每次输入增加一个空间
        point -> Data = num;
        point -> Next = NULL;
        Point -> Next = point;
        Point = Point -> Next;
        cin >> num;
    }
}

void ShowList(ListPoint * Point){
    if(ListLength(Point) == 0){
        cout << "Nothing";
        return;
    }
    while(Point -> Next != NULL){
        Point = Point -> Next;
        cout << Point -> Data << " ";
    }
    cout << endl;
}

int ListLength(ListPoint * Point){
    int Length = 0;
    while(Point -> Next != NULL){
        Length++;
        Point = Point -> Next;
    }
    return Length;
}

void ClearList(ListPoint * Point){
    while(Point -> Next != NULL){
        ListPoint * point = Point -> Next;
        Point -> Next = Point -> Next -> Next;
        free(point);
    }
}

void ReverseList(ListPoint * Point){
    ListPoint * point_ = Point -> Next, * point__ = NULL;
    while(point_ -> Next != NULL) {
        ListPoint * point = (ListPoint *) malloc(sizeof(ListPoint));
        point -> Data = point_ -> Next -> Data;
        point -> Next = Point -> Next;
        Point -> Next = point;
        point__ = point_ -> Next;
        point_ -> Next = point_ -> Next -> Next;
        free(point__);
    }
}

vector<int> FindList(ListPoint * Point, int FindNum){
    vector<int> Order;
    int OrderNum = 0;
    while(Point -> Next != NULL){
        Point = Point -> Next;
        OrderNum++;
        if(Point -> Data == FindNum)
            Order.push_back(OrderNum);
    }
    if(Order.size() == 0)
        Order.push_back(-1);
    return Order;
}