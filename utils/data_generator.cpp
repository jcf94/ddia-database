/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : SSTable_DataBase_TestData_Generator
************************************************ */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;

struct node
{
    string s1, s2;
    friend bool operator < (node a, node b)
    {
        return a.s1 > b.s1;
    }
};

priority_queue<node> heap;
queue<node> q;

string random_string(int length)
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const int max_index = sizeof(charset) - 1;
        return charset[rand() % max_index];
    };
    std::string str(length,0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

int main()
{
    freopen("test_data.txt", "w", stdout);

    int total = 160000;

    for (int i=0;i<total;i++)
    {
        string s1 = random_string(5);
        string s2 = random_string(100);
        heap.push(node{s1, s2});
    }

    for (int i=0;i<total;i++)
    {
        node temp = heap.top();
        cout << temp.s1 << endl << temp.s2 << endl;
        q.push(temp);
        heap.pop();
    }

    for (int i=0;i<4;i++)
    {
        char name[20];
        sprintf(name, "datafile_00%d", i);
        freopen(name, "w", stdout);
        for (int j=0;j<40000;j++)
        {
            node temp = q.front();
            cout << temp.s1 << endl << temp.s2 << endl;
            q.pop();
        }
    }

    return 0;
}