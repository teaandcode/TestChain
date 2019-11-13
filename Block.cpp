//
// Created by Dave Nash on 20/10/2017.
//

#include "Block.h"
#include "sha256.h"

Block::Block(uint32_t nIndexIn, const string &sDataIn) : _nIndex(nIndexIn), _sData(sDataIn)
{
    _nNonce = 0;
    _tTime = time(nullptr);

    sHash = _CalculateHash();
}

void Block::MineBlock(uint32_t nDifficulty)
{
#if (_MSC_VER >= 1500)
	char* cstr = new char[nDifficulty + 1];
#else
	char cstr[nDifficulty + 1];
#endif

    for (uint32_t i = 0; i < nDifficulty; ++i)
    {
        cstr[i] = '0';
    }
    cstr[nDifficulty] = '\0';

    string str(cstr);

    do
    {
        _nNonce++;
        sHash = _CalculateHash();
    }
    while (sHash.substr(0, nDifficulty) != str);

    cout << "Block mined: " << sHash << endl;

#if (_MSC_VER >= 1500)
	delete[] cstr;
#endif
}

inline string Block::_CalculateHash() const
{
    stringstream ss;
    ss << _nIndex << sPrevHash << _tTime << _sData << _nNonce;

    return sha256(ss.str());
}
