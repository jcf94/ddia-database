/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : SSTable_DataBase
************************************************ */

#include "sstdb.h"

#include "sstdb_util.h"

SSTable_DB::SSTable_DB()
{
    _table.clear();
}

SSTable_DB::~SSTable_DB()
{

}

void SSTable_DB::insert(std::string key, std::string value)
{
    auto result = _table.find(key);
    if (result == _table.end())
    {
        _table.insert(DATA_PAIR(key, value));
        log_info("New Item Insert");
    } else
    {
        result->second = value;
        log_info(make_string("Value for %s changed", key.c_str()));
    }
}

void SSTable_DB::get(std::string key)
{
    auto result = _table.find(key);
    if (result == _table.end())
    {
        log_error("Key not found");
    } else
    {
        std::cout << result->second << std::endl;
    }
}