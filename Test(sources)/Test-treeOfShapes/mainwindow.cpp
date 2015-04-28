//#include "Image.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_FileSelection_clicked()
{
    QDir *dir = new QDir(QDir::current());
    dir->cd ("../..");
    dir->cd("Images_test");

    // on autorise uniquement l'ouverture des fichiers .png (pour le moment ce sont les seuls qui sont gérés)
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open File"),dir->absolutePath(),tr("Image Files (*.png)"));
//    std::cout << fileNames.front().toStdString()<< std::endl;
    if (!fileNames.empty())
    {
        // récupération de l'url de l'image selectionnée

        QString* file_url = new QString (fileNames.front());
        std::cout << "url de l'image selectionnée : " << file_url->toStdString() << std::endl;
        ui->ImageLabel->setPixmap(QPixmap(*file_url));

        // création de l'image en question à partir de l'url choisie
//        Image<unsigned char>* im = new Image<unsigned char> (file_url->toStdString());

//        // traitement en fonction de la taille de l'image selectionnée
//        if (im->getH()*im->getW()>10000)
//        {
//            ui->InfoLabel->setText("Image trop grande, l'algorithme prendra trop de temps...");
//        }
//        else
//        {
//            ui->InfoLabel->setText("Bonne image");
//        }
    }

}


// gestion des checkBox
void MainWindow::on_Article_version_clicked(bool checked)
{
    ui->modif_version->setChecked(!checked);
}

void MainWindow::on_modif_version_clicked(bool checked)
{
    ui->Article_version->setChecked(!checked);
}

void MainWindow::on_connex4_clicked(bool checked)
{
    ui->connex8->setChecked(!checked);
}

void MainWindow::on_connex8_clicked(bool checked)
{
    ui->connex4->setChecked(!checked);
}
