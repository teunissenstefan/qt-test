#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "centerwindow.h"
#include "json.hpp"
#include "curl/curl.h"
#include "sstream"

using json = nlohmann::json;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string DownloadJSON(std::string URL)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
        struct curl_slist *headers=NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charsets: utf-8");

    curl = curl_easy_init();
    if(curl) {

        curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
                curl_easy_setopt(curl, CURLOPT_HTTPGET,1);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        //qDebug() << readBuffer.c_str();
        res = curl_easy_perform(curl);
        if(CURLE_OK == res) {
            char *ct;
            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
//            if((CURLE_OK == res) && ct)
//                return ct;
            //niet nodig
        }
        return readBuffer;
    }
    curl_easy_cleanup(curl);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->inputGebruikersnaam->setFocus();

    j2 = json::parse(DownloadJSON("https://opendata.cbs.nl/ODataApi/odata/83958NED/TypedDataSet").c_str());
    qDebug() << j2["value"][0]["Woonplaatsen"].dump().c_str();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnWeetIk_clicked()
{
//    if(ui->inputGebruikersnaam->text()=="pizza"&&ui->inputWachtwoord->text()=="koerier"){
    // "WP1925" met quotes?
    if(ui->inputGebruikersnaam->text()==j2["value"][0]["Woonplaatsen"].dump().c_str()&&ui->inputWachtwoord->text()=="koerier"){
//        QMessageBox::question(this, "Gefeliciteerd", "Je bent ingelogd", QMessageBox::Ok);
        CenterWindow *cw = new CenterWindow();
        cw->show();
        this->close();
    }else{
        ui->inputWachtwoord->setText("");
        ui->inputGebruikersnaam->setText("");
        QMessageBox::warning(this, "Helaas", "Inloggen kon niet gebeurden wwwwworden", QMessageBox::Ok);
        ui->inputGebruikersnaam->setFocus();
    }
}

void MainWindow::on_inputWachtwoord_returnPressed()
{
    ui->btnWeetIk->animateClick();
}

void MainWindow::on_inputGebruikersnaam_returnPressed()
{
    ui->btnWeetIk->animateClick();
}

void MainWindow::on_actionStopman_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_actionexit_triggered()
{
    QCoreApplication::quit();
}
