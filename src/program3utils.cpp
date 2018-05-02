#include "program3utils.h"
#include <fstream>

using namespace std;

void program3utils::writeFile(unsigned char* out, char* fileName) {
  FILE* write;
   
  write = fopen(fileName, "w");
  fwrite(out, 1, 8, write);
  fclose(write);
}

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


void program3utils::getSessionKey(char* files[]) {

  //tppk = third party public key: TA's key.
  //test.txt ../encrypted_session.key ../pubkey.pem ../privkey.pem  

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
  if (!ctx)
     cerr << "Error with the ctx" << endl;
  if (EVP_PKEY_encrypt_init(ctx) <= 0)
     cerr << "Error with the ctx PKEY encrypt" << endl;
  if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_NO_PADDING) <= 0)
     cerr << "Error with the ctx RSA padding" << endl;

  /* Determine buffer length */
  if (EVP_PKEY_encrypt(ctx, NULL, &outlen, in, inlen) <= 0)
     cerr << "Error with the ctx RSA padding" << endl;
  
  cout << outlen << "this is outlen" << endl;
  out = (unsigned char*)OPENSSL_malloc(outlen);

  if (!out)
     cerr << "Error generating out malloc" << endl;

  if (EVP_PKEY_encrypt(ctx, out, &outlen, in, inlen) <= 0)
     cerr << "Error with EVP PKEY encrypt" << endl;

  /* Encrypted data is outlen bytes written to buffer out */

  writeFile(out, sessionkeyfileName);
  fclose(tppk);
  free(in);
  free(out);
    
}

void program3utils::signEncryptedMessage(char* privkeyName) {

 EVP_PKEY_CTX *ctx;
 /* md is a SHA-256 digest in this example. */
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
 if (!ctx) {
     cerr << "ctx error!" << endl;
     exit(1);
 }
     /* Error occurred */
 if (EVP_PKEY_sign_init(ctx) <= 0) {
     cerr << "EVP sign init error!" << endl;
     exit(1);
 }
     /* Error */
 if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING) <= 0) {
     cerr << "RSA padding errors!" << endl;
     exit(1);
 }
     /* Error */
 if (EVP_PKEY_CTX_set_signature_md(ctx, EVP_sha256()) <= 0) {
     cerr << "PKEY set sig error!" << endl;
     exit(1);
 }
     /* Error */

 /* Determine buffer length */
 if (EVP_PKEY_sign(ctx, NULL, &siglen, md, mdlen) <= 0) {
     cerr << "PKEY sign error!" << endl;
     exit(1);
 }
     /* Error */

 sig = (unsigned char*)OPENSSL_malloc(siglen);

 if (!sig) {
     cerr << "sig error!" << endl;
     exit(1);
 }
     /* malloc failure */

 if (EVP_PKEY_sign(ctx, sig, &siglen, md, mdlen) <= 0) {
     cerr << "PKEY sign error 2!" << endl;
     exit(1);
 }
     /* Error */

 /* Signature is siglen bytes written to buffer sig */
 siglen = 256;
 FILE* encSign = fopen("enc_sign.txt", "w");
 fwrite(sig, 1, siglen, encSign);
 
 fclose(encSign);
 fclose(privkey);
 fclose(encMsg);
 free(sig);
 free(md);
    
}

void program3utils::verifySignature(char* files[]) {


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
 if (!ctx) {
     cerr << "ctx error!" << endl;
     exit(1);
 }
     /* Error occurred */
 if (EVP_PKEY_verify_init(ctx) <= 0) {
     cerr << "EVP sign init error!" << endl;
     exit(1);
 }
     /* Error */
 if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING) <= 0) {
     cerr << "RSA padding errors!" << endl;
     exit(1);
 }
     /* Error */
 if (EVP_PKEY_CTX_set_signature_md(ctx, EVP_sha256()) <= 0) {
     cerr << "PKEY set sig error!" << endl;
     exit(1);
 }
     /* Error */
    ret = EVP_PKEY_verify(ctx, sig, siglen, md, mdlen);
//    cout << ret << endl;
    
    (ret) ? cout << "Signature valid" << endl : cout << "Signature not valid" << endl;  
      
}
