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
    previous = NULL;

    //GUI General
    p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    //setPalette(p);

    // To historic
    ui->gui_historic->setEnabled(true);
    ui->gui_historic->setReadOnly(true);
    ui->gui_historic->setPalette(p);

    //To Input
    ui->gui_input->setPalette(p);

   connect(ui->gui_go, SIGNAL (released()), this, SLOT (handleButton()));
   connect(ui->gui_input, SIGNAL (returnPressed()), this, SLOT (handleButton()));
   // To no start in the Debug folder of QTApplication
   chdir("/Users");
   ui->gui_historic->appendHtml("<span style='color: grey'>"+QString::fromStdString(help())+"</span>");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton()
 {
    // Update historic with input
    if (ui->gui_input->text() != NULL){
        ui->gui_historic->setPalette(p);
        ui->gui_historic->appendPlainText(ui->gui_input->text());

        //Update historic with output if has one
        char ** argv = inputByToken(ui->gui_input->text().toStdString());

        //clear input
        ui->gui_input->setText("");

        std::string output = execute(argv, previous);
        if(previous != NULL && strcmp(argv[0], "repetir") != 0) {
            int i = 0;
            while(previous[i] != NULL) {
                delete[] previous[i];
                i++;
            }
            delete[] previous;
         }
         if(strcmp(argv[0], "repetir") != 0)
            previous = argv;
        if (!output.empty()){
            if(output.compare(":") == 0) {
                QApplication::quit();
            }
            ui->gui_historic->appendHtml("<span style='color: grey'>"+QString::fromStdString(output)+"</span>");
        }
    }
 }

