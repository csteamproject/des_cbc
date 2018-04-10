//Needs to be cleaned up

#include <iostream>
#include <sstream>
#include <bitset>
#include <cstdlib>
//#include <random>
#include <vector>
#include <fstream>

using namespace std;

char hexDigits[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

int keyShifts[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

/********************************************/
/* Tables for initial and final permutation */
/********************************************/

// initial permutation
char IP[64] = {
	58,	50,	42,	34,	26,	18,	10,	2,
	60,	52,	44,	36,	28,	20,	12,	4,
	62,	54,	46,	38,	30,	22,	14,	6,
	64,	56,	48,	40,	32,	24,	16,	8,
	57,	49,	41,	33,	25,	17,	9,	1,
	59,	51,	43,	35,	27,	19,	11,	3,
	61,	53,	45,	37,	29,	21,	13,	5,
	63,	55,	47,	39,	31,	23,	15,	7
};

// final permutation
char FP[64] = {
	40,	8,	48,	16,	56,	24,	64,	32,
	39,	7,	47,	15,	55,	23,	63,	31,
	38,	6,	46,	14,	54,	22,	62,	30,
	37,	5,	45,	13,	53,	21,	61,	29,
	36,	4,	44,	12,	52,	20,	60,	28,
	35,	3,	43,	11,	51,	19,	59,	27,
	34,	2,	42,	10,	50,	18,	58,	26,
	33,	1,	41,	9,	49,	17,	57,	25
};

// PC-1 table (initial key permutation)
int PC1[56] = {
	57,	49,	41,	33,	25,	17,	9,
	1,	58,	50,	42,	34,	26,	18,
	10,	2,	59,	51,	43,	35,	27,
	19,	11,	3,	60,	52,	44,	36,
	63,	55,	47,	39,	31,	23,	15,
	7,	62,	54,	46,	38,	30,	22,
	14,	6,	61,	53,	45,	37,	29,
	21,	13,	5,	28,	20,	12,	4
};

// PC-2 table (permutation for generating each subkey)
int PC2[48] = {
	14,	17,	11,	24,	1,	5,	3,	28,
	15,	6,	21,	10,	23,	19,	12,	4,
	26,	8,	16,	7,	27,	20,	13,	2,
	41,	52,	31,	37,	47,	55,	30,	40,
	51,	45,	33,	48,	44,	49,	39,	56,
	34,	53,	46,	42,	50,	36,	29,	32
};

/*********************************/
/* Tables for the round function */
/*********************************/

// expansion box
char E[48] = {
	32,	1,	2,	3,	4,	5,
	4,	5,	6,	7,	8,	9,
	8,	9,	10,	11,	12,	13,
	12,	13,	14,	15,	16,	17,
	16,	17,	18,	19,	20,	21,
	20,	21,	22,	23,	24,	25,
	24,	25,	26,	27,	28,	29,
	28,	29,	30,	31,	32,	1
};

// substitution boxes
// addressable using xxyyyy where xx are the first and last bits, and yyyy are the middle 4 bits
char S1[64] = {
	14,	4,	13,	1,	2,	15,	11,	8,	3,	10,	6,	12,	5,	9,	0,	7,
	0,	15,	7,	4,	14,	2,	13,	1,	10,	6,	12,	11,	9,	5,	3,	8,
	4,	1,	14,	8,	13,	6,	2,	11,	15,	12,	9,	7,	3,	10,	5,	0,
	15,	12,	8,	2,	4,	9,	1,	7,	5,	11,	3,	14,	10,	0,	6,	13
};

char S2[64] = {
	15,	1,	8,	14,	6,	11,	3,	4,	9,	7,	2,	13,	12,	0,	5,	10,
	3,	13,	4,	7,	15,	2,	8,	14,	12,	0,	1,	10,	6,	9,	11,	5,
	0,	14,	7,	11,	10,	4,	13,	1,	5,	8,	12,	6,	9,	3,	2,	15,
	13,	8,	10,	1,	3,	15,	4,	2,	11,	6,	7,	12,	0,	5,	14,	9
};

char S3[64] = {
	10,	0,	9,	14,	6,	3,	15,	5,	1,	13,	12,	7,	11,	4,	2,	8,
	13,	7,	0,	9,	3,	4,	6,	10,	2,	8,	5,	14,	12,	11,	15,	1,
	13,	6,	4,	9,	8,	15,	3,	0,	11,	1,	2,	12,	5,	10,	14,	7,
	1,	10,	13,	0,	6,	9,	8,	7,	4,	15,	14,	3,	11,	5,	2,	12
};

char S4[64] = {
	7,	13,	14,	3,	0,	6,	9,	10,	1,	2,	8,	5,	11,	12,	4,	15,
	13,	8,	11,	5,	6,	15,	0,	3,	4,	7,	2,	12,	1,	10,	14,	9,
	10,	6,	9,	0,	12,	11,	7,	13,	15,	1,	3,	14,	5,	2,	8,	4,
	3,	15,	0,	6,	10,	1,	13,	8,	9,	4,	5,	11,	12,	7,	2,	14
};

char S5[64]  = {
	2,	12,	4,	1,	7,	10,	11,	6,	8,	5,	3,	15,	13,	0,	14,	9,
	14,	11,	2,	12,	4,	7,	13,	1,	5,	0,	15,	10,	3,	9,	8,	6,
	4,	2,	1,	11,	10,	13,	7,	8,	15,	9,	12,	5,	6,	3,	0,	14,
	11,	8,	12,	7,	1,	14,	2,	13,	6,	15,	0,	9,	10,	4,	5,	3
};

char S6[64] = {
	12,	1,	10,	15,	9,	2,	6,	8,	0,	13,	3,	4,	14,	7,	5,	11,
	10,	15,	4,	2,	7,	12,	9,	5,	6,	1,	13,	14,	0,	11,	3,	8,
	9,	14,	15,	5,	2,	8,	12,	3,	7,	0,	4,	10,	1,	13,	11,	6,
	4,	3,	2,	12,	9,	5,	15,	10,	11,	14,	1,	7,	6,	0,	8,	13
};

char S7[64] = {
	4,	11,	2,	14,	15,	0,	8,	13,	3,	12,	9,	7,	5,	10,	6,	1,
	13,	0,	11,	7,	4,	9,	1,	10,	14,	3,	5,	12,	2,	15,	8,	6,
	1,	4,	11,	13,	12,	3,	7,	14,	10,	15,	6,	8,	0,	5,	9,	2,
	6,	11,	13,	8,	1,	4,	10,	7,	9,	5,	0,	15,	14,	2,	3,	12
};

char S8[64] = {
	13,	2,	8,	4,	6,	15,	11,	1,	10,	9,	3,	14,	5,	0,	12,	7,
	1,	15,	13,	8,	10,	3,	7,	4,	12,	5,	6,	11,	0,	14,	9,	2,
	7,	11,	4,	1,	9,	12,	14,	2,	0,	6,	10,	13,	15,	3,	5,	8,
	2,	1,	14,	7,	4,	10,	8,	13,	15,	12,	9,	0,	3,	5,	6,	11
};

char* SBOXMAP[] = {S1, S2, S3, S4, S5, S6, S7, S8};

int P[32] = {
               16,   7,  20,  21,
               29,  12,  28,  17,
               1,  15,  23,  26,
               5,  18,  31,  10,
               2,   8,  24,  14,
               32,  27,   3,   9,
               19,  13,  30,   6,
               22,  11,   4,  25
};

//string random_string()
//{
//     string str("0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF");

//     random_device rd;
//     mt19937 generator(rd());

//     shuffle(str.begin(), str.end(), generator);

//     return str.substr(0, 16);    // assumes 32 < number of characters in str         
//}

string keyGenerator(const int len) {
    	string s = "00000000000000000";
	srand((unsigned)time(0));
//    	static const char alphanum[] =
//        "0123456789"
//        "ABCDEF";

    for (int i = 0; i < len; ++i) {
        s[i] = hexDigits[rand() % (sizeof(hexDigits) - 1)];
    }

    s[len] = 0;

    return s;
}

//bitset<64> stringToBinary(string a) {
//	bitset<64> answer;
//	bitset<8> temp;
//	int index = 0;

//	for(int i = 0; i < a.size(); i++) {
//		temp = bitset<8>(a[i]);

//		for(int j = 0; j < 8; j++) {
//			answer[index] = temp[j];
//			index++;

//		}


//	}

////	cout << answer.to_string() << endl;

//	return answer;


//}

bitset<64> stringToBinary(string a) {
	bitset<64> answer;
	bitset<8> temp;
	int index = 0;

	for(int i = 0; i < a.size(); i++) {
		temp = bitset<8>(a[i]);

		for(int j = 0; j < 8; j++) {
			answer[(64-i*8)-(8-j)] = temp[j];
			index++;

		}


	}

//	cout << answer.to_string() << endl;

	return answer;


}

int calcSBoxIndex(bitset<48> b, int s) {

	bitset<2> i;
	bitset<4> j;

	i[1] = b[s];
	i[0] = b[s-5];

	j[3] = b[s-1];
	j[2] = b[s-2];
	j[1] = b[s-3];
	j[0] = b[s-4];

	return (16 * (int)i.to_ulong() + (int)j.to_ulong());
}

bitset<32> fillBitSet(bitset<32> initial, bitset<4> added, int s) {
	bitset<32> answer = initial;

	answer[s] = added[3];
	answer[s-1] = added[2];
	answer[s-2] = added[1];
	answer[s-3] = added[0];

	return answer;

}

bitset<64> combineBitSet(bitset<32> a, bitset<32> b) {
	bitset<64> answer;
	int i;

	for(i = 0; i < 32; i++) answer[i] = b[i];

	for( ; i < 64; i++) answer[i] = a[i-32];

//	cout << answer << endl;

	return answer;




}

//bitset<28> circularShift(bitset<28> s, unsigned shiftBy) {

//	bitset<28> answer = s << shiftBy | s >> (28-shiftBy);

//	return answer;

//}

string pad(string a, int blockLength) {
	string answer = "00000000";
	int padLength = 8 - blockLength;


	for(int i = 0; i < 8; i++) answer[i] = (char)padLength;


	for(int i = 0; i < blockLength; i++) answer[i] = a[i];


	return answer;


}

char next8BitsToChar(bitset<64> a, int s) {
	bitset<8> temp;


	for(int i = s; i < s+8; i++) temp[i-s] = a[i];

//	if(s == 56) cout << "The eight bits are " << temp << endl;


	return (char)(int)temp.to_ulong();


}

int main(){

//key scheduling

	string key, IV;

//**************uncomment****************

	while(key.length() != 16) {
	cout << "Please enter your key or enter -1 for a key to be generated" << endl;

	cin >> key;

	if(!key.compare("-1")) { 

		cout << endl;

		key = keyGenerator(16);

		break;

	}

	if(key.length() != 16) cout << "Your key is not the correct number of bits" << " it is " << key.length()*4 << " bits" << endl;

	if(key.length() == 16) {
		if(key.find_first_not_of("abcdefABCDEF0123456789") != string::npos) {
			cout << "The key contains invalid characters. Please enter only hexadecimal digits" << endl;
			key = "";
			continue;
		}

	}
	
	}
//**************uncomment****************

	while(IV.length() != 16) {
	cout << "Please enter your IV or enter -1 for an IV to be generated" << endl;

	cin >> IV;

	if(!IV.compare("-1")) { 

		cout << endl;

		IV = keyGenerator(16);

		break;

	}

	if(IV.length() != 16) cout << "Your IV is not the correct number of bits" << " it is " << key.length()*4 << " bits" << endl;

	if(IV.length() == 16) {
		if(IV.find_first_not_of("abcdefABCDEF0123456789") != string::npos) {
			cout << "The IV contains invalid characters. Please enter only hexadecimal digits" << endl;
			IV = "";
			continue;
		}

	}
	
	}
//comment
//	key = "133457799BBCDFF1";
//comment

	int mode = -1, modeTemp;
	string modeString;

	while(mode != 1 && mode != 2){

		cout << "Select mode. Enter 1 for encryption or 2 for decryption" << endl;


		cin >> modeString;

		stringstream modeConvert(modeString);

		modeConvert >> modeTemp;

		cout << modeTemp << endl;


		if(modeTemp != 1 && modeTemp != 2) cout << "That is not a valid entry." << endl;

		else mode = modeTemp;



	}

	char outputFileName[1000];

	cout << "Please enter the name of the output file" << endl;


	cin >> outputFileName;

	

	cout << "Your key is " << key << endl;

	cout << "Your IV is " << IV << endl;

	if(mode == 1) cout << "You are encrypting" << endl;

	else cout << "You are decrypting" << endl;

	stringstream ss;

	ss << hex << key;

	unsigned long long n;

	ss >> n;

	bitset<64> b(n);

//	cout << "In binary: " << b << endl;

//	cout << "Bit 67 is " << b[67] << endl;

	bitset<56> kPlus;
	

	for(int i = 56; i > 0; i--){
		kPlus[i-1] = b[64-PC1[56-i]];

//		if(PC1[56-i] == 33) cout << "The bit is " << b[64-PC1[56-i]] << endl;

	}


//	cout << "K+ = " << kPlus.to_string() << endl;

//split key
	bitset<56> andSet (0b00000000000000000000000000001111111111111111111111111111);
	
//	bitset<28> c0;
//	bitset<28> d0;

	bitset<28> cshifts[17];
	bitset<28> dshifts[17];

	bitset<48> keySchedule[16];

	cshifts[0] = bitset<28> (((kPlus >> 28) & andSet).to_ulong());
	dshifts[0] = bitset<28> ((kPlus & andSet).to_ulong());

//end of split key?

//	cout << "c0 = " << cshifts[0].to_string() << endl;
//	cout << "d0 = " << dshifts[0].to_string() << endl;


	for(int i = 1; i < 17; i++){
		cshifts[i] = (cshifts[i-1] << keyShifts[i-1] | cshifts[i-1] >> (28-keyShifts[i-1]));
		dshifts[i] = (dshifts[i-1] << keyShifts[i-1] | dshifts[i-1] >> (28-keyShifts[i-1]));

	}

//	cout << "c1 = " << cshifts[1].to_string() << endl;
//	cout << "d1 = " << dshifts[1].to_string() << endl;

//	cout << "The key schedule is as follows: " << endl;

	for(int i = 0; i < 16; i++){

		for(int j = 48; j > 0; j--) {

			if(PC2[48-j] < 29) keySchedule[i][j-1] = cshifts[i+1][28-PC2[48-j]];

			else keySchedule[i][j-1] = dshifts[i+1][28-(PC2[48-j]-28)];


		}

//		cout << "k" << i+1 << " = " << keySchedule[i].to_string() << endl;

	}

//	cout << "k1 = " << keySchedule[0].to_string() << endl;

//end of key schedule

//read file

	char inputFile[1000];
//***************************uncomment*********
	if(mode == 1) cout << "Please enter the file path for file to be encrypted." << endl;

	else cout << "Please enter the file path for file to be decrypted." << endl;

	cin >> inputFile;
//***************************uncomment*********

	char c;

	string temp = "00000000";

	int i = 0, j = 0;

	vector<string> inputFileBlocks;

	

//	fstream f(inputFile, fstream::in);

//***********uncomment*************
	ifstream inF(inputFile);
//***********uncomment*************

//comment
//	ifstream inF("textfile.txt");
//comment

//output file initialization
	ofstream outputFile;

	outputFile.open(outputFileName);

//	if(mode == 1)  outputFile.open("encryptedfile");

//	else outputFile.open("decryptedfile");

//end of output file initialization

//	while(f >> noskipws >> c) {

	while(inF.get(c)) {
		temp[i] = c;
		i++;
		if(i == 8){
			inputFileBlocks.push_back(temp);
			temp = "00000000";
			i = 0;
		}
	}

	inF.close();

	if(temp.compare("00000000")) inputFileBlocks.push_back(pad(temp, i));

//end of read file

//	stringstream convertstream;

//	unsigned long long n1;

//convert blocks into binary

	int j1 = 0;

	bitset<64> inputFileBlocksBinary[inputFileBlocks.size()];

	bitset<8> blockToBits;

	

//	for(vector <string> :: iterator i = plaintextBlocks.begin(); i != plaintextBlocks.end(); ++i){

	for(int i = 0; i < inputFileBlocks.size(); i++) {

//		cout << plaintextBlocks[i] << endl;

//		convertstream << hex << *i;

//		convertstream >> n1;
		
//		bitset<64> b(plaintextBlocks[i]);

		inputFileBlocksBinary[j1] = stringToBinary(inputFileBlocks[i]);

//		plaintextBlocksBinary[j1] = bitset<64>(plaintextBlocks[i]);

//		cout << plaintextBlocksBinary[j1].to_string() << endl;

		j1++;


	}

//	cout << "This is the first block " << plaintextBlocksBinary[0] << endl;

//end of block to binary

//temp check stuff

//string mess = "0123456789ABCDEF";

//	stringstream convertstream;

//	convertstream << hex << mess;

//	unsigned long long n1;

//	convertstream >> n1;
//	cout << "First binary is " << plaintextBlocksBinary[0] << endl;
//	plaintextBlocksBinary[0] = bitset<64>(n1);

//	cout << "Now it is " << plaintextBlocksBinary[0] << endl;

//end of temp check
// CBC requires XORing plaintext with old cipher block

	stringstream IVconvertstream;

	IVconvertstream << hex << IV;

	unsigned long long IVn;

	IVconvertstream >> IVn;

	bitset<64> ciMinusOne(IVn);

cout << "The IV in binary is " << ciMinusOne << endl;

//end of setting old cipher block

//go through blocks
for(int i = 0; i < inputFileBlocks.size(); i++) {

	bitset<64> currentBlock;

//applying CBC mode condition if encrypting
	if(mode == 1) currentBlock = (inputFileBlocksBinary[i]^=ciMinusOne);
//end of CBC mode condition if encrypting

	else currentBlock = inputFileBlocksBinary[i];

//initial permuation 
	bitset<64> initialPerm;


	for(int j = 0; j < 64; j++) {
		initialPerm[63-j] = currentBlock[64-IP[j]];  
//select each block
		
//		initialPerm[63-j] = plaintextBlocksBinary[0][64-IP[j]];


	}

//	cout << "Initial Perm is  " << initialPerm << endl;
//end of initial permutation

	bitset<64> andSet1 (0b0000000000000000000000000000000011111111111111111111111111111111);

	bitset<32> lO = bitset<32> (((initialPerm >> 32) & andSet1).to_ulong());
	bitset<32> rO = bitset<32> ((initialPerm & andSet1).to_ulong());

//	cout << "L0 = " << l0 << endl;

//	cout << "R0 = " << r0 << endl;

	bitset<32> lN;
	bitset<32> rN;

	bitset<48> erO;


//rounds
	for(int j = 0; j < 16; j++) {
		lN = rO;

		rN= lO;
//expansion of rOld

		for(int k = 0; k < 48; k++) erO[47-k] = rO[32-E[k]];

//	cout << "E(R0) = " << erO << endl;

//end of expansion

//XOR with key

	if(mode == 1) erO = (erO^=keySchedule[j]);

	else erO = (erO^=keySchedule[15-j]);

//	cout << "E(R0) = " << erO << endl;

//end of XOR

// S boxes
	
//	cout << bitset<4>(S1[2]) << endl;

	bitset<32> sboxOutput;

	bitset<4> sBoxtemp;

	for(int k = 0; k < 8; k++) {
		switch(k) {
			case 0: {
				sBoxtemp = bitset<4>(S1[calcSBoxIndex(erO, 47-k*6)]);
//				cout << (int)calcSBoxIndex(erO, 47-k*6) << endl;
				sboxOutput = fillBitSet(sboxOutput, sBoxtemp, 31-k*4);

//				cout << sboxOutput << endl;
				break;

			}
			case 1: {
				sBoxtemp = bitset<4>(S2[calcSBoxIndex(erO, 47-k*6)]);
//				cout << (int)calcSBoxIndex(erO, 47-k*6) << endl;
				sboxOutput = fillBitSet(sboxOutput, sBoxtemp, 31-k*4);

				break;

			}
			case 2: {
				sBoxtemp = bitset<4>(S3[calcSBoxIndex(erO, 47-k*6)]);
				sboxOutput = fillBitSet(sboxOutput, sBoxtemp, 31-k*4);
				break;

			}
			case 3: {
				sBoxtemp = bitset<4>(S4[calcSBoxIndex(erO, 47-k*6)]);
				sboxOutput = fillBitSet(sboxOutput, sBoxtemp, 31-k*4);
				break;

			}
			case 4: {
				sBoxtemp = bitset<4>(S5[calcSBoxIndex(erO, 47-k*6)]);
				sboxOutput = fillBitSet(sboxOutput, sBoxtemp, 31-k*4);
				break;

			}
			case 5: {
				sBoxtemp = bitset<4>(S6[calcSBoxIndex(erO, 47-k*6)]);
				sboxOutput = fillBitSet(sboxOutput, sBoxtemp, 31-k*4);
				break;

			}
			case 6: {
				sBoxtemp = bitset<4>(S7[calcSBoxIndex(erO, 47-k*6)]);
				sboxOutput = fillBitSet(sboxOutput, sBoxtemp, 31-k*4);
				break;

			}
			case 7: {
				sBoxtemp = bitset<4>(S8[calcSBoxIndex(erO, 47-k*6)]);
				sboxOutput = fillBitSet(sboxOutput, sBoxtemp, 31-k*4);
//				cout << sboxOutput << endl;
				break;

			}
			default: cout << "Something went wrong" << endl;


		}

	}


// end of S boxes
//permuation of output of s boxes
	bitset<32> pOS;

	for(int k = 0; k < 32; k++) pOS[31-k] = sboxOutput[32-P[k]];


//	cout << pOS << endl;
//end of permutation of output of s boxes

//find rN

rN = (lO^=pOS);

//cout << rN << endl;
//end of rN

	lO = lN;
	rO = rN;
		


	}
//end of rounds

//after rounds combine and apply final permuation

bitset<64> R16L16;

bitset<64> R16L16FP;



R16L16 = combineBitSet(rN, lN);

//final permutation

for(int k = 0; k < 64; k++) R16L16FP[63-k] = R16L16[64-FP[k]];

if(mode == 2) {

	R16L16FP = (R16L16FP^=ciMinusOne);

	ciMinusOne = currentBlock;

}

else ciMinusOne = R16L16FP;

cout << R16L16FP << endl;

for(int k = 7; k >= 0; k--) {

	outputFile << next8BitsToChar(R16L16FP, 8*k);

}

//end of permutation

//resetting ciMinusOne

} 
//end of outer loop for blocks

	outputFile.close();
	return 0;
}
