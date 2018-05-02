#include "desutils.h"
#include "program3utils.h"

using namespace std;

int main(int argc, char* argv[]){

  desutils d;
  program3utils p;

  if (argc != 5) {
    cerr << "Incorrect argument parameters!" << endl;
    return 1;
  }

  cout << "Hello, welcome to the program!" << endl;
  cout << "Entered file names:" << endl;
  for (int i = 1; i < 5; i++) {
    cout << argv[i] << ": ";
    if (!d.inputFileValidation(argv[i])) {
      cout << "Not a valid file!" << endl;
      return 0;
    }
    cout << "File found" << endl;
  }
  
  char decryptedfileName[1000] = "decrypted_message.txt";
  char ivfileName[1000] = "ivFile.txt";
  
  vector<string> ctblocks = d.inputFileReader(argv[3], 2);  
  vector<string> keyBlocks = d.inputFileReader(argv[2], 1);
  
  string iv = p.inputFileReadIV(ivfileName);
  
  cout << "IV : " << iv << endl;
  bitset<64> ctblocksbin[ctblocks.size()];
  bitset<64> keyBin = d.stringToBinary(keyBlocks[0]);
  bitset<64> ivBin = d.hexStringToBinary64(iv);
  
  std::vector< bitset<48> > keySchedule = d.keyScheduleGenerator(keyBin);

  //ctblocksbin[ptblocks.size()];
  for (int i = 0; i < ctblocks.size(); i++) 
    ctblocksbin[i] = (d.stringToBinary(ctblocks[i]));
  
  d.des(decryptedfileName, ctblocksbin, 2, ivBin, ctblocks.size(), keySchedule, 1);  
  
  p.verifySignature(argv);
  
}
