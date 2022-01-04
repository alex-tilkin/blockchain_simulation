#include "SecuredTransaction.h"

SecuredTransaction::SecuredTransaction(Transaction *transaction, Address miner) : transaction(*transaction), miner(miner){

}

bool SecuredTransaction::tryGet(uint8_t* signature, Address invoker, Satoshi& balance){
    if(!authenticate(signature)){
        return false;
    }

    if(invoker == miner){
        balance += transaction.fee;
    } else if(invoker == transaction.from){
        balance -= (transaction.amount + transaction.fee);
    } else if(invoker == transaction.to){
        balance += transaction.amount;
    } else{
        // unknown invoker ignoring...
    }

    return true;
}

bool SecuredTransaction::authenticate(uint8_t* signature){
    for (int index = 0; index < SIG_LENGTH; ++index) {
        if(signature[index] != transaction.signature[index]){
            return false;
        }
    }

    return true;
}

