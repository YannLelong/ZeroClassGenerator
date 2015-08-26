#include "mainwindow.h"
#include "codegenwindow.h"

MainWindow :: MainWindow() : QWidget()
{
    /*****************************
    /SECTION 1 : Class definition/
    *****************************/
    name = new QLineEdit;
    motherClass = new QLineEdit;

    definition = new QFormLayout;
    definition->addRow("&Name", name);
    definition->addRow("&Mother class", motherClass);

    definitionBox = new QGroupBox("Class definition");
    definitionBox->setLayout(definition);

    /********************
    /SECTION 2 : Options/
    ********************/
    protectHeader = new QCheckBox("Protect the &header against multiple inclusions");
    protectHeader->setChecked(true);
    generateConstructor = new QCheckBox("Generate a default &constructor");
    generateDestructor = new QCheckBox("Generate a &destructor");

    options = new QVBoxLayout;
    options->addWidget(protectHeader);
    options->addWidget(generateConstructor);
    options->addWidget(generateDestructor);

    optionsBox = new QGroupBox("Options");
    optionsBox->setLayout(options);

    /*********************
    /SECTION 3 : Comments/
    *********************/
    author = new QLineEdit;

    role = new QTextEdit;

    creation = new QDateEdit;
    creation->setDisplayFormat("dd/MM/yyyy");
    creation->setDate(QDate::currentDate());

    comments = new QFormLayout;
    comments->addRow("&Author", author);
    comments->addRow("Crea&tion date", creation);
    comments->addRow("Class &role", role);

    commentsBox = new QGroupBox("Add comments");
    commentsBox->setCheckable(true);
    commentsBox->setChecked(false);
    commentsBox->setLayout(comments);

    /***************************
    /SECTION 4 : Footer buttons/
    ***************************/
    generate = new QPushButton;
    generate->setText("Generate");
    generate->setToolTip("Click to generate the class skeleton");
    //Generate the code on click
    connect(generate,SIGNAL(clicked()),this,SLOT(codeGen()));

    exitButton = new QPushButton;
    exitButton->setText("Exit");
    //Exit the application on click
    connect(exitButton,SIGNAL(clicked()),this,SLOT(exit()));

    footerButtons = new QHBoxLayout;
    footerButtons->setAlignment(Qt::AlignRight);
    footerButtons->addWidget(generate);
    footerButtons->addWidget(exitButton);

    /************
    /MAIN LAYOUT/
    ************/
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(definitionBox);
    mainLayout->addWidget(optionsBox);
    mainLayout->addWidget(commentsBox);
    mainLayout->addLayout(footerButtons);

    /*******
    /WINDOW/
    *******/
    setLayout(mainLayout);
    setWindowTitle("Zero Class Generator");
    setWindowIcon(QIcon("icon.png"));

}

/*****************
/SLOTS DEFINITION/
*****************/

void MainWindow::codeGen()  {
    if(name->text().isEmpty()){ //no class name == no file to generate
        QMessageBox::critical(this,"Error!","You need to at least enter a class name.");
        return;
    }

    QString code;   //the code generated

    if(commentsBox->isChecked()) {   //comments inclusion if true
        code += "/*\nAuthor: " + name->text() +
                "\nCreation date: " + creation->date().toString() +
                "\nClass role:\n" + role->toPlainText() +
                "\n*/\n\n";
    }

    if(protectHeader->isChecked())   {  //avoid double inclusions of file if true
        code += "#ifndef HEADER_" + name->text().toUpper() +
                "\n#define HEADER_" + name->text().toUpper() +
                "\n\n";
    }

    code += "class " + name->text();

    if(!motherClass->text().isEmpty())  {   //add inherited class if specified
        code += " : public : " + motherClass->text();
    }

    code += "\n{\n"
            "   public:\n";

    if(generateConstructor->isChecked())    {   //add a constructor if true
        code += "       " + name->text() +
                "();\n";
    }

    if(generateDestructor->isChecked()) {   //add a destructor if true
        code += "       ~" + name->text() +
                "();\n";
    }

    code += "\n"
            "   protected:\n\n"
            "   private:\n\n"
            "};";

    if(protectHeader->isChecked())  {   //add footer for protection against double inclusions
        code += "\n\n"
                "#endif\n";
    }

    CodeGenWindow *codeGenWindow = new CodeGenWindow(code,this); //creation of the window where the generated code will be displayed
    codeGenWindow->exec();
}

void MainWindow::exit()    {
    int response = QMessageBox::question(this,"Exit?","Do you really want to exit the application?",QMessageBox::Yes|QMessageBox::No);
    if(response == QMessageBox::Yes)
    {
        qApp->exit();
    }
}
