#ifndef CODEGENWINDOW
#define CODEGENWINDOW

#include <QtWidgets>
#include "mainwindow.h"

class CodeGenWindow : public QDialog
{
    Q_OBJECT

public:
    CodeGenWindow(QString &code, MainWindow *parent );

private:
    QPushButton *close;

    QTextEdit *genCode;

    QVBoxLayout *mainLayout;

    QHBoxLayout *buttonBox;
};

#endif // CODEGENWINDOW

