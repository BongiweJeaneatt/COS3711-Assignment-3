#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "Operation.h"

class Multiplication : public Operation {
public:
    double compute(double x, double y) override {
        return x * y;
    }
};

#endif // MULTIPLICATION_H