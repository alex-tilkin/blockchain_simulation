#include "BlockchainUser.h"
#include "Utils.h"

BlockchainUser::BlockchainUser(string name, Satoshi balance) : name(name), balance(balance){

}

void BlockchainUser::update(SecuredTransaction& securedTransaction) {
    mtx.lock();
    Satoshi oldBalance = balance;
    vector<Transaction*>::iterator transaction;
    for(transaction = pendings.begin(); transaction != pendings.end(); transaction++) {
        if(securedTransaction.tryGet((*transaction)->signature, reinterpret_cast<Address>(this), balance)){
            cout << "BlockchainUser " << name << ". Update notification received from the Blockchain. The old Balance was " << oldBalance << ". The new balance is " << balance << endl;
            pendings.erase(transaction);

            break;
        }
    }

    mtx.unlock();
}


void BlockchainUser::addToPendings(Transaction& transaction) {
    mtx.lock();
    pendings.push_back(&transaction);
    mtx.unlock();
}

void BlockchainUser::removeFromPendings(Transaction& transactionToRemove) {
    vector<Transaction*>::iterator it;
    mtx.lock();
    for(it = pendings.begin(); it != pendings.end(); it++){
        if(isEqual((*it)->signature, transactionToRemove.signature)){
            break;
        }
    }

    pendings.erase(it);
    mtx.unlock();
}