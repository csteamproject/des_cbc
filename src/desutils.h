#ifndef DESUTILS_H
#define DESUTILS_H

#include <iostream>
#include <sstream>
#include <bitset>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;

class desutils {
private:
public:
  void des(char outputFileName[1000], bitset<64> inputFileBlocksBinary[], int mode, bitset<64> ciMinusOne, int blockNumber, vector<bitset<48> > keySchedule);
  string keyGenerator(const int len);
  bitset<64> stringToBinary(string a);
  int calcSBoxIndex(bitset<48> b, int s);
  bitset<32> fillBitSet(bitset<32> initial, bitset<4> added, int s);
  bitset<64> combineBitSet(bitset<32> a, bitset<32> b);
  string pad(string a, int blockLength);
  char next8BitsToChar(bitset<64> a, int s, int ofs);
  string getHexStringInput(string keyOrIV);
  int getMode();
  bitset<64> hexStringToBinary64(string hString);
  bitset<32> sBoxOutputFunc(bitset<48> erO);
  std::vector<bitset<48> > keyScheduleGenerator(bitset<64> keyBin);
  vector<string> inputFileReader(char inputFile[1000]);
};

#endif
