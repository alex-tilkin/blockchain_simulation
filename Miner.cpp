#include "Miner.h"
#include <unistd.h>

Miner::Miner(string name, int feeThreshold, Blockchain* blockchain, Satoshi balance): BlockchainUser(name, balance), feeThreshold(feeThreshold), currenTransactions(0) {
    this->blockchain = blockchain;
    this->maxTransactionsPerBlock = 1 + rand() % MAX_ENTRIES_IN_BLOCK;
    nextBlock = new Block();
    nextBlock->miner = reinterpret_cast<Address>(this);
    retryTimeout = 500000;

    cout << "Miner created" << endl;
    cout << "\t* Name: " << name << endl;
    cout << "\t* Fee threshold: " << feeThreshold << endl;
    cout << "\t* Transactions per block: " << maxTransactionsPerBlock << endl;
}

bool Miner::tryMining(Transaction& transaction) {
    cout << "Miner " << name << " is trying to mine transaction" << endl;
    if(transaction.fee <= feeThreshold){
        cout << "Miner " << name << " declines transaction request, transaction fee " << transaction.fee << " is less than the " << "fee threshold which is " << feeThreshold << endl;

        return false;
    }

    if(!blockchain->isValid(transaction)){
        cout << "Miner " << name << " declines transaction request, transaction isn't valid" << endl;

        return false;
    }

    nextBlock->trans.push_back(transaction);
    currenTransactions++;

    cout << "Transaction request accepted. You will be notified when the block that contains your transaction will be mined" << endl;
    if(nextBlock->trans.size() >= maxTransactionsPerBlock){
        tryAddingBlockToTheBlockchain();
    }

    return true;
}

void Miner::tryAddingBlockToTheBlockchain() {
    for(vector<Transaction>::iterator transaction = nextBlock->trans.begin(); transaction != nextBlock->trans.end(); transaction++){
        addToPendings(*transaction);
    }

    while(!blockchain->tryAddingBlock(nextBlock)){
        cout << "Miner " << name << " failed to mine a block. Retrying in " << retryTimeout << " microseconds" << endl;
        usleep(retryTimeout);
    }

    Satoshi oldBalance = balance;
    balance += MONEY_CREATED_FOR_THE_MINER_EACH_BLOCK;
    cout << "Miner " << name << " mined a block. " << "Old balance was " << oldBalance << ". The new balance is " << balance << endl;

    minedBlocks.push_back(nextBlock);
    nextBlock = new Block();
    currenTransactions = 0;
}