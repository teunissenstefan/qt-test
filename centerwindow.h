#ifndef CENTERWINDOW_H
#define CENTERWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

namespace Ui {
class CenterWindow;
}

class CenterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CenterWindow(QWidget *parent = nullptr);
    ~CenterWindow();

private slots:
    void on_actionAfsluiten_triggered();

    void on_addButton_clicked();

    void on_itemInput_returnPressed();

    void on_itemsList_itemClicked(QListWidgetItem *item);

    void on_actionOpslaan_triggered();

    void on_actionOpenen_triggered();

    void saveFile(QString filename);

    void SaveFunction();

    void SaveAsFunction();

    void LoadFunction();

    void on_actionOpslaan_Als_triggered();

private:
    Ui::CenterWindow *ui;
    bool saved;
    QString hasFile;
};

#endif // CENTERWINDOW_H
