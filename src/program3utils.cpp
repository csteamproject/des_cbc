#include "program3utils.h"

using namespace std;

FILE* desutils::getFile(unsigned char* fileName) {
  return fopen(fileName, "r");
}
