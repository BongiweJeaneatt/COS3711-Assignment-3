#ifndef OPERATIONFACTORY_H
#define OPERATIONFACTORY_H

#include "Addition.h"
#include "Subtraction.h"
#include "Multiplication.h"
#include "Division.h"

class OperationFactory {
private:
    OperationFactory() {}
    OperationFactory(const OperationFactory&) = delete;
    OperationFactory& operator=(const OperationFactory&) = delete;

public:
    static OperationFactory* getInstance() {
        static OperationFactory instance;
        return &instance;
    }

    Operation* createOperation(char op) {
        switch (op) {
            case '+': return new Addition();
            case '-': return new Subtraction();
            case '*': return new Multiplication();
            case '/': return new Division();
            default: return nullptr;
        }
    }
};

#endif // OPERATIONFACTORY_H