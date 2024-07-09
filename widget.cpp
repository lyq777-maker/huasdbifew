#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    server = new QTcpServer;
    server->listen(QHostAddress::AnyIPv4,9000);
    connect(server,&QTcpServer::newConnection,this,&Widget::newClient);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::newClient()
{
    QTcpSocket *socket = server->nextPendingConnection();
    socket->peerAddress();
    socket->peerPort();
    ui->lineEdit->setText(socket->peerAddress().toString());
    ui->lineEdit_2->setText(QString::number(socket->peerPort()));

    connect(socket,&QTcpSocket::readyRead, this, &Widget::rmessage);
}


void Widget::rmessage()
{
    QTcpSocket *s=(QTcpSocket*) sender();
    ui->lineEdit_3->setText(QString(s->readAll()));

}
