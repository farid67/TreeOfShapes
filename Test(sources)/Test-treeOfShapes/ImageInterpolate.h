#ifndef IMAGEINTERPOLATE_H
#define IMAGEINTERPOLATE_H


#include "Image.h"
#include "Span.h"

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


    void displayImage ();

};

template <typename T>
std::ostream& operator << (std::ostream& os,const ImageInterpolate<T>& im );

#include "ImageInterpolate.hpp"

#endif // IMAGEINTERPOLATE_H
