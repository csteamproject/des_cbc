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
  
  char encryptedfileName[1000] = "encrypted_message.enc";
  char plaintext[1000] = "plaintext.txt";
  char sessionkey[1000] = "sessionkey.txt";
  char ivfileName[1000] = "ivFile.txt";
  
  ofstream ivFile;
  ivFile.open("ivFile.txt");
  //unsigned char ivArray[1000];
  //vector<string> ptblocks = d.inputFileReader("plaintext.txt");
  
vector<string> ptblocks = d.inputFileReader(plaintext, 1);


  bitset<64> ptblocksbin[ptblocks.size()];

  for (int i = 0; i < ptblocks.size(); i++) 
    ptblocksbin[i] = (d.stringToBinary(ptblocks[i]));

  vector<string> keyBlocks = d.inputFileReader(sessionkey, 1);
  
  string iv = d.keyGenerator(16);

  for(int i = 0; i < 16; i++) ivFile << iv[i];

  bitset<64> keyBin = d.stringToBinary(keyBlocks[0]);
  bitset<64> ivBin = d.hexStringToBinary64(iv);

  std::vector< bitset<48> > keySchedule = d.keyScheduleGenerator(keyBin);

  d.des(encryptedfileName, ptblocksbin, 1, ivBin, ptblocks.size(), keySchedule);
  
  //ptblocks = d.inputFileReader("encrypted_message.enc");
  
  
  p.signEncryptedMessage(argv[4]);
  
//end of des
  
  
}
