#include "desutils.h"

using namespace std;

int main(int argc, char* argv[]){



  if (argc < 2) {
    cerr << "Not all arguments entered!" << endl;
    return 1;
  }

  cout << "Hello, welcome to the program!" << endl;
  cout << argv[1] << endl;
  cout << argv[2] << endl;
}
