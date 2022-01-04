#include <iostream>
#include <array>
#include "SignaturesGenerator.h"
#include "Blockchain.h"
#include "Trader.h"
#include "Miner.h"
#include "Utils.h"

int main() {
	std::cout << "Hello Blockchain! Very nice to meet you! My name is main()" << std::endl;
    srand((unsigned int)time(NULL));

	Blockchain* blockchain = Blockchain::getInstance();

	SignaturesGenerator* signaturesGenerator = SignaturesGenerator::getInstance();

    Miner goldDigger("\"Gold Digger\"", generateFee(), blockchain, 1000000);
    Miner diamondsAreForever("\"Diamonds are Forever\"", generateFee(), blockchain, 1000000);
    blockchain->attach(&goldDigger);
    blockchain->attach(&diamondsAreForever);

    list<Miner*> miners;
    miners.push_back(&goldDigger);
    miners.push_back(&diamondsAreForever);

    Trader sender("Sender", signaturesGenerator, miners, 1000000);
    Trader receiver("Receiver", signaturesGenerator, miners, 1000000);
    blockchain->attach(&sender);
    blockchain->attach(&receiver);

    for (int index = 0; index < 10; ++index) {
        Satoshi value = 1 + rand() % 1000;
        sender.makeTransaction(value, receiver);
    }

    return 0;
}