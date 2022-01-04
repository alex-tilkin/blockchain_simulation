#ifndef GK8_UTILS_H
#define GK8_UTILS_H

#define MAX_FEE 100
#define MIN_FEE 1

static const int generateFee() {
    return rand() % MAX_FEE + MIN_FEE;
}

static string toString(const uint8_t *arr, int size)
{
    int index;
    std::string result = "";

    for (index = 0; index < size; index++) {
        result += std::to_string(arr[index]);
    }

    return result;
}

static bool isEqual(uint8_t* signatureA, uint8_t* signatureB){
    for (int index = 0; index < SIG_LENGTH; ++index) {
        if(signatureA[index] != signatureB[index]){
            return false;
        }
    }

    return true;
}

#endif //GK8_UTILS_H