#ifndef IMAGEINTERPOLATE_HPP
#define IMAGEINTERPOLATE_HPP

#include "ImageInterpolate.h"

template <typename T>
ImageInterpolate <T>::ImageInterpolate():Image<T>()
{
}


template <typename T>
ImageInterpolate<T>::ImageInterpolate(const Image<T> &im):Image<T>(im)
{
    // création d'un tableau de span pour les d-1 faces
    //  On commence par créer les d-1 faces car elles sont créées à partir des d-2 faces, donc de la set-valued map

    // on part du principe qu'on a donnée l'image de base (avec la bordure) comme paramètre,
        // il faut donc commencer par lui effectuer la set-valued map


    // ligne inutile si on passe la set-valued map au constructeur
//    this->set_valued();


    d_1Faces_H = new Span<T> [im.getH() * (im.getW()+1)];
    d_1Faces_V = new Span<T> [(im.getH()+1) * im.getW()];

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

    for (i = 0 ; i < im.getH();i++)
    {
        for (j = 0 ; j< im.getW() +1 ; j++)
        {
            if (j == 0 )
                d_1Faces_H[ i * (im.getW()+1) + j ].setSpan(this->getPixel(i,j));
            else if (j == im.getW()+1 )
                d_1Faces_H[ i * (im.getW()+1) + j ].setSpan(this->getPixel(i,j-1));
            else
                d_1Faces_H[ i * (im.getW()+1) + j ].setSpan(this->getPixel(i,j-1),this->getPixel(i,j));
        }
    }

    // d_1Faces_V

    for (i = 0; i < im.getH()+1 ; i++)
    {
        for (j= 0 ; j < im.getW(); j++)
        {
            if (i==0)
                d_1Faces_V[ i * (im.getW()) + j].setSpan(this->getPixel(i,j));
            else if (i == im.getH()+1)
                d_1Faces_V[ i * (im.getW()) + j].setSpan(this->getPixel(i-1,j));
            else
                d_1Faces_V[ i * (im.getW()) + j].setSpan(this->getPixel(i-1,j),this->getPixel(i,j));
        }
    }

    
    

    //affichage d-1 Faces + d-2Faces (les pixels)

    
    for (i = 0 ; i < im.getH(); i++)
    {
        for (j= 0; j< im.getW(); j++)
        {
            
        }
    }





}


#endif // IMAGEINTERPOLATE_HPP
