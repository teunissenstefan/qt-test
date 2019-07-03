#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "centerwindow.h"
#include "json.hpp"
#include "curl/curl.h"
#include "sstream"
#include "functions.h"
#include "qstring.h"

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
    qDebug() << functions::RemoveChars(j2["value"][0]["Naam_2"].dump().c_str(),"\" ").c_str();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnWeetIk_clicked()
{
    std::string username = j2["value"][0]["Naam_2"].dump().c_str();
    //if(ui->inputGebruikersnaam->text() == username.c_str() && ui->inputWachtwoord->text()=="koerier"){ //werkt
    if(ui->inputGebruikersnaam->text() == functions::RemoveChars(username,"\" ").c_str() && ui->inputWachtwoord->text() == "koerier"){
        CenterWindow *cw = new CenterWindow();
        cw->show();
        this->close();
    }else{
        ui->inputWachtwoord->setText("");
        ui->inputGebruikersnaam->setText("");
        QMessageBox::warning(this, "Helaas", "Inloggen kan niet :'(", QMessageBox::Ok);
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
