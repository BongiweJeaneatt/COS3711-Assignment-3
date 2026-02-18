#ifndef OPERATION_H
#define OPERATION_H

class Operation {
public:
    virtual double compute(double x, double y) = 0;
    virtual ~Operation() {}
};

#endif // OPERATION_H