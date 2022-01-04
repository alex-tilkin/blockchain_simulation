#include "Trader.h"
#include "Utils.h"
#include <array>

using namespace std;

Trader::Trader(string name, SignaturesGenerator* signaturesGenerator, list<Miner*> miners, Satoshi balance) : BlockchainUser(name, balance) {
    this->address = reinterpret_cast<Address>(this);
    this->signaturesGenerator = signaturesGenerator;
    this->miners = miners;

    cout << "Trader created. " << "Address " << address << endl;
}

void Trader::addMiner(Miner* miner){
    miners.push_back(miner);
}

void Trader::makeTransaction(Satoshi amount, Trader& to)  {
    cout << "**** " << address << " is making transaction " << "****" << endl;
    Transaction* transaction = createTransaction(amount, reinterpret_cast<Address>(&to));

    to.addToPendings(*transaction);
    addToPendings(*transaction);

    cout << "Looking for miners" << endl;
    for (list<Miner*>::iterator miner = miners.begin(); miner != miners.end(); ++miner){
        if(((*miner)->tryMining(*transaction))){
            cout << "Miner " << (*miner)->getName() << " mined a transaction" << endl;

            return;
        }
    }

    to.removeFromPendings(*transaction);
    removeFromPendings(*transaction);
    cout << "Transaction failed" << endl;
}

Transaction* Trader::createTransaction(Satoshi amount, Address to) {
    Transaction* transaction = new Transaction();
    transaction->from = address;
    transaction->to = to;
    transaction->amount = amount;
    transaction->fee = generateFee();
    transaction->creationTime = time(0);
    signaturesGenerator->generate(transaction->signature);

    cout    << "Transaction created:" << endl
            << "\t* From: " << transaction->from << endl
            << "\t* To: " << transaction->to << endl
            << "\t* Amount: " << transaction->amount << endl
            << "\t* Fee: " << transaction->fee << endl
            << "\t* Time: " << transaction->creationTime << endl
            << "\t* Signature: ";

    for (int index = 0; index < SIG_LENGTH; index++) {
        cout << transaction->signature[index];
    }

    cout << endl;

    return transaction;
}
