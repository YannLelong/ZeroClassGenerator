#include "codegenwindow.h"

CodeGenWindow :: CodeGenWindow (QString &code, MainWindow *parent = 0) : QDialog(parent)
{
    /***************
    /CODE INCLUSION/
    ***************/
    genCode = new QTextEdit;
    genCode->setPlainText(code);
    genCode->setFont(QFont("Courier"));
    genCode->setLineWrapMode(QTextEdit::NoWrap);
    genCode->setReadOnly(true);

    /******
    /CLOSE/
    ******/
    close = new QPushButton("Close");
    //Close window on click
    connect(close,SIGNAL(clicked()),this,SLOT(accept()));

    buttonBox = new QHBoxLayout;
    buttonBox->setAlignment(Qt::AlignRight);
    buttonBox->addWidget(close);

    /*******
    /LAYOUT/
    *******/
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(genCode);
    mainLayout->addLayout(buttonBox);

    /*******
    /WINDOW/
    *******/
    setLayout(mainLayout);
    setWindowTitle("ZCG : Generated Code");
    setWindowIcon(QIcon("icon.png"));
    resize(300,450);

}
