#ifndef PROGRAM3UTILS_H
#define PROGRAM3UTILS_H

#include <openssl/evp.h>
//#include <opennssl/conf.h>
#include <openssl/err.h>

using namespace std;

class program3utils {
private:
public:
  FILE* getFile(unsigned char* fileName);
};

#endif
