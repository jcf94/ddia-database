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
    SSTable_DB sstb;

    sstb.insert("aa", "bbbb");
    sstb.insert("bb", "sdfsdfsd");
    sstb.insert("cc", "ggggggg");

    sstb.query("bb");
    sstb.query("aa");
    sstb.query("cc");

    sstb.insert("bb", "ccccccccc");
    sstb.query("bb");
    sstb.query("dd");

    sstb.drop("cc");
    sstb.query("cc");
    sstb.drop("dd");

    sstb.save();

    return 0;
}