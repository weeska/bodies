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

//TODO: adjust octree to actual particle distribution
//TODO: use better alternative to euler method
//TODO: navigation
//TODO: optional merging of particles
//TODO: validate barnes hut and naive approach
