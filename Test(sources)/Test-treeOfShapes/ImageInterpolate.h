#ifndef IMAGEINTERPOLATE_H
#define IMAGEINTERPOLATE_H


#include "Image.h"
#include "Span.h"
#include "vector"
#include "list"

template <typename T>
class ImageInterpolate:public Image<T>
{
private:
    Span<T>* d_0Faces;
    Span<T>* d_1Faces_H; // horizontal
    Span<T>* d_1Faces_V; // vertical
public:
    ImageInterpolate();
    // le seul constructeur qui ait du sens ici et celui qui prend en argument une image et qui créer une image interpolate
    ImageInterpolate( const Image<T>& i);


    // accesseurs
    Span<T>* getD_0Face();
    Span<T>* getD_1FaceH();
    Span<T>* getD_1FaceV();

    Span<T> getElement(int h);


    // standardize -> tableau linéaire de Span correspondant à un parcours linéaire de U (this)
    std::vector<Span<T> > *standardize();

    void displayImage ();

    // SORT procédure, prend en paramètre une image im qui sera le u(indice b) de l'article
    //-> pour ne pas avoir à renvoyer une structure qui contienne une image et un tableau
    void sort(Image<T> *im, std::vector<int> *R );

    int * un_interpolate (int * table);

};

template <typename T>
std::ostream& operator << (std::ostream& os,const ImageInterpolate<T>& im );

template <typename T>
void push(std::list<int>* q ,T l,int p);


bool is_empty (std::list<int>* q);

template <typename T>
int priority_pop (std::list<int>* q,T* l);

template <typename T>
void priority_push(std::list<int>* q, int h, std::vector<Span<T> > *U,T l );


#include "ImageInterpolate.hpp"

#endif // IMAGEINTERPOLATE_H
