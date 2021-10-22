

**Original post**: [BUILD A BLOCKCHAIN WITH C++](http://davenash.com/2017/10/build-a-blockchain-with-c/)
# BUILD A BLOCKCHAIN WITH C++

<div align="center">

  <a href="#" alt="License">
        <img src="https://img.shields.io/static/v1?label=License&message=MIT&color=black&style=for-the-badge" /></a>

</div>


 So, you might have heard a lot about something called a blockchain lately and wondered what all the fuss is about. A blockchain is a ledger which has been written in such a way that updating the data contained within it becomes very difficult, some say the blockchain is immutable and to all intents and purposes they’re right but immutability suggests permanence and nothing on a hard drive could ever be considered permanent. Anyway, we’ll leave the philosophical debate to the non-techies; you’re looking for someone to show you how to write a blockchain in C++, so that’s exactly what I’m going to do.

### Before I go any further, I have a couple of disclaimers:

  1. This tutorial is based on one written by Savjee using NodeJS; and
  1. It’s been a while since I wrote any C++ code, so I might be a little rusty.

 The first thing you’ll want to do is open a new C++ project, I’m using CLion from JetBrains but any C++ IDE or even a text editor will do. For the interests of this tutorial we’ll call the project TestChain, so go ahead and create the project and we’ll get started.

 If you’re using CLion you’ll see that the main.cpp file will have already been created and opened for you; we’ll leave this to one side for the time being.

 Create a file called **Block.h in** the main project folder, you should be able to do this by right-clicking on the **TestChain** directory in the Project Tool Window and selecting: New > C/C++ Header File.

Inside the file, add the following code (if you’re using CLion place all code between the lines that read _#define TESTCHAIN_BLOCK_H_ and _#endif_ ):

```cpp
#include <cstdint>
#include <iostream>
```

These lines above tell the compiler to include the cstdint, and iostream libraries.

Add this line below it:
```cpp
using namespace std;
```

This essentially creates a shortcut to the std namespace, which means that we don’t need to refer to declarations inside the std namespace by their full names e.g. _std::string_, but instead use their shortened names e.g. string.

So far, so good; let’s start fleshing things out a little more.

A blockchain is made up of a series of blocks which contain data and each block contains a cryptographic representation of the previous block, which means that it becomes very hard to change the contents of any block without then needing to change every subsequent one; hence where the blockchain essentially gets its immutable properties.

So let’s create our block class, add the following lines to the **Block.h** header file:

```cpp
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

```cpp 
#include <cstdint>
#include <vector>
#include "Block.h"

using namespace std;
```

They tell the compiler to include the cstdint, and vector libraries, as well as the **Block.h header** file we have just created, and creates a shortcut to the std namespace.

Now let’s create our blockchain class, add the following lines to the **Blockchain.h** header file:

```cpp
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

Since blockchains use cryptography, now would be a good time to get some cryptographic functionality in our blockchain. We’re going to be using the SHA256 hashing technique to create hashes of our blocks, we could write our own but really – in this day and age of open source software – why bother?


To make my life that much easier, I copied and pasted the text for the sha256.h, sha256.cpp and LICENSE.txt files shown on the C++ sha256 function from [Zedwood](http://www.zedwood.com/article/cpp-sha256-function) and saved them in the project folder.

Right, let’s keep going.

Create a source file for our block and save it as **Block.cpp** in the main project folder; you should be able to do this by right-clicking on the **TestChain** directory in the Project Tool Window and selecting: New > C/C++ Source File.

Start by adding these lines, which tell the compiler to include the **Block.h** and sha256.h files we added earlier.

```cpp
#include "Block.h"
#include "sha256.h"
```

Follow these with the implementation of our block constructor:

```cpp
Block::Block(uint32_t nIndexIn, const string &sDataIn) : _nIndex(nIndexIn), _sData(sDataIn) {
    _nNonce = -1;
    _tTime = time(nullptr);
}
```

The constructor starts off by repeating the signature we specified in the **Block.h** header file (line 1) but we also add code to copy the contents of the parameters into the the variables _nIndex, and _sData. The _nNonce variable is set to -1 (line 2) and the _tTime variable is set to the current time (line 3).

Let’s add an accessor for the block’s hash:

```cpp
string Block::GetHash() {
    return _sHash;
}
```

We specify the signature for GetHash (line 1) and then add a return for the private variable _sHash (line 2).

As you might have read, blockchain technology was made popular when it was devised for the Bitcoin digital currency, as the ledger is both immutable and public; which means that, as one user transfers Bitcoin to another user, a transaction for the transfer is written into a block on the blockchain by nodes on the Bitcoin network. A node is another computer which is running the Bitcoin software and, since the network is peer-to-peer, it could be anyone around the world; this process is called ‘mining’ as the owner of the node is rewarded with Bitcoin each time they successfully create a valid block on the blockchain.

To successfully create a valid block, and therefore be rewarded, a miner must create a cryptographic hash of the block they want to add to the blockchain that matches the requirements for a valid hash at that time; this is achieved by counting the number of zeros at the beginning of the hash, if the number of zeros is equal to or greater than the difficulty level set by the network that block is valid. If the hash is not valid a variable called a nonce is incremented and the hash created again; this process, called Proof of Work (PoW), is repeated until a hash is produced that is valid.

So, with that being said, let’s add the MineBlock method; here’s where the magic happens!


```cpp
void Block::MineBlock(uint32_t nDifficulty) {
    char cstr[nDifficulty + 1];
    for (uint32_t i = 0; i < nDifficulty; ++i) {
        cstr[i] = '0';
    }
    cstr[nDifficulty] = '\0';

    string str(cstr);

    do {
        _nNonce++;
        _sHash = _CalculateHash();
    } while (_sHash.substr(0, nDifficulty) != str);

    cout << "Block mined: " << _sHash << endl;
}
```

We start with the signature for the MineBlock method, which we specified in the **Block.h header** file (line 1), and create an array of characters with a length one greater that the value specified for nDifficulty (line 2). A **for** loop is used to fill the array with zeros, followed by the final array item being given the string terminator character (\0), (lines 3–6) then the character array or c-string is turned into a standard string (line 8). A **do…while** loop is then used (lines 10–13) to increment the *_nNonce* and *_sHash* is assigned with the output of *_CalculateHash*, the front portion of the hash is then compared the string of zeros we’ve just created; if no match is found the loop is repeated until a match is found. Once a match is found a message is sent to the output buffer to say that the block has been successfully mined (line 15).

We’ve seen it mentioned a few times before, so let’s now add the _CalculateHash method:

```cpp
inline string Block::_CalculateHash() const {
    stringstream ss;
    ss << _nIndex << _tTime << _sData << _nNonce << sPrevHash;

    return sha256(ss.str());
}
```

We kick off with the signature for the *_CalculateHash* method (line 1), which we specified in the Block.h header file, but we include the inline keyword which makes the code more efficient as the compiler places the method’s instructions inline wherever the method is called; this cuts down on separate method calls. A string stream is then created (line 2), followed by appending the values for *_nIndex, _tTime, _sData, _nNonce*, and *sPrevHash* to the stream (line 3). We finish off by returning the output of the sha256 method (from the sha256 files we added earlier) using the string output from the string stream (line 5).

Right, let’s finish off our blockchain implementation! Same as before, create a source file for our blockchain and save it as Blockchain.cpp in the main project folder.

Add these lines, which tell the compiler to include the Blockchain.h file we added earlier.

```cpp
#include "Blockchain.h"
```
Follow these with the implementation of our blockchain constructor:

```cpp
Blockchain::Blockchain() {
    _vChain.emplace_back(Block(0, "Genesis Block"));
    _nDifficulty = 6;
}
```

We start off with the signature for the blockchain constructor we specified in **Blockchain.h** (line 1). As a blocks are added to the blockchain they need to reference the previous block using its hash, but as the blockchain must start somewhere we have to create a block for the next block to reference, we call this a genesis block. A genesis block is created and placed onto the *_vChain* vector (line 2). We then set the *_nDifficulty* level (line 3) depending on how hard we want to make the PoW process.

Now it’s time to add the code for adding a block to the blockchain, add the following lines:

```cpp
void Blockchain::AddBlock(Block bNew) {
    bNew.sPrevHash = _GetLastBlock().GetHash();
    bNew.MineBlock(_nDifficulty);
    _vChain.push_back(bNew);
}
```

The signature we specified in **Blockchain.h** for AddBlock is added (line 1) followed by setting the *sPrevHash* variable for the new block from the hash of the last block on the blockchain which we get using *_GetLastBlock* and its GetHash method (line 2). The block is then mined using the *MineBlock* method (line 3) followed by the block being added to the *_vChain* vector (line 4), thus completing the process of adding a block to the blockchain.

Let’s finish this file off by adding the last method:

```cpp
Block Blockchain::_GetLastBlock() const {
    return _vChain.back();
}
```

We add the signature for *_GetLastBlock* from Blockchain.h (line 1) followed by returning the last block found in the *_vChain* vector using its back method (line 2).

Right, that’s almost it, let’s test it out!

Remember the main.cpp file? Now’s the time to update it, open it up and replace the contents with the following lines:

```c
#include "Blockchain.h"
```
This tells the compiler to include the Blockchain.h file we created earlier.

Then add the following lines:

```c
int main() {
    Blockchain bChain = Blockchain();

    cout << "Mining block 1..." << endl;
    bChain.AddBlock(Block(1, "Block 1 Data"));

    cout << "Mining block 2..." << endl;
    bChain.AddBlock(Block(2, "Block 2 Data"));

    cout << "Mining block 3..." << endl;
    bChain.AddBlock(Block(3, "Block 3 Data"));

    return 0;
}
```

As with most C/C++ programs, everything is kicked off by calling the main method, this one creates a new blockchain (line 2) and informs the user that a block is being mined by printing to the output buffer (line 4) then creates a new block and adds it to the chain (line 5); the process for mining that block will then kick off until a valid hash is found. Once the block is mined the process is repeated for two more blocks.

Time to run it! If you are using CLion simply hit the ‘Run TestChain’ button in the top right hand corner of the window. If you’re old skool, you can compile and run the program using the following commands from the command line:

```bash
gcc -lstdc++ \
    -o TestChain \
    -std=c++11 \
    -stdlib=libc++ \
    -x c++ \
    main.cpp Block.cpp Blockchain.cpp sha256.cpp
./TestChain
```
If all goes well you should see an output like this

    Mining block 1...
    Block mined: 000000c1b50cb30fd8d9a0f2e16e38681cfcf9caead098cea726854925ab3772
    Mining block 2...
    Block mined: 0000005081063c8c854d11560cfea4fe734bde515a08565c26aa05448eea184e
    Mining block 3...
    Block mined: 000000ea61810fa85ff636440eb803263daf06b306c607aced9a1f996a421042

Congratulations, you have just written a blockchain from scratch in C++, in case you got lost I’ve put all the files into a [Github repo](https://github.com/teaandcode/TestChain). Since the original code for Bitcoin was also written in C++, why not take a look at [its code](https://github.com/bitcoin/bitcoin) and see what improvements you can make to what we’ve started off today?

If you have any questions or comments – as always – I’d love to hear them; please put them in the comments below.

<div align="center">

 <a href='https://ko-fi.com/knasher' target='_blank'><img height='35' style='border:0px;height:46px;' src='https://az743702.vo.msecnd.net/cdn/kofi3.png?v=0' border='0' alt='Buy Me a Coffee at ko-fi.com' />

</div>