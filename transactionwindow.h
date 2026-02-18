#ifndef TRANSACTIONWINDOW_H
#define TRANSACTIONWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTime>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QMutex>
#include <QDebug>

enum TransactionType { Deposit, Withdrawal };

class Transaction {
public:
    Transaction(double amount, TransactionType type);
    QString getTransactionDetails() const;
    double amount;
    TransactionType type;
    QDateTime dateTime;
};

class TransactionList {
public:
    static TransactionList* getInstance();
    void addTransaction(Transaction* transaction);
    void saveToFile(const QString &fileName);

private:
    TransactionList();
    QList<Transaction*> transactions;
    QMutex mutex;
};

class TransactionWindow : public QWidget {
    Q_OBJECT

public:
    explicit TransactionWindow(QWidget* parent = nullptr);

private slots:
    void onDepositClicked();
    void onWithdrawClicked();
    void onToFileClicked();

private:
    void handleTransaction(TransactionType type);
    void updateDateLabel();

    QLabel* dateLabel;
    QPushButton* depositButton;
    QPushButton* withdrawButton;
    QPushButton* toFileButton;
    QLineEdit* amountEdit;
};

#endif // TRANSACTIONWINDOW_H
