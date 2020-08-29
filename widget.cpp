#include "widget.h"
#include "ui_widget.h"

#include "tcpserver.h"
#include "processmsg.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    init();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    ProcessMsg* processer = new ProcessMsg();
    TcpServer* server = TcpServer::getInstance();
    server->setTcpSocketInterface(processer);
    server->listen(QHostAddress::Any, 8080);
}

