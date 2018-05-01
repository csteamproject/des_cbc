#ifndef PROGRAM3UTILS_H
#define PROGRAM3UTILS_H

#include <openssl/evp.h>
#include <openssl/crypto.h>
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/engine.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <string>
#include <sys/stat.h>
#include <iostream>

using namespace std;

class program3utils {
private:
public:
  void writeFile(unsigned char* out, char* fileName);
  void getSessionKey(char* files[]);
  void signEncryptedMessage(char* privkeyName);
  void verifySignature(char* files[]);
  string inputFileReadIV(char inputFile[1000]);
};

#endif
