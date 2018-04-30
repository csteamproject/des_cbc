#!/bin/bash

make clean
make part2
./part2 plaintext.txt encrypted_session.key pubkey.pem privkey.pem
