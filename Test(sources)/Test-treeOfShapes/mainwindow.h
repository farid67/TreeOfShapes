#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <iostream>
//#include "Image.h"
// GROS PROBLEME ici avec le #include "Image.h" qui provoquent une série d'erreurs
// venant de l'ajout de l'application (à la base elle n'était pas prévue)



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_FileSelection_clicked();

    void on_Article_version_clicked(bool checked);

    void on_modif_version_clicked(bool checked);

    void on_connex4_clicked(bool checked);

    void on_connex8_clicked(bool checked);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
