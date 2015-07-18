#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->connect(ui->showVelocityCheckbox, SIGNAL(toggled(bool)), ui->simulationView, SLOT(setShowVelocities(bool)));
    this->connect(ui->resetButton, SIGNAL(pressed()), ui->simulationView, SLOT(reset()));

    this->ui->showVelocityCheckbox->setChecked(ui->simulationView->showVelocities());
}

MainWindow::~MainWindow()
{
    delete ui;
}
