/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : SSTable_DataBase_H
************************************************ */

#ifndef SSTABLE_DATABASE_H
#define SSTABLE_DATABASE_H

#include <string>
#include <map>

#define DATA_PAIR(x, y) std::pair<std::string, std::string>(x, y)

class SSTable_DB
{
public:
    SSTable_DB();
    ~SSTable_DB();

    void insert(std::string key, std::string value);
    std::string get(std::string key);

private:

    std::map<std::string, std::string> _table;
};

#endif // !SSTABLE_DATABASE_H
