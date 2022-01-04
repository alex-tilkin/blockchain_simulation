#include "Blockchain.h"
#include "SignaturesGenerator.h"
#include "Utils.h"
#include <algorithm>

#define SIGNATURE_TIMEOUT_SECONDS 30

#define MIN_SUCCESS_RATE 1
#define MAX_SUCCESS_RATE 10
// Success rate is calibrated to 80%. Modify the value below to change the probability
#define SUCCESS_RATE 2

Blockchain *Blockchain::instance = 0;

Blockchain *Blockchain::getInstance()
{
    mutex().lock();
    if (!instance) {
        instance = new Blockchain(new Block());
        cout << "Blockchain created" << endl;
    }

    mutex().unlock();

    return instance;
}

Blockchain::Blockchain(Block* firstBlock):m_firstBlock(firstBlock) {
    blocks = m_firstBlock;
}

bool Blockchain::isValid(const Transaction& newTransaction) const {
    if(!SignaturesGenerator::getInstance()->isValid(newTransaction.signature, SIG_LENGTH)){
        cout << "Invalid signature, transaction isn't valid" << endl;

        return false;
    }

    string signature = toString(newTransaction.signature, SIG_LENGTH);
    if(binary_search(siganturesInUse.begin(), siganturesInUse.end(), signature)){
        cout << "Signature " << signature << " was used, transaction isn't valid" << endl;

        return false;
    }

    time_t now;
    time(&now);
    double diffInSeconds = difftime(now, newTransaction.creationTime);
    if(diffInSeconds > SIGNATURE_TIMEOUT_SECONDS) {
        cout << "More than " << SIGNATURE_TIMEOUT_SECONDS << " passed from the creation of the signature, transaction isn't valid" << endl;

        return false;
    }

    cout << "Transaction is valid" << endl;

    return true;
}

bool Blockchain::tryAddingBlock(Block *newBlock) {
    mutex().lock();

    if((MIN_SUCCESS_RATE + rand() % MAX_SUCCESS_RATE) > SUCCESS_RATE){
        return false;
    }

    blocks->miner = newBlock->miner;
    vector<Transaction>::iterator iterator;
    for (iterator = newBlock->trans.begin(); iterator != newBlock->trans.end(); iterator++) {
        Transaction transaction;

        transaction.creationTime = iterator->creationTime;
        transaction.fee = iterator->fee;
        transaction.amount = iterator->amount;
        transaction.from = iterator->from;
        transaction.to = iterator->to;
        for (int index = 0; index < SIG_LENGTH; index++) {
            transaction.signature[index] = iterator->signature[index];
        }

        string signature = toString(transaction.signature, SIG_LENGTH);
        siganturesInUse.push_back(signature);
        blocks->trans.push_back(transaction);

        notify(new SecuredTransaction(&transaction, blocks->miner));
    }

    blocks->next = new Block();
    blocks = blocks->next;

    mutex().unlock();

    return true;
}

void Blockchain::attach(IObserver* observer){
    observers.push_back(observer);
}

void Blockchain::notify(SecuredTransaction* securedTransaction){
    for(vector<IObserver*>::iterator observer = observers.begin(); observer != observers.end(); observer++){
        (*observer)->update(*securedTransaction);
    }
}
