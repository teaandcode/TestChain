# BUILD A BLOCKCHAIN WITH C++

Here are the files for the TestChain C++ tutorial I have placed on my website [BUILD A BLOCKCHAIN WITH C++](http://davenash.com/2017/10/build-a-blockchain-with-c/)



 So, you might have heard a lot about something called a blockchain lately and wondered what all the fuss is about. A blockchain is a ledger which has been written in such a way that updating the data contained within it becomes very difficult, some say the blockchain is immutable and to all intents and purposes they’re right but immutability suggests permanence and nothing on a hard drive could ever be considered permanent. Anyway, we’ll leave the philosophical debate to the non-techies; you’re looking for someone to show you how to write a blockchain in C++, so that’s exactly what I’m going to do.

### Before I go any further, I have a couple of disclaimers:

  1. This tutorial is based on one written by Savjee using NodeJS; and
  1. It’s been a while since I wrote any C++ code, so I might be a little rusty.

 The first thing you’ll want to do is open a new C++ project, I’m using CLion from JetBrains but any C++ IDE or even a text editor will do. For the interests of this tutorial we’ll call the project TestChain, so go ahead and create the project and we’ll get started.

 If you’re using CLion you’ll see that the main.cpp file will have already been created and opened for you; we’ll leave this to one side for the time being.

 Create a file called **Block.h in** the main project folder, you should be able to do this by right-clicking on the **TestChain** directory in the Project Tool Window and selecting: New > C/C++ Header File.

Inside the file, add the following code (if you’re using CLion place all code between the lines that read _#define TESTCHAIN_BLOCK_H_ and _#endif_ ):

```c
#include <cstdint>
#include <iostream>
```

These lines above tell the compiler to include the cstdint, and iostream libraries.

Add this line below it:
```c
using namespace std;
```

This essentially creates a shortcut to the std namespace, which means that we don’t need to refer to declarations inside the std namespace by their full names e.g. _std::string_, but instead use their shortened names e.g. string.

So far, so good; let’s start fleshing things out a little more.

A blockchain is made up of a series of blocks which contain data and each block contains a cryptographic representation of the previous block, which means that it becomes very hard to change the contents of any block without then needing to change every subsequent one; hence where the blockchain essentially gets its immutable properties.

So let’s create our block class, add the following lines to the **Block.h** header file:

```{.cpp .numberLines}
class Block {
public:
    string sPrevHash;

    Block(uint32_t nIndexIn, const string &sDataIn);

    string GetHash();

    void MineBlock(uint32_t nDifficulty);

private:
    uint32_t _nIndex;
    int64_t _nNonce;
    string _sData;
    string _sHash;
    time_t _tTime;

    string _CalculateHash() const;
};
```
    
 Unsurprisingly, we’re calling our class Block (line 1) followed by the public modifier (line 2) and **public** variable sPrevHash (remember each block is linked to the previous block) (line 3). 

 The constructor signature (line 5) takes three parameters for nIndexIn, and sDataIn; note that the **const** keyword is used along with the reference modifier (**&**) so that the parameters are passed by reference but cannot be changed, this is done to improve efficiency and save memory. 
 
 The GetHash method signature is specified next (line 7) followed by the MineBlock method signature (line 9), which takes a parameter nDifficulty. We specify the private modifier (line 11) followed by the private variables *_nIndex, _nNonce, _sData, _sHash, and _tTime* (lines 12–16). 
 
 The signature for _CalculateHash (line 18) also has the const keyword, this is to ensure the method cannot change any of the variables in the block class which is very useful when dealing with a blockchain.
 
 Now it’s time to create our **Blockchain.h** header file in the main project folder.

Let’s start by adding these lines (if you’re using CLion place all code between the lines that read *#define TESTCHAIN_BLOCKCHAIN_H* and *#endif*):

```{.cpp .numberLines}
#include <cstdint>
#include <vector>
#include "Block.h"

using namespace std;
```

They tell the compiler to include the cstdint, and vector libraries, as well as the **Block.h header** file we have just created, and creates a shortcut to the std namespace.

Now let’s create our blockchain class, add the following lines to the **Blockchain.h** header file:

```c
class Blockchain {
public:
    Blockchain();

    void AddBlock(Block bNew);

private:
    uint32_t _nDifficulty;
    vector<Block> _vChain;

    Block _GetLastBlock() const;
};
```

As with our block class, we’re keeping things simple and calling our blockchain class Blockchain (line 1) followed by the public modifier (line 2) and the constructor signature (line 3). The AddBlock signature (line 5) takes a parameter bNew which must be an object of the Block class we created earlier. We then specify the private modifier (line 7) followed by the private variables for _nDifficulty, and _vChain (lines 8–9) as well as the method signature for _GetLastBlock (line 11) which is also followed by the const keyword to denote that the output of the method cannot be changed.
