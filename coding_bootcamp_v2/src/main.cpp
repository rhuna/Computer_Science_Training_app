#include "MainWindow.h"

#include <QApplication>
#include <QIcon>
#include <QPixmap>
#include <QSplashScreen>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("CS Bootcamp Desktop");
    QApplication::setApplicationVersion("15.0.0");
    QApplication::setOrganizationName("LocalLearningLab");
    QApplication::setWindowIcon(QIcon(":/assets/app_icon.png"));

    QSplashScreen splash(QPixmap(":/assets/splash.png"));
    splash.show();
    splash.showMessage("Loading curriculum, progress database, and release tools...", Qt::AlignBottom | Qt::AlignCenter, Qt::white);
    app.processEvents();

    MainWindow window;
    window.show();
    splash.finish(&window);

    return app.exec();
}
