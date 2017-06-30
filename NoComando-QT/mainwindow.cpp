#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <iostream>
#include "shell.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //GUI General
    p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    //setPalette(p);

    // To historic
    ui->gui_historic->setEnabled(true);
    ui->gui_historic->setReadOnly(true);
    ui->gui_historic->setPalette(pInput);

    //To Input
    ui->gui_input->setPalette(pInput);

   connect(ui->gui_go, SIGNAL (released()), this, SLOT (handleButton()));
   // To no start in the Debug folder of QTApplication
   chdir("/Users/Raquel/Desktop/NoComando");
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

        //clear input
        ui->gui_input->setText("");

        //Update historic with output if has one
        char ** inp = inputByToken(ui->gui_input->text().toStdString());
        std::string output = execute(inp);
        if (!output.empty()){
            ui->gui_historic->appendPlainText(QString::fromStdString(output));
        }
    }
 }

