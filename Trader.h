#ifndef GK8_TRADER_H
#define GK8_TRADER_H
#include "Blockchain.h"
#include "SignaturesGenerator.h"
#include "Miner.h"
#include "IObserver.h"
#include "BlockchainUser.h"

class Trader: public BlockchainUser {
public:
    Trader(string name, SignaturesGenerator* signaturesGenerator, list<Miner*> miners, Satoshi balance);
    void makeTransaction(Satoshi amount, Trader& to);
    void addMiner(Miner* miner);

private:
    Address address;
    SignaturesGenerator* signaturesGenerator;
    list<Miner*> miners;
    Transaction* createTransaction(Satoshi amount, Address to);
};

#endif //GK8_TRADER_H
