#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new UniverseScene(this);
    ui->Universe->setScene(scene);
    ui->Universe->update();
    ui->Universe->show();
    this->show();
    scene->createGrid(ui->Universe->size().width(),ui->Universe->size().height());
    ui->Universe->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Universe->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    update
}


void MainWindow::mouseReleaseEvent(QMouseEvent *ev)
{
}

void MainWindow::mouseMoveEvent(QMouseEvent *)
{
}




MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}
