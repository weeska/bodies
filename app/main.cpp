#include <QMainWindow>
#include <QApplication>

#include "MainWindow.h"
#include "SimulationView.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow window;
    window.showMaximized();

    return app.exec();
}

