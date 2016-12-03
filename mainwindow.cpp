#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "trem.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    trem1 = new Trem(1,130, 30);
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    trem1->setVelocidade(50);
    trem1->start();

    Trem *trem2 = new Trem(2,130,240);
    connect(trem2, SIGNAL(updateGUI(int,int,int)), SLOT(updateInterface(int,int,int)));
    trem2->setVelocidade(90);
    trem2->start();

    Trem *trem3 = new Trem(3,420, 140);
    connect(trem3, SIGNAL(updateGUI(int,int,int)), SLOT(updateInterface(int,int,int)));
    trem3->setVelocidade(120);
    trem3->start();

    Trem *trem4 = new Trem(4, 420, 350);
    connect(trem4, SIGNAL(updateGUI(int,int,int)), SLOT(updateInterface(int,int,int)));
    trem4->setVelocidade(100);
    trem4->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateInterface(int id, int x, int y)
{
    switch(id){
        case 1:
            ui->labelTrem01->setGeometry(x,y,20,20);
            break;
        case 2:
            ui->labelTrem02->setGeometry(x,y,20,20);
            break;

        case 3:
            ui->labelTrem03->setGeometry(x,y,20,20);
            break;

        case 4:
            ui->labelTrem04->setGeometry(x, y, 20, 20);
            break;

        default:
            break;
    }
}

