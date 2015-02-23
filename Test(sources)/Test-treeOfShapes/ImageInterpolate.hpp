#ifndef IMAGEINTERPOLATE_HPP
#define IMAGEINTERPOLATE_HPP

#include "ImageInterpolate.h"

template <typename T>
ImageInterpolate <T>::ImageInterpolate():Image<T>()
{
}



// dans cette fonction REDUIRE les appels à im.getH() et im.getW() en mettant les 2 valeurs dans des variables
template <typename T>
ImageInterpolate<T>::ImageInterpolate(const Image<T> &im):Image<T>(im)
{
    // création d'un tableau de span pour les d-1 faces
    //  On commence par créer les d-1 faces car elles sont créées à partir des d-2 faces, donc de la set-valued map

    // on part du principe qu'on a donnée l'image de base (avec la bordure) comme paramètre,
        // il faut donc commencer par lui effectuer la set-valued map


    // ligne inutile si on passe la set-valued map au constructeur
//    this->set_valued();

    int h(im.getH()),w(im.getW());


    d_1Faces_H = new Span<T> [h * w+1];
    d_1Faces_V = new Span<T> [(h+1) * w];

    // affichage -> test
    /*
    int i, j ;
    for (i = 0; i < this->getH();i++)
    {
        for (j = 0; j < this->getW(); j ++)
        {
            std::cout << static_cast<int>(this->getPixel(i,j))<< " ";
        }
        std::cout << std::endl;
    }
    */


    // construction du tableau d-1 faces à partir des valeur contenues dans le tableau des pixels

    // -> En réalité il y aura 2 tableau pour les d-1 faces un horizontal et un vertical


    // construction du tableau d-1Faces_H

    int i,j;

    for (i = 0 ; i < h;i++)
    {
        for (j = 0 ; j< w +1 ; j++)
        {
            if (j == 0 )
                d_1Faces_H[ i * (w+1) + j ].setSpan(this->getPixel(i,j));
            else if (j == w )
                d_1Faces_H[ i * (w+1) + j ].setSpan(this->getPixel(i,j-1));
            else
                d_1Faces_H[ i * (w+1) + j ].setSpan(this->getPixel(i,j-1),this->getPixel(i,j));
        }
    }

    // d_1Faces_V

    for (i = 0; i < h+1 ; i++)
    {
        for (j= 0 ; j < w; j++)
        {
            if (i==0)
                d_1Faces_V[ i * (w) + j].setSpan(this->getPixel(i,j));
            else if (i == h)
                d_1Faces_V[ i * (w) + j].setSpan(this->getPixel(i-1,j));
            else
                d_1Faces_V[ i * (w) + j].setSpan(this->getPixel(i-1,j),this->getPixel(i,j));
        }
    }

    
    


    // construction du tableau des d0Faces de tailles h+1 * l+1

    d_0Faces = new Span<T> [(h +1) * (w +1)];

    // remplissage du tableau

    for (i = 0; i < h +1; i ++)
    {
        for (j = 0 ; j < w +1 ; j++)
        {
            if (i == 0) //bord haut
            {
                if (j == 0)//coin h-g
                    d_0Faces[i*(w+1) + j ].setSpan(d_1Faces_H[i * (w+1) + j ] , d_1Faces_V[i*w + j]);
                else if (j == w)// coin h-d
                    d_0Faces[i*(w+1) + j ].setSpan(d_1Faces_H[i * (w+1) + j ] , d_1Faces_V[i*w + (j-1)]);
                else //bord haut (coins exclus)
                    d_0Faces[i*(w+1) + j ].setSpan(d_1Faces_H[i * (w+1) + j ] , d_1Faces_V[i*w + j] , d_1Faces_V[i*w + (j-1)]);
            }

            else if (i == h) // bord bas
            {

                if (j == 0)// coin b-g
                    d_0Faces[i*(w+1) + j ].setSpan(d_1Faces_H[(i-1) * (w+1) + j ] , d_1Faces_V[i*w + j]);
                else if (j == w) // coin b-d
                    d_0Faces[i*(w+1) + j ].setSpan(d_1Faces_H[(i-1) * (w+1) + j ] , d_1Faces_V[i*w + (j-1)]);
                else
                    d_0Faces[i*(w+1) + j ].setSpan(d_1Faces_H[(i-1) * (w+1) + j ] , d_1Faces_V[i*w + (j-1)] , d_1Faces_V[i*w + j]);
            }
            else
            {
                if (j == 0) // bord gauche (coins exclus)
                    d_0Faces[i*(w+1) + j ].setSpan(d_1Faces_H[(i-1) * (w+1) + j ] , d_1Faces_H[i*(w+1) + j] , d_1Faces_V[i*w + j]);
                else if (j  == w) // bord droit (coins exclus)
                    d_0Faces[i*(w+1) + j ].setSpan(d_1Faces_H[(i-1) * (w+1) + j ] , d_1Faces_H[i*(w+1) + j] , d_1Faces_V[i*w + (j-1)]);

                else //cas général
                    d_0Faces[i*(w+1) + j ].setSpan(d_1Faces_H[(i-1) * (w+1) + j ] , d_1Faces_H[i*(w+1) + j] , d_1Faces_V[i*w + (j-1)], d_1Faces_V[i*w + j]);
            }
        }
    }


    //affichage d-1 Faces + d-2Faces (les pixels) + d-0Faces
}

