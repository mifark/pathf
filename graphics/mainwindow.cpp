#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QEvent>
#define GRSIZE 3000

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
    scene->mapToView();
    scene->clearGrid();
//    scene->createGrid(ui->Universe->size().height(),ui->Universe->size().width());
    scene->createGrid(GRSIZE,GRSIZE);
    scene->gridToView();
    scene->reSetItems();
    ui->Universe->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->Universe->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->sizePolicy().setHeightForWidth(true);
    this->installEventFilter(this);
//    update
}


void MainWindow::mouseReleaseEvent(QMouseEvent *ev)
{
}

void MainWindow::mouseMoveEvent(QMouseEvent *)
{
}

bool MainWindow::eventFilter(QObject *, QEvent * ev)
{
    if(ev->type() == QEvent::Resize)
    {
        scene->clearGrid();
        scene->createGrid(GRSIZE,GRSIZE);
        scene->reSetItems();
    }
}

int MainWindow::heightForWidth(int w) const
{
   return w;
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}
