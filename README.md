![](https://img.shields.io/badge/Code-C++-orange.svg?style=plastic&logo=c%2B%2B)
![](https://img.shields.io/badge/OS-Linux-orange.svg?style=plastic&logo=Linux)
![](https://img.shields.io/badge/Algorithm-AES-orange.svg?style=plastic&logo)
![](https://img.shields.io/badge/Algorithm-SHA-orange.svg?style=plastic&logo)
![](https://img.shields.io/badge/Tools-SublimeText-orange.svg?style=plastic&logo)
<h1 align="center"> SHADOW </h1>

<h3 algin="left"> About the program </h3>

Shadow is an encryption program (double) using AES-256 in Galois/Counter Mode (GCM) as an encryption algorithm and SHA-256 (for HKDF).
For more information about AES-256, Galois/Counter Mode and HKDF; follow the following links:

AES-256 > https://en.wikipedia.org/wiki/Advanced_Encryption_Standard

GCM > https://en.wikipedia.org/wiki/Galois/Counter_Mode

HKDF > https://en.wikipedia.org/wiki/HKDF

<h3 align="left"> Precision about the output </h3>

Results are not outputted on the screen. The program tells only to the user that the folder/file has been encrypted or decrypted; which is indeed the case.
Open the file / folder to see the result.

![Output](https://github.com/AndryRafam/Shadow/blob/main/Output/folderCrypt.gif)

![Output](https://github.com/AndryRafam/Shadow/blob/main/Output/folderDcrypt.gif)

<h3 align="left"> Precision about the Salt.txt FILE </h3>

The Salt.txt file is as it sounds, a file which contains random strings used as salt parameter for passwords.
The salt parameters (one for each passwords, two by two different) are generated randomly.
Users can update the Salt.txt file at will.

<h3 align="left"> How to run on Linux </h3>

- 1) In command line, go to the program directory.
- 2) Type <make> to compile and build the files.
- 3) Type ./shadow <encrypt/decrypt> to encrypt/decrypt

<h3 align="left"> WARRANTY </h3>
  
  THIS IS A FREE SOFTWARE (GPL Version 3 License) AND IT COMES WITH ABSOLUTELY NO WARRANTY OF ANY KIND.
