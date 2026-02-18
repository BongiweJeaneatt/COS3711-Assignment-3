#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "Operation.h"

class Subtraction : public Operation {
public:
    double compute(double x, double y) override {
        return x - y;
    }
};

#endif // SUBTRACTION_H