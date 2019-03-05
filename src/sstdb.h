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
#include <queue>

#define FILE_LENGTH 40000
#define DEFAULT_TABLE_LENGTH 60000

struct table_node
{
    std::string value;
    int file_no, offset;
};

struct temp_node
{
    std::string key, value;
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

private:

    int query_in_file(std::string key, int l_file_no, int l_offset, int u_file_no, int u_offset);

    void load_dbdata_from_disk();
    std::queue<temp_node>* load_dbdata_from_file(std::string file_name, std::queue<temp_node>* temp_data = NULL);
    void save_dbdata_to_disk();

    std::map<std::string, table_node> _table;
    std::vector<std::string> _db_file_list;
};

#endif // !SSTABLE_DATABASE_H
