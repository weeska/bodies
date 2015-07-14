#include <QMainWindow>
#include <QApplication>

#include "SimulationView.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QMainWindow window;

    window.setCentralWidget(new SimulationView);
    window.showMaximized();

    return app.exec();
}

