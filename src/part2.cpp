#include "desutils.h"
#include "program3utils.h"

using namespace std;

int main(int argc, char* argv[]){

  desutils d;
  program3utils p;

// input checking
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

// end of input checking

// output session key file from encrypted session key file
  p.getSessionKey(argv);

// start of des encrypt (outputs encryption to a file)
  
  char encryptedfileName[1000] = "encrypted_message.enc";
//  char plaintext[1000] = "plaintext.txt";
  char sessionkey[1000] = "sessionkey.txt";
  char ivfileName[1000] = "ivFile.txt";
  
  ofstream ivFile;
  ivFile.open("ivFile.txt");
  
vector<string> ptblocks = d.inputFileReader(argv[1], 1);


  bitset<64> ptblocksbin[ptblocks.size()];

  for (int i = 0; i < ptblocks.size(); i++) 
    ptblocksbin[i] = (d.stringToBinary(ptblocks[i]));

  vector<string> keyBlocks = d.inputFileReader(sessionkey, 1);
  
  string iv = d.keyGenerator(16);

  for(int i = 0; i < 16; i++) ivFile << iv[i]; //write iv to a file

  bitset<64> keyBin = d.stringToBinary(keyBlocks[0]);
  bitset<64> ivBin = d.hexStringToBinary64(iv);

  std::vector< bitset<48> > keySchedule = d.keyScheduleGenerator(keyBin);

  d.des(encryptedfileName, ptblocksbin, 1, ivBin, ptblocks.size(), keySchedule, 0);

// end of des encrypted
  
// start of signing message
  p.signEncryptedMessage(argv[4]);
// end of signing message  
  
}
