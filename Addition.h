#ifndef ADDITION_H
#define ADDITION_H

#include "Operation.h"

class Addition : public Operation {
public:
    double compute(double x, double y) override {
        return x + y;
    }
};

#endif // ADDITION_H