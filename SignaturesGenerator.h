#ifndef GK8_SIGNATURESGENERATOR_H
#define GK8_SIGNATURESGENERATOR_H


#include <cstdint>
#include <list>
#include <mutex>
#include "Data.h"

using namespace std;

class SignaturesGenerator {
public:
    static SignaturesGenerator *getInstance();
    bool isValid(const uint8_t* signature, int size);
    void generate(uint8_t* placeholder);

private:
    list<std::array<uint8_t,SIG_LENGTH>> signaturesInUse;
    mutex mtx;

    SignaturesGenerator();
    bool isInUse(array<uint8_t,SIG_LENGTH> candidate);
    array<uint8_t,SIG_LENGTH> generateCandidate() const;
    static SignaturesGenerator* instance;
};


#endif //GK8_SIGNATURESGENERATOR_H