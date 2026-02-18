#include "CalculatorWindow.h"
#include "OperationFactory.h"
#include <QMessageBox>

CalculatorWindow::CalculatorWindow(QWidget *parent) : QWidget(parent) {
    input1 = new QDoubleSpinBox;
    input2 = new QDoubleSpinBox;
    display = new QLCDNumber;
    display->setDigitCount(10);

    QString ops[5] = {"+", "-", "*", "/", "Clear"};
    QGridLayout *layout = new QGridLayout(this);

    layout->addWidget(input1, 0, 0, 1, 2);
    layout->addWidget(input2, 1, 0, 1, 2);
    layout->addWidget(display, 2, 0, 1, 2);

    for (int i = 0; i < 5; ++i) {
        buttons[i] = new QPushButton(ops[i]);
        if (i < 4)
            connect(buttons[i], &QPushButton::clicked, this, &CalculatorWindow::onOperationClicked);
        else
            connect(buttons[i], &QPushButton::clicked, this, &CalculatorWindow::onClearClicked);
        layout->addWidget(buttons[i], 3 + i / 2, i % 2);
    }
}

void CalculatorWindow::onOperationClicked() {
    QPushButton *senderBtn = qobject_cast<QPushButton*>(sender());
    if (!senderBtn) return;

    char op = senderBtn->text().toStdString()[0];
    double x = input1->value();
    double y = input2->value();

    if (op == '/' && y == 0) {
        QMessageBox::warning(this, "Error", "Cannot divide by zero.");
        return;
    }

    Operation *operation = OperationFactory::getInstance()->createOperation(op);
    if (!operation) {
        QMessageBox::warning(this, "Error", "Invalid operation.");
        return;
    }

    double result = operation->compute(x, y);
    display->display(result);
    delete operation;
}

void CalculatorWindow::onClearClicked() {
    input1->setValue(0.0);
    input2->setValue(0.0);
    display->display(0.0);
}