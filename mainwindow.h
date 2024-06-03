#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QPushButton"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QPushButton * button;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int buttonwid = 200, buttonlen = 70, space = 5, labwid = 30, lablen = 30;

private slots:
    void myClicked();
};

#endif // MAINWINDOW_H
