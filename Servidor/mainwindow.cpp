#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "conexao.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    trem0 = new Trem(0,180,20);
    connect(trem0,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    trem0->start();

    trem0->setVelocidade(200);


    trem1 = new Trem(1,150,200);
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    trem1->start();

    trem1->setVelocidade(160);

    trem2 = new Trem(2,320,120);
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    trem2->start();

    trem2->setVelocidade(200);


    trem3 = new Trem(3,290,320);
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    trem3->start();

    trem3->setVelocidade(250);

    nova = new Conexao();
    nova->start(trem0, trem1, trem2, trem3);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateInterface(int id, int x, int y)
{
    switch(id){
        case 0:
            ui->labelTrem00->setGeometry(x,y,20,20);
            break;
        case 1:
            ui->labelTrem01->setGeometry(x,y,20,20);
            break;
        case 2:
            ui->labelTrem02->setGeometry(x,y,20,20);
            break;
        case 3:
            ui->labelTrem03->setGeometry(x,y,20,20);
            break;
        default:
            break;
    }
}

