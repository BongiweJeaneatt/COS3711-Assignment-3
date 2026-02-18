#ifndef CALCULATORWINDOW_H
#define CALCULATORWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLCDNumber>
#include <QGridLayout>

class CalculatorWindow : public QWidget {
    Q_OBJECT

public:
    CalculatorWindow(QWidget *parent = nullptr);

private slots:
    void onOperationClicked();
    void onClearClicked();

private:
    QDoubleSpinBox *input1;
    QDoubleSpinBox *input2;
    QLCDNumber *display;
    QPushButton *buttons[5]; // +, -, *, /, clear
};

#endif // CALCULATORWINDOW_H