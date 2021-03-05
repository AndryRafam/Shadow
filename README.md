![](https://img.shields.io/badge/Code-C++-orange.svg?style=plastic&logo=c%2B%2B)
![](https://img.shields.io/badge/OS-Linux-orange.svg?style=plastic&logo=Linux)
![](https://img.shields.io/badge/Algorithm-AES-orange.svg?style=plastic&logo)
![](https://img.shields.io/badge/Algorithm-SHA-orange.svg?style=plastic&logo)
![](https://img.shields.io/badge/Tools-SublimeText-orange.svg?style=plastic&logo)
<h1 align="center"> SHADOW </h1>
SHADOW is a full double encryption program which means that it can encrypt/decrypt a specific file, a specific folder or an entire folder and thus all of its sub folders. The program is based on AES-256, Serpent-256 and SHA-256 and uses GCM (Galois/Counter Mode) as an operation mode for encryption. This program is intended for Linux OS.

<h2 align="left"> PASSWORD RULES </h2>
The program requires two passwords for encryption and decryption. Each password must be different.

- 1) Each password must be at least 12 Characters long (At least 12 characters).
- 2) Each password must contains at least ONE Upper character.
- 3) Each password must contains at least ONE Lower character.
- 4) Each password must contains at least ONE Digit.
- 5) Each password must contains at least ONE Special Character.

<h4 align="left"> WARNING FOR DECRYPTION !!! </h4>
This program comes with a security measure, which means that if the user enters the wrong password, the data contained in the files/folders will be erased. (See output example at the last line).

<h2 align="left"> HOW TO RUN ON LINUX </h2>

- 1) In command line, go to the program directory.
- 2) Type < make > to compile and build the files.
- 3) Type ./shadow to run the program. Enjoy.
