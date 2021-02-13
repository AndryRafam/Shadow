![](https://img.shields.io/badge/Code-C++-orange.svg?style=plastic&logo=c%2B%2B)
![](https://img.shields.io/badge/OS-Linux-orange.svg?style=plastic&logo=Linux)
![](https://img.shields.io/badge/Algorithm-AES-orange.svg?style=plastic&logo)
![](https://img.shields.io/badge/Algorithm-Serpent-orange.svg?style=plastic&logo)
![](https://img.shields.io/badge/Algorithm-SHA-orange.svg?style=plastic&logo)
![](https://img.shields.io/badge/Tools-SublimeText-orange.svg?style=plastic&logo)
<h1 align="center"> SHADOW (VERSION 1.0) </h1>
SHADOW is a full double encryption which means that it can encrypt/decrypt a specific file, a specific folder or an entire folder and thus all of its sub folders. The program is based on AES-256, Serpent-256 and SHA-256 and uses GCM (Galois/Counter Mode) as an operation mode for encryption. This program is intended for Linux OS.

<h2 align="left"> PASSWORD RULES </h2>
<h4 align="left"> For encryption, the user needs to confirm the password. (enter it twice)</h4>

	1) Password must be at least 12 Characters long (At least 12 characters).
	2) Password must contains at least ONE Upper character.
	3) Password must contains at least ONE Lower character.
	4) Password must contains at least ONE Digit.
	5) Password must contains at least ONE Special Character.

<h4 align="left"> WARNING FOR DECRYPTION !!! </h4>
This program comes with a security measure, which means that if the user enters the wrong password, the data contained in the files/folders will be erased. (See output example below).

<h2 align="left"> HOW TO RUN ON LINUX </h2>

	1) In command line, go to the program directory.
	2) Type < make > to compile and build the files.
	3) Type ./shadow to run the program. Enjoy.
	
<h2 align="left"> OUTPUT EXAMPLES (ENCRYPTION && DECRYPTION) </h2>
No result is outputted on the terminal. They can be seen directly from the original file(s) / folder(s). The program only output a message that your file(s) / folder(s) has / have been successfully encrypted / decrypted.

<h4 align="left"> File Encryption && Decryption </h4>
![Output](https://github.com/AndryRafam/Shadow/blob/main/Output/FileCrypt.gif)

![Output](https://github.com/AndryRafam/Shadow/blob/main/Output/FileDcrypt.gif)

<h4 align="left"> Specific Folder Encryption && Decryption </h4>
![Output](https://github.com/AndryRafam/Shadow/blob/main/Output/FolderCrypt.gif)

![Output](https://github.com/AndryRafam/Shadow/blob/main/Output/FolderDcrypt.gif)

<h4 align="left"> Entire Folder (and thus all of its sub folders) Encryption && Decryption </h4>
![Output](https://github.com/AndryRafam/Shadow/blob/main/Output/FolderAllCrypt.gif)

![Output](https://github.com/AndryRafam/Shadow/blob/main/Output/FolderAllDcrypt.gif)

<h4 align="left"> Example of error (enter the wrong password for decryption) </h4>
![Ouput](https://github.com/AndryRafam/Shadow/blob/main/Output/ErrorDcrypt.gif)
As we can see, the error message says: "HashVerificationFilter: message hash or MAC not valid.". It means that the hash (signature) of the password we have entered for decryption doesn't not correspond to the hash (signature) of the password we have entered for encryption. Thus, the decryption doesn't work and the data contained in the file has been erased.
