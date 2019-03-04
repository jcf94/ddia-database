/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : SSTable_DataBase_H
************************************************ */

#ifndef SSTABLE_DATABASE_H
#define SSTABLE_DATABASE_H

#include <string>
#include <map>
#include <queue>

#define DATA_PAIR(x, y) std::pair<std::string, std::string>(x, y)

class SSTable_DB
{
public:
    SSTable_DB();
    ~SSTable_DB();

    int insert(std::string key, std::string value);
    int query(std::string key);
    int drop(std::string key);

    void load();
    void save();

private:

    std::map<std::string, std::string> _table;
    std::queue<std::string> _db_file_list;
};

#endif // !SSTABLE_DATABASE_H
