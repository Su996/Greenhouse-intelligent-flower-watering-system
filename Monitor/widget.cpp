#include "widget.h"
#include "ui_widget.h"

#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QApplication>
#include <Python.h>
#include <iostream>
#include <QTimer>
#include <QPixmap>
using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("Monitor");
    QFont ft("Microsoft YaHei",20,75);
    ui->label_3->setFont(ft);
    ui->label_4->setFont(ft);

    QFont ftr("Microsoft YaHei",15,75);
    ui->label_6->setFont(ftr);
    ui->label_7->setFont(ftr);
    ui->label_11->setFont(ftr);
    ui->label_12->setFont(ftr);
    ui->label_13->setFont(ftr);
    QFont ftteam("Microsoft YaHei",10,75);
    ui->label_10->setFont(ftteam);

    QFont ftnum;
    ftnum.setPointSize(25);
    ui->label_8->setFont(ftnum);
    ui->label_9->setFont(ftnum);

    QFont fttitle("Microsoft YaHei",15,75);
    QPalette pat;
    pat.setColor(QPalette::WindowText,Qt::blue);
    ui->label_5->setFont(fttitle);
    ui->label_5->setPalette(pat);

    QPixmap pix;
    pix=QPixmap("E:/Eric/Qt files/RTEP/logo.jpg");
    ui->label_14->setPixmap(pix);
    ui->label_14->show();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    timer->start(2000);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::paintEvent(QPaintEvent *ev)
{
    Py_Initialize();
    if ( !Py_IsInitialized() )
    {
 //   return -1;
    }
    PyObject* pModule = PyImport_ImportModule("getdata");  // getdata.py is the python script
    if (!pModule) {
            cout<< "Cant open python file!\n" << endl;
      //      return -1;
        }
    PyObject* pFungetRH= PyObject_GetAttrString(pModule,"getRH");  // function in python script
    PyObject* pFungetTMP= PyObject_GetAttrString(pModule,"getTMP");
    /*
    if(!pFunhello){
        cout<<"Get function hello failed"<<endl;
        return -1;
    }
    */
    PyObject* v1 = PyObject_CallFunction(pFungetRH,NULL);
    PyObject* v2 = PyObject_CallFunction(pFungetTMP,NULL);
    int RH,TMP;
    PyArg_Parse(v1, "i", &RH);
    PyArg_Parse(v2, "i", &TMP);
    qDebug()<<RH<<','<<TMP;

    Py_Finalize();

    ui->label->setText(QString::number(RH)+"%");
    ui->label_2->setText(QString::number(TMP)+"℃");
    QFont ft;
    ft.setPointSize(60);
    QPalette parh;
    QPalette patmp;
    if(RH>60||RH<20)
    {
        parh.setColor(QPalette::WindowText,Qt::red);
    }
    else
        {
        parh.setColor(QPalette::WindowText,Qt::green);
    }
    if(TMP>30||TMP<10)
    {
        patmp.setColor(QPalette::WindowText,Qt::red);
    }
    else
        {
        patmp.setColor(QPalette::WindowText,Qt::green);
    }
    ui->label->setFont(ft);
    ui->label_2->setFont(ft);
    ui->label->setPalette(parh);
    ui->label_2->setPalette(patmp);
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label_2->setAlignment(Qt::AlignCenter);
}

