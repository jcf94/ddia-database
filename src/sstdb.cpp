/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : SSTable_DataBase
************************************************ */

#include "sstdb.h"
#include "sstdb_util.h"

#include <fstream>

SSTable_DB::SSTable_DB()
{
    _table.clear();
}

SSTable_DB::~SSTable_DB()
{

}

int SSTable_DB::insert(std::string key, std::string value)
{
    auto result = _table.find(key);
    if (result == _table.end())
    {
        _table.insert(DATA_PAIR(key, value));
        log_info("New Item Insert");
        return 0;
    } else
    {
        result->second = value;
        log_info(make_string("Value for %s changed", key.c_str()));
        return -1;
    }
}

int SSTable_DB::query(std::string key)
{
    auto result = _table.find(key);
    if (result == _table.end())
    {
        log_error("Key not found");
        return -1;
    } else
    {
        std::cout << result->second << std::endl;
        return 0;
    }
}

int SSTable_DB::drop(std::string key)
{
    auto result = _table.find(key);
    if (result == _table.end())
    {
        log_error("Key not found");
        return -1;
    } else
    {
        _table.erase(result);
        log_info(make_string("Item for %s delete", key.c_str()));
        return 0;
    }
}

void SSTable_DB::load()
{
    
}

void SSTable_DB::save()
{
    FILE *file = fopen("db_data/datafile", "w");
    for (auto i:_table)
    {
        fprintf(file, "%s\n%s\n", i.first.c_str(), i.second.c_str());
    }
    fclose(file);
}