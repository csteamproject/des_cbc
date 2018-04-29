#include "program3utils.h"
#include <string>
#include <sys/stat.h>

using namespace std;

FILE* program3utils::getFile(unsigned char* fileName) {
   FILE* a;
   return a;
}

long program3utils::GetFileSize(std::string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}
