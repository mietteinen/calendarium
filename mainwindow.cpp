#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->yearBox->setMaximum(3000);
    ui->yearBox->setMinimum(1000);

    ui->monthBox->setMaximum(12);
    ui->monthBox->setMinimum(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

