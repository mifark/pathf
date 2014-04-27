#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QEvent>
#include <QMouseEvent>
#include "universescene.h"


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int heightForWidth(int) const;

protected:
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    bool eventFilter(QObject *, QEvent *);
    
private slots:
    void on_pbOpen_clicked();

private:
    Ui::MainWindow *ui;
    UniverseScene *scene;

signals:
    void sig_sendMapName(QString send);
    
    
};

#endif // MAINWINDOW_H
