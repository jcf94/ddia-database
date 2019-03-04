/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : SSTable_DataBase_Main
************************************************ */

#include <iostream>
#include "src/sstdb.h"

using namespace std;

int main()
{
    auto sstb = new SSTable_DB();

    sstb->insert("aa", "bbbb");
    sstb->insert("bb", "sdfsdfsd");
    sstb->insert("cc", "ggggggg");

    cout << sstb->get("bb");

    return 0;
}