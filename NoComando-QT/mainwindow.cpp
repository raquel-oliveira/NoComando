#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //GUI General
    pInput = palette();
    pOutput = palette();
    pInput.setColor(QPalette::Base, Qt::black);
    pOutput.setColor(QPalette::Base, Qt::black);
    pInput.setColor(QPalette::Text, Qt::green);
    pOutput.setColor(QPalette::Text, Qt::gray);
    //setPalette(pInput);

    // To historic
    ui->gui_historic->setEnabled(true);
    ui->gui_historic->setReadOnly(true);
    ui->gui_historic->setPalette(pInput);
    //ui->gui_historic->setMaximumBlockCount(100);

    //To Input
    ui->gui_input->setPalette(pInput);

   connect(ui->gui_go, SIGNAL (released()), this, SLOT (handleButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton()
 {
    // Update historic with input
    if (ui->gui_input->text() != NULL){
        ui->gui_historic->setPalette(pInput);
        ui->gui_historic->appendPlainText(ui->gui_input->text());
        ui->gui_input->setText(""); //clear input
        //TODO: backend to send command
        std::string input = ui->gui_input->text().toStdString();
        ui->gui_historic->setPalette(pOutput);
    }
 }

