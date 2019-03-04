/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : SSTable_DataBase_H
************************************************ */

#ifndef SSTABLE_DATABASE_H
#define SSTABLE_DATABASE_H

#include <string>
#include <map>
#include <vector>

#define FILE_LENGTH 40000
#define DEFAULT_TABLE_LENGTH 60000

struct table_node
{
    std::string value;
    int file_no, offset;
};

#define DATA_PAIR(a, b, c, d) std::pair<std::string, table_node>(a, table_node{b, c, d})

class SSTable_DB
{
public:
    SSTable_DB();
    ~SSTable_DB();

    int insert(std::string key, std::string value);
    int query(std::string key);
    int drop(std::string key);

    void save();

private:
    void load();

    std::map<std::string, table_node> _table;
    std::vector<std::string> _db_file_list;
};

#endif // !SSTABLE_DATABASE_H
