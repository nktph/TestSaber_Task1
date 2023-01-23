// TestSaber Task 1
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>

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

    ListRand()
    {
        Head = Tail = NULL;
        Count = 0;
    }

    void AddToHead(string data)
    {
        ListNode* temp = new ListNode;
        temp->Next = Head;
        temp->Data = data;
        temp->Prev = NULL;
        if (Head != 0)
        {
            Head->Prev = temp;
        }
        if (Count == 0)
            Head = Tail = temp;
        else
            Head = temp;

        Count++;
    }

    void AddToTail(string data)
    {
        ListNode* temp = new ListNode;
        temp->Next = NULL;
        temp->Data = data;
        temp->Prev = Tail;
        if (Tail != 0)
        {
            Tail->Next = temp;
        }
        if (Count == 0)
            Head = Tail = temp;
        else
            Tail = temp;
        
        Count++;
    }

    void AddToTail(ListNode* node)
    {
        node->Next = NULL;
        node->Prev = Tail;
     
        if (Tail != 0)
        {
            Tail->Next = node;
        }
        if (Count == 0)
            Head = Tail = node;
        else
            Tail = node;
        Count++;
    }

    void Show()
    {
        ListNode* temp = Head;
        while (temp != NULL)
        {
            if (temp->Rand != 0)
            {
                cout << temp << "\t" << temp->Data << "\t" << temp->Rand << endl;

            }
            else
            {
                cout << temp << "\t" << temp->Data << endl;

            }
            temp = temp->Next;
        }
    }

    void Serialize(ofstream& s)
    {
        s.open("file.bin", ios::binary);
        if (s.is_open())
        {
            ListNode* temp = Head;

            while (temp != NULL)
            {
                s.write(reinterpret_cast<char*>(temp), sizeof(ListNode));
                temp = temp->Next;
            }
            s.close();
        }
        else
        {
            cout << "file not opened" << endl;
        }
    }

    void Deserialize(ifstream& s)
    {
        map<ListNode*, ListNode*> mapping;

        s.open("file.bin", ios::binary);
        if (s.is_open())
        {
            while (!s.eof())
            {
                ListNode* newer = new ListNode;
                s.read(reinterpret_cast<char*>(newer), sizeof(ListNode));
                if (newer->Next != NULL)
                {
                    mapping[(newer->Next)->Prev] = newer;
                    this->AddToTail(newer);
                }
                else
                {
                    mapping[(newer->Prev)->Next] = newer;
                    this->AddToTail(newer);
                    break;
                }
            }
            s.close();
        }
        else
        {
            cout << "file not opened" << endl;
        }

        ListNode* tmp = Head;
        while (tmp != NULL)
        {
            tmp->Rand = mapping[tmp->Rand];
            tmp = tmp->Next;
        }

    }
};


int main()
{
                                //Поля данных
    string data1 = "first node";
    string data2 = "second node";
    string data3 = "third node";
    string data4 = "fourth node";
    string data5 = "fifth node";
    
    ListRand List;              //создание и инициализация списка
    List.AddToHead(data1);
    List.AddToTail(data2);
    List.AddToTail(data3);
    List.AddToTail(data4);
    List.AddToTail(data5);

    ListNode* tmp = new ListNode; //расстановка случайных связей
    tmp = List.Head;
    tmp = tmp->Next;
    tmp->Rand = tmp;
    tmp->Next->Rand = List.Tail;
    tmp->Next->Next->Rand = List.Head;


    List.Show();                //Вывод изначального списка

    ofstream ofs;
    List.Serialize(ofs);        //Сериализация изначального списка


    ListRand list2;             //Объявление нового списка
    ifstream ifs;
    list2.Deserialize(ifs);     //Десериализация и заполнение списка из файла

    cout << "----------------------------------------" << endl;
    list2.Show();               //Вывод полученного из файла списка
    
    return 0;
}
