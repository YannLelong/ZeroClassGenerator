#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString locale = QLocale::system().name().section('_',0,0);
    //system().name() == fr_FR, en_EN, fr_CA

    QTranslator translator;
    translator.load("zeroclassgenerator_" + locale);
    app.installTranslator(&translator);

    MainWindow window;
    window.show();

    return app.exec();
}
