/* ***********************************************
MYID	: Chen Fan
LANG	: G++
PROG	: RDMA_UTIL_CPP
************************************************ */

#include "sstdb_util.h"

#include <stdexcept>

std::string make_string(const char *fmt, ...)
{
    #ifndef _WIN32

    char * sz;
    va_list ap;
    va_start(ap, fmt);
    if (vasprintf(&sz, fmt, ap) == -1)
        throw std::runtime_error("memory allocation failed\n");
    va_end(ap);
    std::string str(sz);
    free(sz);
    return str;

    #else

    char sz[100];
    va_list ap;
    va_start(ap, fmt);
    if (vsprintf(sz, fmt, ap) == -1)
        throw std::runtime_error("memory allocation failed\n");
    va_end(ap);
    std::string str(sz);
    return str;

    #endif // !_WIN32
}
