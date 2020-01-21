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
    client = new QNetworkAccessManager();
    ui->setupUi(this);
    ui->lineEdit->setFocus();
    ui->comboBox->addItem("GET");
    ui->comboBox->addItem("POST");
    ui->comboBox->addItem("HEAD");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QUrl qurl(ui->lineEdit->text());
    QNetworkRequest req(qurl);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "*/*");
    req.setAttribute(QNetworkRequest::HTTP2AllowedAttribute, QVariant(true));
    QNetworkReply* reply;
    QUrlQuery query;
    // get postman like table view of to line edits
    // this is so ugly omg kill me
    auto opSwitch = ui->comboBox->currentText();
    if (opSwitch == "GET")
        reply = client->get(req);        
    if (opSwitch == "HEAD")
        reply = client->head(req);
    if (opSwitch == "POST")
        reply = client->post(req, query.query().toUtf8()); // to be continued

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        ui->textEdit->setText(doc.toJson());
        reply->deleteLater(); // kore mo smooth desu
    });

    auto highlighter = new JsonHighlighter(ui->textEdit->document());
    // Where does our highlightBlock gets triggered anyway?


    // Valgrinding ?
    // Diagnostics ?
}


void MainWindow::on_lineEdit_returnPressed()
{
    emit ui->pushButton->clicked(); // Smooth desu
}
