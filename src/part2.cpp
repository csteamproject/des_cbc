#include "desutils.h"

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
  
  FILE* esk = p.getFile(argv[2]);
  FILE* tppk = p.getFile(argv[3]);
  FILE* pk = p.getFile(argv[4]);

  
  
}
