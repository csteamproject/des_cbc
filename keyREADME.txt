
Commands used to generate a key [public and private]:

robert@robert $ openssl req -newkey rsa:2048 -nodes -keyout key.pem -x509 -days 365 -out certificate.pem

    BEGIN OUTPUT

    Generating a 2048 bit RSA private key
    ................................+++
    ..................+++
    writing new private key to 'key.pem'
    -----
    You are about to be asked to enter information that will be incorporated
    into your certificate request.
    What you are about to enter is what is called a Distinguished Name or a DN.
    There are quite a few fields but you can leave some blank
    For some fields there will be a default value,
    If you enter '.', the field will be left blank.
    -----
    Country Name (2 letter code) [AU]:US
    State or Province Name (full name) [Some-State]:NM
    Locality Name (eg, city) []:LC
    Organization Name (eg, company) [Internet Widgits Pty Ltd]:    
    Organizational Unit Name (eg, section) []:
    Common Name (e.g. server FQDN or YOUR name) []:NMSU
    Email Address []:

    END OUTPUT


robert@robert $ openssl x509 -text -noout -in certificate.pem

    BEGIN OUTPUT

    Certificate:
        Data:
            Version: 3 (0x2)
            Serial Number: 15352542455019779603 (0xd50f3005868eb613)
        Signature Algorithm: sha256WithRSAEncryption
            Issuer: C=US, ST=NM, L=LC, O=Internet Widgits Pty Ltd, CN=NMSU
            Validity
                Not Before: Apr 24 20:27:21 2018 GMT
                Not After : Apr 24 20:27:21 2019 GMT
            Subject: C=US, ST=NM, L=LC, O=Internet Widgits Pty Ltd, CN=NMSU
            Subject Public Key Info:
                Public Key Algorithm: rsaEncryption
                    Public-Key: (2048 bit)
                    Modulus:
                        00:b5:7f:c3:a3:aa:33:12:ed:3a:5c:48:52:19:21:
                        5d:13:ad:a5:5e:97:4f:0d:35:b8:5a:be:c5:ad:f8:
                        02:13:38:3d:b3:10:d5:32:25:a6:44:58:cc:a6:71:
                        da:67:db:89:17:5d:43:eb:5d:f8:cf:5a:d0:95:83:
                        42:6b:fb:62:fa:d6:fb:1f:e9:81:41:52:14:f4:b0:
                        e4:e4:3b:c3:12:fb:39:ba:40:14:d0:e1:af:8e:34:
                        84:63:dc:a9:50:dd:cb:56:18:85:3c:57:23:4c:39:
                        20:0c:10:ac:e8:ac:be:31:6f:c9:1e:0e:31:30:af:
                        1d:be:80:46:00:2b:67:af:17:75:03:6d:a6:3b:09:
                        14:94:b1:d7:4c:c1:18:31:34:9e:de:d3:d7:d2:4f:
                        a5:be:90:f1:ce:80:8f:c9:f1:7e:81:85:6f:88:17:
                        1d:cf:1c:db:29:fc:e4:75:61:ee:2a:c2:c8:1d:ef:
                        47:20:05:59:b4:2e:27:77:95:bd:bd:49:31:0e:64:
                        d7:e6:b0:3b:5d:80:83:e9:c0:03:e6:ef:4a:ca:9f:
                        f5:47:79:f1:2b:b3:fd:82:93:12:1d:c3:c6:2e:00:
                        44:2a:3f:92:da:18:90:42:9a:90:24:2c:71:28:9a:
                        61:cd:7d:bf:12:26:5d:95:00:c1:b3:ae:e9:33:81:
                        e1:5d
                    Exponent: 65537 (0x10001)
            X509v3 extensions:
                X509v3 Subject Key Identifier: 
                    A0:9E:B5:63:ED:BE:04:BB:D7:8D:17:0B:53:AB:B5:34:38:AE:D8:D0
                X509v3 Authority Key Identifier: 
                    keyid:A0:9E:B5:63:ED:BE:04:BB:D7:8D:17:0B:53:AB:B5:34:38:AE:D8:D0

                X509v3 Basic Constraints: 
                    CA:TRUE
        Signature Algorithm: sha256WithRSAEncryption
             9b:7b:e8:16:35:bf:8f:db:f7:bb:40:c4:67:b8:6d:45:69:3e:
             63:49:9d:90:a6:f2:30:f0:57:74:24:61:a7:7b:74:fb:5b:ea:
             b3:20:84:f3:bf:41:11:1b:42:47:93:b9:c1:cb:cb:14:bb:10:
             8d:22:5a:e7:4b:67:4a:c0:6a:4b:b1:ae:11:8d:35:eb:30:1d:
             0e:3a:38:83:04:14:68:f0:f1:70:2e:e9:dc:ca:f5:5f:87:24:
             ea:2f:0c:c8:73:8c:8e:6e:ef:d6:54:44:34:3a:8c:d5:f2:3b:
             c5:bc:9d:7b:67:c5:d4:37:3e:56:f0:8a:af:b0:5d:8c:19:57:
             25:13:bd:06:17:ee:44:fc:24:b6:ce:32:7f:b6:d1:d7:13:d2:
             d4:74:cb:08:a9:eb:6d:86:a1:49:6c:d6:4d:1c:1d:68:fa:13:
             b1:7c:68:a3:21:0a:27:e8:12:42:a1:29:53:75:6b:67:98:68:
             26:06:4f:2c:d3:08:f0:f2:7c:78:0f:e8:d2:02:11:8c:57:b5:
             11:57:f6:51:72:72:69:a5:a8:a5:15:77:b9:fe:ae:d9:71:e5:
             92:11:f0:ae:94:5b:d6:39:89:f2:00:b2:7e:69:08:ed:4d:84:
             36:4c:1a:31:42:bf:76:b5:78:24:09:4f:f6:c9:d3:ac:3c:ff:
             74:23:2b:23

    END OUTPUT


robert@robert $  openssl pkcs12 -inkey key.pem -in certificate.pem -export -out certificate.p12
    Enter Export Password:
    Verifying - Enter Export Password:

robert@robert $ openssl rsa -in key.pem -pubout -out pubkey.pem
    writing RSA key

