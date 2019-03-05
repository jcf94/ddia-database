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
    load_dbdata_from_disk();
}

SSTable_DB::~SSTable_DB()
{
    save_dbdata_to_disk();
}

int SSTable_DB::insert(std::string key, std::string value)
{
    auto result = _table.find(key);
    if (result == _table.end())
    {
        auto lower = _table.upper_bound(key);
        lower--;
        _table.insert(DATA_PAIR(key, value, lower->second.file_no, lower->second.offset));
        log_info("New Item Insert");
        return 0;
    } else
    {
        result->second.value = value;
        log_info(make_string("Value for %s changed", key.c_str()));
        return -1;
    }
}

int SSTable_DB::query(std::string key)
{
    auto result = _table.find(key);
    if (result == _table.end())
    {
        auto upper = _table.upper_bound(key);
        auto lower = upper;
        lower--;
        
        if (query_in_file(key,
            lower->second.file_no, lower->second.offset,
            upper->second.file_no, upper->second.offset))
        {
            log_error("Key not found");
            return -1;
        } else
        {
            return 0;
        }
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

void SSTable_DB::load_dbdata_from_disk()
{
    char name[20];
    int index = 0;
    sprintf(name, "db_data/datafile_%03d", index);
    
    int total_record = 0;
    while (FILE* file = fopen(name, "r"))
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
        FILE* file = fopen(i.c_str(), "r");
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
        count++;
    }

    log_ok("Disk Files Load Success");
    log_ok(make_string("Total %d Files with %d Records", _db_file_list.size(), total_record));
    log_ok(make_string("SSTable DataBase now have %d Records", _table.size()));
}

std::queue<temp_node>* SSTable_DB::load_dbdata_from_file(std::string file_name, std::queue<temp_node>* temp_data)
{
    if (!temp_data) temp_data = new std::queue<temp_node>;
    FILE* file = fopen(file_name.c_str(), "r");
    int num_record;
    fscanf(file, "%d", &num_record);
    char s1[10], s2[200];
    for (int now=0;now<num_record;now++)
    {
        int current_offset = ftell(file);
        fscanf(file, "%s", s1);
        fscanf(file, "%s", s2);
        temp_data->push(temp_node{s1, s2});
    }
    fclose(file);
    return temp_data;
}

void SSTable_DB::save_dbdata_to_disk()
{
    auto i = _table.begin();
    auto fi = _db_file_list.begin();
    int target_file_index = 0;
    char target_file_name[20];

    sprintf(target_file_name, "db_data/datafile_%03d", target_file_index);
    auto temp_data = load_dbdata_from_file(fi->c_str());
    fi ++;

    while (i!=_table.end() || fi!=_db_file_list.end())
    {
        // assert target_file_name < fi
        if (fi!=_db_file_list.end() && fi->compare(target_file_name) <= 0)
        {
            temp_data = load_dbdata_from_file(fi->c_str(), temp_data);
            fi++;
        }

        FILE* file = fopen(target_file_name, "w");
        fprintf(file, "%d\n", FILE_LENGTH);

        int count = 0;
        while (count < FILE_LENGTH)
        {
            if (!temp_data->empty() && i!=_table.end())
            {
                int cmp = temp_data->front().key.compare(i->first);
                if (cmp < 0)
                {
                    fprintf(file, "%s\n%s\n",
                        temp_data->front().key.c_str(),
                        temp_data->front().value.c_str());
                    temp_data->pop();
                    if (temp_data->empty() && fi!=_db_file_list.end())
                    {
                        temp_data = load_dbdata_from_file(fi->c_str(), temp_data);
                        fi++;
                    }
                } else
                {
                    fprintf(file, "%s\n%s\n",
                        i->first.c_str(),
                        i->second.value.c_str());
                    i++;
                    if (cmp == 0)
                    {
                        temp_data->pop();
                        if (temp_data->empty() && fi!=_db_file_list.end())
                        {
                            temp_data = load_dbdata_from_file(fi->c_str(), temp_data);
                            fi++;
                        }
                    }
                }
            } else if (!temp_data->empty())
            {
                fprintf(file, "%s\n%s\n",
                    temp_data->front().key.c_str(),
                    temp_data->front().value.c_str());
                temp_data->pop();
                if (temp_data->empty() && fi!=_db_file_list.end())
                {
                    temp_data = load_dbdata_from_file(fi->c_str(), temp_data);
                    fi++;
                }
            } else if (i!=_table.end())
            {
                fprintf(file, "%s\n%s\n",
                    i->first.c_str(),
                    i->second.value.c_str());
                i ++;
            } else break;
            count ++;
        }
        if (count < FILE_LENGTH)
        {
            fseek(file, 0, SEEK_SET);
            fprintf(file, "%5d", count);
        }
        fclose(file);

        target_file_index ++;
        sprintf(target_file_name, "db_data/datafile_%03d", target_file_index);
    }

    log_ok("SSTable DataBase Save to Disk Files Success");
    log_ok(make_string("Total %d Files Saved", target_file_index));
}

int SSTable_DB::query_in_file(std::string key, int l_file_no, int l_offset, int u_file_no, int u_offset)
{
    char s1[10], s2[200];
    if (l_file_no == u_file_no)
    {
        FILE *file = fopen(_db_file_list[l_file_no].c_str(), "r");
        fseek(file, l_offset, SEEK_SET);
        while (ftell(file) < u_offset)
        {
            fscanf(file, "%s", s1);
            fscanf(file, "%s", s2);
            if (key.compare(s1) == 0)
            {
                std::cout << s2 << std::endl;
                fclose(file);
                return 0;
            }
        }
        fclose(file);
    } else
    {
        FILE *file = fopen(_db_file_list[l_file_no].c_str(), "r");
        fseek(file, l_offset, SEEK_SET);
        while (fscanf(file, "%s", s1) != EOF)
        {
            fscanf(file, "%s", s1);
            fscanf(file, "%s", s2);
            if (key.compare(s1) == 0)
            {
                std::cout << s2 << std::endl;
                fclose(file);
                return 0;
            }
        }
        fclose(file);
        file = fopen(_db_file_list[u_file_no].c_str(), "r");
        while (ftell(file) < u_offset)
        {
            fscanf(file, "%s", s1);
            fscanf(file, "%s", s2);
            if (key.compare(s1) == 0)
            {
                std::cout << s2 << std::endl;
                fclose(file);
                return 0;
            }
        }
        fclose(file);
    }
    return -1;
}