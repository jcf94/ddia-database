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
    load();
}

SSTable_DB::~SSTable_DB()
{

}

int SSTable_DB::insert(std::string key, std::string value)
// To be fixed
{
    auto result = _table.find(key);
    if (result == _table.end())
    {
        _table.insert(DATA_PAIR(key, value, 0, 0));
        log_info("New Item Insert");
        return 0;
    } else
    {
        result->second = table_node{value, 0, 0};
        log_info(make_string("Value for %s changed", key.c_str()));
        return -1;
    }
}

int SSTable_DB::query(std::string key)
// To be fixed
{
    auto result = _table.find(key);
    if (result == _table.end())
    {
        log_error("Key not found");
        return -1;
    } else
    {
        std::cout << result->second.value << std::endl;
        return 0;
    }
}

int SSTable_DB::drop(std::string key)
// To be fixed
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
    char name[20];
    int index = 0;
    sprintf(name, "db_data/datafile_%03d", index);
    
    int total_record = 0;
    while (FILE *file = fopen(name, "r"))
    {
        _db_file_list.push_back(std::string(name));
        int num_record;
        fscanf(file, "%d", &num_record);
        total_record += num_record;
        fclose(file);
        index++;
        sprintf(name, "db_data/datafile_%03d", index);
    }

    int stride = total_record / DEFAULT_TABLE_LENGTH;

    int count = 0;
    for (auto i:_db_file_list)
    {
        FILE *file = fopen(i.c_str(), "r");
        int num_record;
        fscanf(file, "%d", &num_record);
        char s1[10], s2[200];
        for (int now=0;now<num_record;now++)
        {
            int current_offset = ftell(file);
            fscanf(file, "%s", s1);
            fscanf(file, "%s", s2);
            if (now % stride == 0)
            {
                _table.insert(DATA_PAIR(s1, s2, count, current_offset));
            }
        }
    }

    log_ok("Disk Files Load Success");
    log_ok(make_string("Total %d Files with %d Records", _db_file_list.size(), total_record));
    log_ok(make_string("SSTable DataBase now have %d Records", _table.size()));
}

void SSTable_DB::save()
{
    FILE *file = fopen("db_data/datafile", "w");
    for (auto i:_table)
    {
        fprintf(file, "%s\n%s\n", i.first.c_str(), i.second.value.c_str());
    }
    fclose(file);
}