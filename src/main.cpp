// Robert Dale & Alexander Kurian
// CS 478

#include "desutils.h"

using namespace std;

int main(){
	//variables
	string key, IV;
	desutils d;
	int mode;
	char outputFileName[1000];

	//user inputs
	key = d.getHexStringInput("key");
	IV = d.getHexStringInput("IV");

	mode = d.getMode();
	cout << "Please enter the name of the output file" << endl;
	cin >> outputFileName;

	cout << "Your key is " << key << endl;
	cout << "Your IV is " << IV << endl;

	if(mode == 1) cout << "You are encrypting" << endl;
	else cout << "You are decrypting" << endl;

	bitset<64> keyBin = d.hexStringToBinary64(key);
	vector<bitset<48> > keySchedule = d.keyScheduleGenerator(keyBin);

	//read file
	char inputFile[1000];
	if(mode == 1) cout << "Please enter the file path for file to be encrypted." << endl;
	else cout << "Please enter the file path for file to be decrypted." << endl;

	cin >> inputFile;

	vector<string> inputFileBlocks = d.inputFileReader(inputFile);

	//convert input blocks into binary
	int j1 = 0;
	bitset<64> inputFileBlocksBinary[inputFileBlocks.size()];
	bitset<8> blockToBits;

	for(int i = 0; i < inputFileBlocks.size(); i++) {
		inputFileBlocksBinary[j1] = d.stringToBinary(inputFileBlocks[i]);
		j1++;
	}
	//end of conversion 

	// CBC requires XORing plaintext with old cipher block
	bitset<64> ciMinusOne(d.hexStringToBinary64(IV));
	//end of setting old cipher block
	
	//calling of des function
	d.des(outputFileName, inputFileBlocksBinary, mode, ciMinusOne, inputFileBlocks.size(), keySchedule);
	return 0;
}
