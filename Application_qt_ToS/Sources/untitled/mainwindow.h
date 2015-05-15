#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <iostream>
//#include "Image.h"


template <typename T>
class Image;

template <typename T>
class ImageInterpolate;



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

    void on_ComputeTOS_clicked();

    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;

    QString* file_url;
};

#endif // MAINWINDOW_H
