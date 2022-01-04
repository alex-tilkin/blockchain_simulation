//
// Created by Alex Tilkin on 06/03/2021.
//

#ifndef GK8_IOBSERVER_H
#define GK8_IOBSERVER_H


#include "SecuredTransaction.h"

class IObserver {
public:
    virtual ~IObserver() {}
    virtual void update(SecuredTransaction& securedTransaction) = 0;
};


#endif //GK8_IOBSERVER_H
