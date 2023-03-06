![](https://img.shields.io/badge/Code-C++-orange.svg?style=plastic&logo=c%2B%2B)
![](https://img.shields.io/badge/OS-Linux-orange.svg?style=plastic&logo=Linux)
![](https://img.shields.io/badge/Algorithm-AES-orange.svg?style=plastic&logo)
![](https://img.shields.io/badge/Algorithm-SHA-orange.svg?style=plastic&logo)
![](https://img.shields.io/badge/Tools-SublimeText-orange.svg?style=plastic&logo)
<h1 align="center"> SHADOW </h1>

<h3 algin="left"> About the program </h3>

Shadow is a command line encryption program using AES-256 in Galois/Counter Mode (GCM) as an encryption algorithm and SHA-256 for HKDF (Key Derivation function based on HMAC). The program works with two passwords (each different). For more information about AES-256, Galois/Counter Mode and HKDF (Hash Derivation Key Function), follow the link below.

   - [AES-256](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard)
   - [GCM](https://en.wikipedia.org/wiki/Galois/Counter_Mode)
   - [HKDF](https://en.wikipedia.org/wiki/HKDF)

<h3 algin="left"> Output Example </h3>

![Output](https://github.com/AndryRafam/Shadow/blob/main/Output/out.gif)

<h3 align="left"> Precision about the output </h3>

Results are not outputted on the screen. The program tells only to the user that the folder/file has been encrypted or decrypted; which is indeed the case.
Open the file / folder to see the result.

<h3 align="left"> Precision about the Salt.txt file </h3>

The Salt.txt file is as it sounds, a file which contains random strings used as salt parameter for passwords.
The salt parameters (one for each passwords, two by two different) are generated randomly.
Users can update the Salt.txt file at will.

<h3 align="left"> How to run on Linux </h3>

    1) In command line, go to the program directory.
    2) Type <make> to compile, build and link.
    3) Type ./shadow and press <enter> to run.

<h3 algin="left"> Password Rules </h3>

    1) Each passwords must be at least 16 characters long and different.
    2) Each passwords must contains at least one UPPER CASE character.
    3) Each passwords must contains at least one LOWER CASE character.
    4) Each passwords must contains at least one SPECIAL CASE character.
    5) Each passwords must contains at least one number between 0 to 9.

<h3 align="left"> Supported commands </h3>

<h4 align="left"> General </h4>

* **encrypt**: Enable the encryption mode
* **decrypt**: Enable the decryption mode
* **show_license**: Print the license
* **clear**: Clear the screen
* **quit**: Terminate the program

<h4 algin="left"> Encryption mode </h4>

* **usage**: Print tutorial for encryption mode
* **password**: Print password rules
* **show_license**: Print the license
* **clear**: Clear the screen
* **exit**: Exit the encryption mode
* **quit**: Terminate the program

<h4 align="left"> Decryption mode </h4>

* **usage**: Print tutorial for decryption mode
* **password**: Print password rules
* **show_license**: Print the license
* **clear**: Clear the screen
* **exit**: Exit the decryption mode
* **quit**: Terminate the program