// accesseurs
template <typename T>
Span<T>* ImageInterpolate<T>::getD_0Face()
{
    return d_0Faces;
}

template <typename T>
Span<T>* ImageInterpolate<T>::getD_1FaceH()
{
    return d_1Faces_H;
}

template <typename T>
Span<T>* ImageInterpolate<T>::getD_1FaceV()
{
    return d_1Faces_V;
}


// méthode d'affichage -> + gestion des couleur pour y voir quelque chose
template <typename T>
std::ostream operator << (std::ostream& os, const ImageInterpolate<T>& im)
{

    int i,j,h (im.getH()),w(im.getW());
    for (i = 0 ; i < h; i++)
    {
        // afficher la j-ème ligne du tableau d_1Faces_V
        for (j= 0; j< w; j++)
        {
            os << im.getD_0Face()[i*(w+1)+j] << " " ;
            os << im.getD_1FaceV()[i*w+j] << " " ;
        }
        os << im.getD_0Face()[i*(w+1)+w] << " " << std::endl;

        // afficher en alternance d_1Faces_H et le contenu du tableau des pixels
        for (j= 0 ; j < w; j++)
        {
            os << im.getD_1FaceH()[i*(w+1) + j] << "   ";
            os << static_cast <int>(im.getPixel(i,j)) << "   ";
        }

        // afficher la ligne du bord de droite
        os << im.getD_1FaceH()[i*(w+1) + w] << " " << std::endl;
    }
    // afficher la dernière ligne
    for (j= 0; j < w; j++)
    {
        os << im.getD_0Face()[h * (w+1) + j ] << " ";
        os << im.getD_1FaceV()[h * w + j ] << " ";
    }
    os << im.getD_0Face()[h * (w+1) + w ] << " " << std::endl;

    return os;
}


// -> PROB : lors de l'appel à l'opertor << sur un objet de type ImageInterpolate, le compilateur ne sait pas si l'objet est de
// type image ou de type ImageInterpolate ?
// -> définition d'une nouvelle fonction display pour le moment


void displayLegend()
{
    std::cout << "\t\tLegende pour l'affichage des imageInterpolate" << std::endl;
    std::cout << "\033[1;34m d-0 Faces \033[0m" << std::endl;
    std::cout << "\033[1;32m d-1 Faces \033[0m" << std::endl;
    std::cout << "\033[1;31m d-2 Faces \033[0m" << std::endl;
    std::cout << std::endl;
}

template <typename T>
void ImageInterpolate<T>::displayImage()
{
    int i,j,h (this->getH()),w(this->getW());
    for (i = 0 ; i < h; i++)
    {
        // afficher la j-ème ligne du tableau d_1Faces_V
        for (j= 0; j< w; j++)
        {
            std::cout << "\033[1;34m" << this->getD_0Face()[i*(w+1)+j] << "\033[0m " ;
            std::cout << "\033[1;32m" << this->getD_1FaceV()[i*w+j] << "\033[0m " ;
        }
        std::cout << "\033[1;34m" << this->getD_0Face()[i*(w+1)+w] << "\033[0m " << std::endl;

        // afficher en alternance d_1Faces_H et le contenu du tableau des pixels
        for (j= 0 ; j < w; j++)
        {
            std::cout << "\033[1;32m" << this->getD_1FaceH()[i*(w+1) + j] << "\033[0m   ";
            std::cout << "\033[1;31m" << static_cast <int>(this->getPixel(i,j)) << "\033[0m   ";
        }

        // afficher la ligne du bord de droite
        std::cout << "\033[1;32m" << this->getD_1FaceH()[i*(w+1) + w] << "\033[0m " << std::endl;
    }
    // afficher la dernière ligne
    for (j= 0; j < w; j++)
    {
        std::cout << "\033[1;34m" << this->getD_0Face()[h * (w+1) + j ] << "\033[0m ";
        std::cout << "\033[1;32m" << this->getD_1FaceV()[h * w + j ] << "\033[0m ";
    }
    std::cout << "\033[1;34m" << this->getD_0Face()[h * (w+1) + w ] << "\033[0m " << std::endl;
}

#endif // IMAGEINTERPOLATE_HPP
