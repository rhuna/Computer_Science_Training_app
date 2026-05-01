#include "MainWindow.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("CS Bootcamp Desktop");
    QApplication::setOrganizationName("LocalLearningLab");

    MainWindow window;
    window.show();

    return app.exec();
}
