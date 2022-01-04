//
// Created by Alex Tilkin on 06/03/2021.
//

#ifndef GK8_SECUREDTRANSACTION_H
#define GK8_SECUREDTRANSACTION_H


#include "Data.h"

class SecuredTransaction {
public:
    SecuredTransaction(Transaction *transaction, Address miner);
    bool tryGet(uint8_t* signature, Address invoker, Satoshi& balance);

private:
    bool authenticate(uint8_t* signature);

    Transaction transaction;
    Address miner;
};


#endif //GK8_SECUREDTRANSACTION_H
