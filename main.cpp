
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>
#include <QVector>

void countWordsInFile(const QString &filename, bool flagA, bool flagB, bool flagC, bool flagD) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file:" << filename;
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();

    // Remove whitespace and punctuation
    content = content.replace(QRegularExpression("[^\w\s]"), " ").simplified();

    // Split the content into words
    QStringList words = content.split(" ", QString::SkipEmptyParts);

    int countA = 0, countB = 0, countC = 0, countD = 0;

    // Regular Expressions
    QRegularExpression reA("([A-Z][a-zA-Z]{4,})");  // Words longer than 4 chars starting with a capital letter
    QRegularExpression reB("([a-zA-Z]+-[a-zA-Z]+)");  // Hyphenated words
    QRegularExpression reC("([a-zA-Z])\1");  // Words that start and end with the same letter
    QRegularExpression reD("([^aeiouAEIOU][a-zA-Z]*)");  // Words not starting with a vowel

    // Traditional for loop instead of range-based for loop
    for (int i = 0; i < words.size(); ++i) {
        const QString &word = words[i];
        if (flagA && reA.match(word).hasMatch()) {
            countA++;
        }
        if (flagB && reB.match(word).hasMatch()) {
            countB++;
        }
        if (flagC && reC.match(word).hasMatch()) {
            countC++;
        }
        if (flagD && reD.match(word).hasMatch()) {
            countD++;
        }
    }

    // Output the results
    if (flagA) qDebug() << "Count of words with more than 4 chars and starting with a capital letter:" << countA;
    if (flagB) qDebug() << "Count of hyphenated words:" << countB;
    if (flagC) qDebug() << "Count of words that start and end with the same letter:" << countC;
    if (flagD) qDebug() << "Count of words not starting with a vowel:" << countD;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QStringList args = QCoreApplication::arguments();

    // If no arguments are passed
    if (args.size() <= 1) {
        qDebug() << "Usage: count [-a] [-b] [-c] [-d] [file1] [file2] ...";
        return 0;
    }

    bool flagA = false, flagB = false, flagC = false, flagD = false;
    QVector<QString> files;

    // Parse flags and files
    for (int i = 1; i < args.size(); ++i) {
        QString arg = args[i];
        if (arg.startsWith("-")) {
            if (arg.contains("a")) flagA = true;
            if (arg.contains("b")) flagB = true;
            if (arg.contains("c")) flagC = true;
            if (arg.contains("d")) flagD = true;
        } else {
            files.append(arg);
        }
    }

    // If no flags are provided, assume all flags should be set to true
    if (!flagA && !flagB && !flagC && !flagD) {
        flagA = flagB = flagC = flagD = true;
    }

    // If no files are provided, print usage message
    if (files.isEmpty()) {
        qDebug() << "No files provided. Usage: count [-a] [-b] [-c] [-d] [file1] [file2] ...";
        return 0;
    }

    // Traditional for loop instead of range-based for loop
    for (int i = 0; i < files.size(); ++i) {
        const QString &file = files[i];
        countWordsInFile(file, flagA, flagB, flagC, flagD);
    }

    return a.exec();
}
