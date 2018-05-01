#!/bin/bash

make part3
./part3 ourpubkey.pem sessionkey.txt encrypted_message.enc enc_sign.txt
