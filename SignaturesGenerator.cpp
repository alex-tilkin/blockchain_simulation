#include <array>
#include "SignaturesGenerator.h"

#define MAX_VALUE 100
#define MIN_VALUE 1

SignaturesGenerator *SignaturesGenerator::instance = 0;

SignaturesGenerator *SignaturesGenerator::getInstance() {
    mutex().lock();
    if (!instance) {
        instance = new SignaturesGenerator();
        cout << "SignaturesGenerator created" << endl;
    }
    mutex().unlock();

    return instance;
}

void SignaturesGenerator::generate(uint8_t* placeholder) {
    mtx.lock();

    array<uint8_t,SIG_LENGTH> signatureCandidate;
    do{
        signatureCandidate = generateCandidate();
    } while(isInUse(signatureCandidate));

    for (int index = 0; index < SIG_LENGTH; ++index) {
        placeholder[index] = signatureCandidate.at(index);
    }

    signaturesInUse.push_back(signatureCandidate);

    mtx.unlock();
}

array<uint8_t,SIG_LENGTH> SignaturesGenerator::generateCandidate() const{
    array<uint8_t,SIG_LENGTH> signatureCandidate{};
    for (int index = 0; index < SIG_LENGTH; ++index) {
        signatureCandidate.at(index) = (uint8_t)(MIN_VALUE + rand() % MAX_VALUE);
    }

    return signatureCandidate;
}

bool SignaturesGenerator::isValid(const uint8_t* signature, int size) {
    for (int index = 0; index < size; ++index) {
        if(signature[index] < MIN_VALUE || signature[index] > MAX_VALUE){
            return false;
        }
    }

    return true;
}

bool SignaturesGenerator::isInUse(array<uint8_t,SIG_LENGTH> candidate) {
    std::list<array<uint8_t,SIG_LENGTH>>::iterator iterator;
    for (iterator = signaturesInUse.begin(); iterator != signaturesInUse.end(); ++iterator){
        int counter = 0;
        for (int index = 0; index < candidate.size(); ++index) {
            if(candidate.at(index) != iterator->at(index)){
                break;
            }

            counter++;
        }

        if(counter == SIG_LENGTH){
            return true;
        }
    }

    return false;
}

SignaturesGenerator::SignaturesGenerator() {

}