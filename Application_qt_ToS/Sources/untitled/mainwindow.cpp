#include "Image.h"

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

        file_url = new QString (fileNames.front());
        std::cout << "url de l'image selectionnée : " << file_url->toStdString() << std::endl;
        ui->ImageLabel->setPixmap(QPixmap(*file_url));
        ui->ComputeTOS->setEnabled(true);
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

void MainWindow::on_ComputeTOS_clicked()
{
    if (ui->Article_version->isChecked())
        finalToS2(file_url->toStdString());
    else
    {
        Image<unsigned char> i(file_url->toStdString());
//        std::cout << "image correctly created (dimension : " << i.getH() << "*" << i.getW() << ")" << std::endl;
//         <<  << "*" << i.getW() << ")" << std::endl;
//        ui->InfotextBrowser->append(QString("image correctly created (dimension : ")+QString(i.getH())+"*"+QString(i.getW())+")");
        TreeType t=MaxTree;
        if (ui->connex4->isChecked())
            t = MinTree;

        int * parent_Tos = i.computeTOS_perso(t);
    //    int * parent_Tos = i.computeTreeOfShapes();
        std::cout << "... parent table computed" << std::endl;
        // nom du ToS
        std::ostringstream ToS_name;
        ToS_name << *i.get_filename() << "_ToS";
        Tree* ToS = new Tree (parent_Tos,(i.getH()+2)*(i.getW()+2),ToS_name.str());
        std::cout << ToS_name.str() << " created" << std::endl;
        i.add_edge();
        // version texte de l'arbre
    //    std::cout << *ToS << std::endl;
    //    std::cout << "écriture de l'arbre" << std::endl;

        // ajout de la proportion du noeud
        QString chaine;
        chaine.append("Proportion choisie : ");
        chaine.append(QString::number(ui->horizontalSlider->value()));
        std::cout << "proportion : " << ui->horizontalSlider->value() << std::endl;
        ui->InfoLabel->setText("Bonjour");
        i.writeTree_simpl(ToS,ui->horizontalSlider->value());
        std::cout << "... images created"<< std::endl;

        // ajout de la fonction permettant d'écrire l'arbre dans un fichier .dot
        std::ostringstream graphPath;
        graphPath << "../../Graph/" << *i.get_filename() <<".dot" ;
        initGraphviz(graphPath.str(),ToS_name.str());
        i.writeTreeInfo_graphviz(ToS,graphPath.str(),ui->horizontalSlider->value());
        i.writeTree_graphviz(ToS,graphPath.str(),ui->horizontalSlider->value());
        finishGraphviz(graphPath.str());

        std::ostringstream dotCmd ;
        std::ostringstream pngGraphPath;
        pngGraphPath << "../../Graph/" << *i.get_filename() <<".png" ;
        dotCmd << "dot -Tpng -o "<< pngGraphPath.str() << " " << graphPath.str() ;

    //    std::cout << dotCmd.str() << std::endl;

        system(dotCmd.str().c_str());


        std::cout << "... graph file done"<< std::endl;

        std::cout << "... over" << std::endl;
    }

    ui->InfoLabel->setText("Tree was created");

}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    QString s = QString::number(position);
    s += QString("‰");
    ui->NodeProportion->setText(s);
}
