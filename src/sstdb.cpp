/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : SSTable_DataBase
************************************************ */

#include "sstdb.h"

SSTable_DB::SSTable_DB()
{
    _table.clear();
}

SSTable_DB::~SSTable_DB()
{

}

void SSTable_DB::insert(std::string key, std::string value)
{
    _table.insert(std::pair<std::string, std::string>(key, value));
}

std::string SSTable_DB::get(std::string key)
{
    auto result = _table.find(key);
    return result->second;
}