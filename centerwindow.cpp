#include "centerwindow.h"
#include "ui_centerwindow.h"

CenterWindow::CenterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CenterWindow)
{
    ui->setupUi(this);
    saved = true;
}

CenterWindow::~CenterWindow()
{
    delete ui;
}

void CenterWindow::on_actionAfsluiten_triggered()
{
    if(!saved){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Onopgeslagen werk", "Weet je zeker dat je wilt afsluiten?",
                                QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            QApplication::quit();
        }
    }else{
        QCoreApplication::quit();
    }
}

void CenterWindow::on_addButton_clicked()
{
    if(ui->itemInput->text()!=""){
        ui->itemsList->addItem(ui->itemInput->text());
        ui->itemInput->setText("");
        ui->itemInput->setFocus();
        saved = false;
    }
}

void CenterWindow::on_itemInput_returnPressed()
{
    ui->addButton->animateClick();
}

void CenterWindow::on_itemsList_itemClicked(QListWidgetItem *item)
{
    delete ui->itemsList->takeItem(ui->itemsList->row(item));
    ui->itemInput->setFocus();
    saved = false;
}

void CenterWindow::LoadFunction(){
    QString filename = QFileDialog::getOpenFileName();
    QFile f( filename );
    if(f.open( QIODevice::ReadOnly )){
        ui->itemsList->clear();
        QTextStream in(&f);

        while(!in.atEnd()) {
            QString line = in.readLine();
            qDebug(line.toLatin1());
            ui->itemsList->addItem(line);
        }
        f.close();
        saved = true;
    }
}

void CenterWindow::SaveFunction(){
    QString filename = QFileDialog::getSaveFileName();
    QFile f( filename );
    if(f.open( QIODevice::WriteOnly )){
        for(int i = 0; i<ui->itemsList->count(); i++){
            QListWidgetItem* item = ui->itemsList->item(i);
            const char* itemTextChar = item->text().toLatin1();
            std::string itemText = itemTextChar;
            qDebug(itemText.c_str());
            f.write(itemText.c_str());
            f.write("\n");
        }
        f.close();
        saved = true;
    }
}

void CenterWindow::on_actionOpslaan_triggered()
{
    SaveFunction();
}

void CenterWindow::on_actionOpenen_triggered()
{
    if(!saved){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Onopgeslagen werk", "Weet je zeker dat dit weg wilt gooien?",
                                QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            LoadFunction();
        }
    }else{
        LoadFunction();
    }
}
