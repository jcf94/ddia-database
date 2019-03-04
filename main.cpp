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

    sstb->get("bb");
    sstb->get("aa");

    sstb->insert("bb", "ccccccccc");
    sstb->get("bb");
    sstb->get("dd");

    return 0;
}