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

  p.getSessionKey(argv);

// start of des

  vector<string> ptblocks = d.inputFileReader("plaintext.txt");

  bitset<64> ptblocksbin[ptblocks.size()];

  for (int i = 0; i < ptblocks.size(); i++) 
    ptblocksbin[i] = (d.stringToBinary(ptblocks[i]));

  vector<string> keyBlocks = d.inputFileReader("sessionkey.txt");

  bitset<64> keyBin = d.hexStringToBinary64(keyBlocks[0]);

  bitset<64> ivBin = d.hexStringToBinary64("0000000000000000");

  char encryptedfileName[1000] = "encrypted_message.enc";

  char decrypedfileName[1000] = "decrypted_message.txt";

  std::vector< bitset<48> > keySchedule = d.keyScheduleGenerator(ivBin);

  d.des(encryptedfileName, ptblocksbin, 1, ivBin, ptblocks.size(), keySchedule);

  d.des(decrypedfileName, ptblocksbin, 2, ivBin, ptblocks.size(), keySchedule);
  

  
//end of des
  
  
}
