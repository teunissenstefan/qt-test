#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>
#include <json.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnWeetIk_clicked();

    void on_inputWachtwoord_returnPressed();

    void on_inputGebruikersnaam_returnPressed();

    void on_actionStopman_triggered();

    void on_actionexit_triggered();

private:
    Ui::MainWindow *ui;
    nlohmann::json j2;
};

#endif // MAINWINDOW_H
