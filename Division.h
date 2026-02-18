#ifndef DIVISION_H
#define DIVISION_H

#include "Operation.h"

class Division : public Operation {
public:
    double compute(double x, double y) override {
        return y != 0 ? x / y : 0.0; // Division by zero handled externally
    }
};

#endif // DIVISION_H