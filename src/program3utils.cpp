#include "program3utils.h"
#include <fstream>

using namespace std;

// Function used to write first 8 bytes of unsigned char pointer to a file
// Used to write session key to file
void program3utils::writeFile(unsigned char* out, char* fileName) {
  FILE* write;
   
  write = fopen(fileName, "w");
  fwrite(out, 1, 8, write);
  fclose(write);
}

// Function that reads a 16 digit long hex string from file
// Used to read IV from file
string program3utils::inputFileReadIV(char inputFile[1000]) {
	char c;
	string temp = "0000000000000000";

	int i = 0, j = 0;

	ifstream inF(inputFile);

	while(inF.get(c) && i != 16) {
		temp[i] = c;
		i++;
	}

	inF.close();
	//end of read file

	return temp;
}

// Function that takes encrypted session key file and outputs decryped session key
// Uses third party public key and library functions
void program3utils::getSessionKey(char* files[]) {

  //tppk = third party public key: TA's key.
  //test.txt ../encrypted_session.key ../pubkey.pem ../privkey.pem  

//set up inputs
  EVP_PKEY_CTX* ctx;
  unsigned char *out, *in;
  size_t outlen, inlen;
  EVP_PKEY* key;
  FILE* write;
  
  FILE* tppk = fopen(files[3], "r");
  FILE* esk = fopen(files[2], "r");
  fseek(esk, 0, SEEK_END);  
  inlen = ftell(esk);
  fseek(esk, 0, SEEK_SET);

  char sessionkeyfileName[100] = "sessionkey.txt";
  
  in = (unsigned char*)malloc(inlen);  
  fread(in, 1, inlen, esk);

  key = PEM_read_PUBKEY(tppk, NULL, NULL, NULL);

  ctx = EVP_PKEY_CTX_new(key, NULL);
//encryption
//error checking
  if (!ctx)
     cerr << "Error with the ctx" << endl;
  if (EVP_PKEY_encrypt_init(ctx) <= 0)
     cerr << "Error with the ctx PKEY encrypt" << endl;
  if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_NO_PADDING) <= 0)
     cerr << "Error with the ctx RSA padding" << endl;

// set outlen
  if (EVP_PKEY_encrypt(ctx, NULL, &outlen, in, inlen) <= 0)
     cerr << "Error with the ctx RSA padding" << endl;
  
  cout << outlen << "this is outlen" << endl;
  out = (unsigned char*)OPENSSL_malloc(outlen);

  if (!out)
     cerr << "Error generating out malloc" << endl;

  if (EVP_PKEY_encrypt(ctx, out, &outlen, in, inlen) <= 0)
     cerr << "Error with EVP PKEY encrypt" << endl;

//encrypted message (decrypted session key) is stored in out

//write session key to file

  writeFile(out, sessionkeyfileName);

// close files and free buffers
  fclose(tppk);
  free(in);
  free(out);
    
}

// Function that signs encrypted message and outputs to a separate file
// Uses a private key and encrypted message file with library functions to sign
void program3utils::signEncryptedMessage(char* privkeyName) {

 //set up of inputs
 EVP_PKEY_CTX *ctx;
 unsigned char *md, *sig;
 size_t mdlen = 32, siglen;
 EVP_PKEY *signing_key;
 
 FILE *encMsg = fopen("encrypted_message.enc", "r");
 FILE *privkey = fopen(privkeyName, "r");
 
 fseek(encMsg, 0, SEEK_END); 
 siglen = ftell(encMsg);
 fseek(encMsg, 0, SEEK_SET);
 
 md = (unsigned char*)malloc(siglen);
 fread(md, 1, siglen, encMsg);
 signing_key = PEM_read_PrivateKey(privkey, NULL, NULL, NULL);
 
 ctx = EVP_PKEY_CTX_new(signing_key, NULL);
//begining of signing
//error checking
 if (!ctx) {
     cerr << "ctx error!" << endl;
     exit(1);
 }
 if (EVP_PKEY_sign_init(ctx) <= 0) {
     cerr << "EVP sign init error!" << endl;
     exit(1);
 }
 if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING) <= 0) {
     cerr << "RSA padding errors!" << endl;
     exit(1);
 }
 if (EVP_PKEY_CTX_set_signature_md(ctx, EVP_sha256()) <= 0) {
     cerr << "PKEY set sig error!" << endl;
     exit(1);
 }

// set siglen
 if (EVP_PKEY_sign(ctx, NULL, &siglen, md, mdlen) <= 0) {
     cerr << "PKEY sign error!" << endl;
     exit(1);
 }

 sig = (unsigned char*)OPENSSL_malloc(siglen);

//check malloc

 if (!sig) {
     cerr << "sig error!" << endl;
     exit(1);
 }

 if (EVP_PKEY_sign(ctx, sig, &siglen, md, mdlen) <= 0) {
     cerr << "PKEY sign error 2!" << endl;
     exit(1);
 }
//end of signing
//signature is written to sig 

//write signature to a file
 siglen = 256;
 FILE* encSign = fopen("enc_sign.txt", "w");
 fwrite(sig, 1, siglen, encSign);

// free buffers and close files
 fclose(encSign);
 fclose(privkey);
 fclose(encMsg);
 free(sig);
 free(md);
    
}

// Function that takes a signature file and encrypted message file as well as a public key
// with library functions to verify a signature 
// Prints out result to console
void program3utils::verifySignature(char* files[]) {

//set up of inputs
 EVP_PKEY_CTX *ctx;

 unsigned char *md, *sig;
 size_t mdlen = 32, siglen;
 EVP_PKEY *verify_key;
 int ret = 0;
 
  FILE *encMsg = fopen(files[3], "r");
  FILE *pubkey = fopen(files[1], "r");
  FILE *signature = fopen(files[4], "r");
 
 fseek(encMsg, 0, SEEK_SET); 
 
 fseek(signature, 0, SEEK_END); 
 siglen = ftell(signature); 
 fseek(signature, 0, SEEK_SET);
 
 md = (unsigned char*)malloc(mdlen);
 sig = (unsigned char*)malloc(siglen);
 fread(md, 1, mdlen, encMsg);
 fread(sig, 1, siglen, signature);

 verify_key = PEM_read_PUBKEY(pubkey, NULL, NULL, NULL);
 
 ctx = EVP_PKEY_CTX_new(verify_key, NULL);

//verification
//error checking
//check ctx
 if (!ctx) {
     cerr << "ctx error!" << endl;
     exit(1);
 }
//initialize
 if (EVP_PKEY_verify_init(ctx) <= 0) {
     cerr << "EVP sign init error!" << endl;
     exit(1);
 }
//pad
 if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING) <= 0) {
     cerr << "RSA padding errors!" << endl;
     exit(1);
 }

 if (EVP_PKEY_CTX_set_signature_md(ctx, EVP_sha256()) <= 0) {
     cerr << "PKEY set sig error!" << endl;
     exit(1);
 }

    ret = EVP_PKEY_verify(ctx, sig, siglen, md, mdlen);
//end of verification

//if value in ret is not 0 then signature is valid
//print out result of verification
    
    (ret) ? cout << "Signature valid" << endl : cout << "Signature not valid" << endl;  
      
}
