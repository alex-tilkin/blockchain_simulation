//
// Created by Alex Tilkin on 06/03/2021.
//

#ifndef GK8_ISUBJECT_H
#define GK8_ISUBJECT_H

#include "IObserver.h"

class ISubject{
public:
    virtual ~ISubject() {}
    virtual void attach(IObserver* observer) = 0;
    virtual void notify(SecuredTransaction* securedTransaction) = 0;
};
#endif //GK8_ISUBJECT_H
