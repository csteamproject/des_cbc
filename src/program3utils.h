#ifndef PROGRAM3UTILS_H
#define PROGRAM3UTILS_H

#include <openssl/evp.h>
#include <openssl/conf.h>
#include <openssl/err.h>
#include <string>

using namespace std;

class program3utils {
private:
public:
  FILE* getFile(unsigned char* fileName);
  long GetFileSize(string filename);
};

#endif
