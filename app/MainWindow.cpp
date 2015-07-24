#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->connect(ui->showVelocityCheckbox, SIGNAL(toggled(bool)), ui->simulationView, SLOT(setShowVelocities(bool)));
    this->connect(ui->showOctreeCheckbox, SIGNAL(toggled(bool)), ui->simulationView, SLOT(setShowOctree(bool)));
    this->connect(ui->useOctreeCheckbox, SIGNAL(toggled(bool)), ui->simulationView, SLOT(setUseOctree(bool)));
    this->connect(ui->resetButton, SIGNAL(pressed()), ui->simulationView, SLOT(reset()));

    this->ui->showVelocityCheckbox->setChecked(ui->simulationView->showVelocities());
    this->ui->showOctreeCheckbox->setChecked(ui->simulationView->showOctree());
    this->ui->useOctreeCheckbox->setChecked(ui->simulationView->useOctree());
}

MainWindow::~MainWindow()
{
    delete ui;
}
