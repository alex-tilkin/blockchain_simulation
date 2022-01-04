#ifndef GK8_BLOCKCHAIN_H
#define GK8_BLOCKCHAIN_H

#include <iostream>
#include <vector>
#include <limits>
#include "Data.h"
#include "ISubject.h"
#include "IObserver.h"

using namespace std;

class Blockchain: public ISubject {
public:
    static Blockchain *getInstance();

    //Assumption: all the transaction in the blockchain ("firstBlock linkedlist") are valid
    //return whether or not the new transaction is valid, given this blockchain
    //No need to validate the crypto signature
    bool isValid(const Transaction& newTransaction)const;

    bool tryAddingBlock(Block *newBlock);
    virtual void attach(IObserver* observer);
    virtual void notify(SecuredTransaction* securedTransaction);

private:
    //assumption firstBlock is not null
    Blockchain(Block* firstBlock);

    //not null
    Block * m_firstBlock;
    Block *blocks;
    static Blockchain* instance;
    vector<string> siganturesInUse;
    vector<IObserver*> observers;
};

#endif //GK8_BLOCKCHAIN_H
