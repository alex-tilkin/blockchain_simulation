#ifndef GK8_BLOCKCHAINUSER_H
#define GK8_BLOCKCHAINUSER_H

#include "SecuredTransaction.h"
#include "IObserver.h"
#include <mutex>

class BlockchainUser: public IObserver {
public:
    BlockchainUser(string name, Satoshi balance);
    void update(SecuredTransaction& securedTransaction);
    void addToPendings(Transaction& transaction);
    void removeFromPendings(Transaction& transactionToRemove);
    string getName(){
        return name;
    }

protected:
    string name;
    Satoshi balance;
    mutex mtx;

private:
    vector<Transaction*> pendings;
};
#endif //GK8_BLOCKCHAINUSER_H
