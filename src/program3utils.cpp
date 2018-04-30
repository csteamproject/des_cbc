#include "program3utils.h"

using namespace std;

void program3utils::writeFile(unsigned char* out, char* fileName) {
  FILE* write;
   
  write = fopen(fileName, "w");
  fwrite(out, 1, 8, write);
  fclose(write);
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

  writeFile(out, "sessionkey.txt");
  fclose(tppk);
  free(in);
  free(out);
    
}
