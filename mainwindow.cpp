#include "mainwindow.h"
#include "ui_mainwindow.h"

//void debugRequest(QNetworkRequest request, QByteArray data = QByteArray())
//{
//  qDebug() << request.url().toString();
//  const QList<QByteArray>& rawHeaderList(request.rawHeaderList());
//  foreach (QByteArray rawHeader, rawHeaderList) {
//    qDebug() << rawHeader << ": " << request.rawHeader(rawHeader);
//  }
//  qDebug() << data;
//}
//void debugResponse(QNetworkReply* reply, QByteArray data = QByteArray())
//{
//  qDebug() << reply->url().toString();
//  const QList<QByteArray>& rawHeaderList(reply->rawHeaderList());
//  foreach (QByteArray rawHeader, rawHeaderList) {
//    qDebug() << reply->rawHeader(rawHeader);
//  }
//  qDebug() << data;
//}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setFocus();
    ui->comboBox->addItem("GET");
    ui->comboBox->addItem("POST");
    ui->comboBox->addItem("HEAD");
}

MainWindow::~MainWindow()
{
    delete r;
    delete ui;
}


// Set enter too TODO

void MainWindow::on_pushButton_clicked()
{
    r = new RestClient();
    auto ret = r->Get(ui->lineEdit->text());
    qDebug().noquote() << ret->readAll();
    QObject::connect(ret.data(), &QNetworkReply::finished, [=]() {
        // qDebug().noquote() <<ret->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(ret->readAll());
        qDebug() << doc.toJson();
        ui->textEdit->setText(doc.toJson());
    });

    auto highlighter = new JsonHighlighter(ui->textEdit->document()); // How does this work anyway?
}


void MainWindow::on_lineEdit_returnPressed()
{
    emit ui->pushButton->clicked();
}
