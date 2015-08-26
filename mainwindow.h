#ifndef MAINWINDOW
#define MAINWINDOW

#include <QtWidgets>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void codeGen();
    void exit();

private:
   QPushButton *generate;
   QPushButton *exitButton;

   QLineEdit *name;
   QLineEdit *motherClass;
   QLineEdit *author;

   QTextEdit *role;

   QDateEdit *creation;

   QCheckBox *protectHeader;
   QCheckBox *generateConstructor;
   QCheckBox *generateDestructor;

   QGroupBox *definitionBox;
   QGroupBox *commentsBox;
   QGroupBox *optionsBox;

   QVBoxLayout *mainLayout;
   QVBoxLayout *options;

   QHBoxLayout *footerButtons;

   QFormLayout *definition;
   QFormLayout *comments;
};

#endif // MAINWINDOW

