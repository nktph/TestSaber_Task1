// TestSaber Task 1
//

#include <iostream>
#include <fstream>

using namespace std;

class ListNode {
public:
    ListNode* Prev;
    ListNode* Next;
    ListNode* Rand; // произвольный элемент внутри списка
    string Data;
};


class ListRand {
public:
    ListNode* Head;
    ListNode* Tail;
    int Count;

    void Serialize(ofstream s)
    {
    }

    void Deserialize(ifstream s)
    {
    }
};


int main()
{
    
}
