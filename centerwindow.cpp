#include "centerwindow.h"
#include "ui_centerwindow.h"

CenterWindow::CenterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CenterWindow)
{
    ui->setupUi(this);
    saved = true;
    hasFile = "";
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
        hasFile = filename;
    }
}

void CenterWindow::saveFile(QString filename){
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
        hasFile = filename;
    }
}

void CenterWindow::SaveAsFunction(){
    QString filename = QFileDialog::getSaveFileName();
    saveFile(filename);
}

void CenterWindow::SaveFunction(){
    QString filename = hasFile;
    if(filename==""){
        filename = QFileDialog::getSaveFileName();
    }
    saveFile(filename);
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

void CenterWindow::on_actionOpslaan_Als_triggered()
{
    SaveAsFunction();
}

void CenterWindow::on_actionAbout_triggered()
{
    if(aw==nullptr){
        aw = new AboutWindow();
        aw->show();
    }else{
        QApplication::setActiveWindow(aw);
    }
}
