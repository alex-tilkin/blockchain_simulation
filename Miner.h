
#ifndef GK8_MINER_H
#define GK8_MINER_H

#include "Data.h"
#include "Blockchain.h"
#include "IObserver.h"
#include "BlockchainUser.h"
#include <mutex>

class Miner: public BlockchainUser {
public:
    Miner(string name, int feeThreshold, Blockchain* blockchain, Satoshi balance);
    bool tryMining(Transaction& transaction);

private:
    vector<Block*> minedBlocks;
    Block* nextBlock;
    int maxTransactionsPerBlock;
    int currenTransactions;
    int feeThreshold;
    Blockchain* blockchain;
    unsigned int retryTimeout;
    void tryAddingBlockToTheBlockchain();
};


#endif //GK8_MINER_H
