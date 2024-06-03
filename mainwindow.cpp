#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cmath"
#include "QPainterPath"
#include "QPainter"
#include "QPen"
#include "poland.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    button = new QPushButton(this);
    button->setGeometry(width() - space - buttonwid, space, buttonwid, buttonlen);
    button->setText("build");
    connect(button, SIGNAL(clicked()), this, SLOT(myClicked()));
    ui->label_fx->setGeometry(width() - space - buttonwid, 2 * space + buttonlen, labwid, lablen);
    ui->label_fx->setText("f(x)");
    ui->lineEdit->setGeometry(width() - space - buttonwid, 3 * space + buttonlen + lablen, buttonwid, lablen);
    ui->label_x->setGeometry(width() - space - buttonwid, 4 * space  + buttonlen + 2 * lablen, labwid, lablen);
    ui->label_x->setText("a");
    ui->lineEdit_a->setGeometry(width() - space - buttonwid, 5 * space + buttonlen + 3 * lablen, buttonwid, lablen);
    ui->label_b->setGeometry(width() - space - buttonwid, 6 * space  + buttonlen + 4 * lablen, labwid, lablen);
    ui->label_b->setText("b");
    ui->lineEdit_b->setGeometry(width() - space - buttonwid, 7 * space + buttonlen + 5 * lablen, buttonwid, lablen);
}

void MainWindow::myClicked()
{
    ui->label->setGeometry(5, 5, width() - 5 - 5 - 5 - button->width(), height() - 5 - 5);
    QPixmap pm(width() - 5 - 5 - 5 - button->width(), height() - 5 - 5);
    pm.fill(Qt::white);
    ui->label->setPixmap(pm);


    QString S1 = ui->lineEdit->text();
    QString A = ui->lineEdit_a->text(), B = ui->lineEdit_b->text();
    double xmin = A.toDouble(), xmax = B.toDouble();
    double ymin, ymax;
    int xgmin = 0, xgmax = pm.width();
    int ygmin = 0, ygmax = pm.height();
    double step = (xmax - xmin) / pm.width();

    long double ans;
    int pr = 0;

    for(double i = xmin; i < xmax; i += 0.5){
        QString S2 = S1;
        S2.replace("x", '('+QString::number(i)+')');
        bool q = calculate(S2.toStdString(), ans);
        if(q && pr == 0){
            ymin = ans;
            ymax = ans;
            pr = 1;
        }
        else{
            if(q){
                if(ymax < ans){
                    ymax = ans;
                }
                if(ymin > ans){
                    ymin = ans;
                }
            }
        }
    }
    ymin -= 2;
    ymax += 2;

    double kx = (xgmax - xgmin) / (xmax - xmin);
    double ky = (ygmin - ygmax) / (ymax -ymin);

    QPen pen;
    pen.setColor(Qt::blue);
    QPainterPath path;
    QPainter painter;
    painter.begin(&pm);
    painter.setPen(pen);
    painter.drawLine(xgmin, ygmin - ky * ymax, xgmax, ygmin - ky * ymax);
    painter.drawLine(xgmin - kx * xmin, ygmin, xgmin - kx * xmin, ygmax);
    pen.setColor(Qt::black);
    painter.setPen(pen);

    double x = xmin;
    QString Sx = S1;
    Sx.replace("x", '('+QString::number(x)+')');
    bool q = calculate(Sx.toStdString(), ans);
    double y = ans;
    int xg = xgmin + kx * (x - xmin);
    int yg = ygmin + ky * (y - ymax);
    pr = 0;
    if(q){
        path.moveTo(xg, yg);
    }
    else{
        pr = 1;
    }
    for(int i = xgmin; i < xgmax; i++){
        Sx = S1;
        Sx.replace("x", '('+QString::number(x)+')');
        bool q = calculate(Sx.toStdString(), ans);
        if(ans >= ymax || ans <= ymin){
            pr = 1;
        }
        else{
            if(pr == 1){
                pr = 0;
                y = ans;
                xg = xgmin + kx * (x - xmin);
                yg = ygmin + ky * (y - ymax);
                path.moveTo(xg, yg);
            }
            else{
                y = ans;
                xg = xgmin + kx * (x - xmin);
                yg = ygmin + ky * (y - ymax);
                path.lineTo(xg, yg);
            }
        }
        x += step;
    }
    painter.drawPath(path);
    ui->label->setPixmap(pm);
}

MainWindow::~MainWindow()
{
    delete ui;
}
