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

    // sstb.insert("aa", "bbbb");
    // sstb.insert("bb", "sdfsdfsd");
    // sstb.insert("cc", "ggggggg");

    // sstb.query("bb");
    // sstb.query("aa");
    // sstb.query("cc");

    // sstb.insert("bb", "ccccccccc");
    // sstb.query("bb");
    // sstb.query("dd");

    // sstb.drop("cc");
    // sstb.query("cc");
    // sstb.drop("dd");

    // sstb.save();

    // sstb.query("UuJVm");
    // sstb.query("kWtRu");
    // sstb.query("kWuWK");
    char s1[10], s2[200], cmd;
    while (1)
    {
        scanf("%c", &cmd);
        getchar();
        switch (cmd)
        {
            case 'q':
                scanf("%s", &s1);
                sstb.query(s1);
                break;
            case 'i':
                scanf("%s", &s1);
                scanf("%s", &s2);
                sstb.insert(s1, s2);
                break;
            case 'c':
                return 0;
            default:
                printf("Usage:\n");
                printf("\tq xxx: query\n");
                printf("\ti xxx yyy: insert\n");
                printf("\tc: close");
                break;
        }
        getchar();
    }

    return 0;
}