#include "transactionwindow.h"

TransactionWindow::TransactionWindow(QWidget* parent)
    : QWidget(parent)
{
    dateLabel = new QLabel(this);
    depositButton = new QPushButton("Deposit", this);
    withdrawButton = new QPushButton("Withdraw", this);
    toFileButton = new QPushButton("To File", this);
    amountEdit = new QLineEdit(this);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(dateLabel);
    mainLayout->addWidget(amountEdit);
    mainLayout->addWidget(depositButton);
    mainLayout->addWidget(withdrawButton);
    mainLayout->addWidget(toFileButton);

    connect(depositButton, &QPushButton::clicked, this, &TransactionWindow::onDepositClicked);
    connect(withdrawButton, &QPushButton::clicked, this, &TransactionWindow::onWithdrawClicked);
    connect(toFileButton, &QPushButton::clicked, this, &TransactionWindow::onToFileClicked);

    updateDateLabel();
}

void TransactionWindow::onDepositClicked() {
    handleTransaction(Deposit);
}

void TransactionWindow::onWithdrawClicked() {
    handleTransaction(Withdrawal);
}

void TransactionWindow::onToFileClicked() {
    TransactionList::getInstance()->saveToFile("transactions.txt");
}

void TransactionWindow::handleTransaction(TransactionType type) {
    bool ok;
    double amount = amountEdit->text().toDouble(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Invalid amount entered.");
        return;
    }

    Transaction* transaction = new Transaction(amount, type);
    TransactionList::getInstance()->addTransaction(transaction);
    qDebug() << transaction->getTransactionDetails();
}

void TransactionWindow::updateDateLabel() {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    dateLabel->setText("Current Date: " + currentDateTime.toString());
}

Transaction::Transaction(double amount, TransactionType type)
    : amount(amount), type(type), dateTime(QDateTime::currentDateTime()) {}

QString Transaction::getTransactionDetails() const {
    QString typeStr = (type == Deposit) ? "Deposit" : "Withdrawal";
    return QString("Amount: %1, Type: %2, Date: %3")
            .arg(amount)
            .arg(typeStr)
            .arg(dateTime.toString());
}

TransactionList* TransactionList::getInstance() {
    static TransactionList instance;
    return &instance;
}

TransactionList::TransactionList() {}

void TransactionList::addTransaction(Transaction* transaction) {
    QMutexLocker locker(&mutex);
    transactions.append(transaction);
}

void TransactionList::saveToFile(const QString &fileName) {
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (Transaction* transaction : transactions) {
            out << transaction->getTransactionDetails() << "\n";
        }
    }
}
