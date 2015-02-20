#ifndef IMAGE_H
#define IMAGE_H

#include "iostream"


template <typename T>
class Image
{
private:

    T* m_pixels; // un tableau sera un tableau de pixels
    int m_h; // height
    int m_w; // width
public:
    Image();

    Image (int height, int width);
    // constructeur par copie -> utile pour créer les images de type U (interpolate)

    Image (const Image<T>& im);

    ~Image();

    T operator[](int i); // modificateurs
    T& operator [] (int i) const; // accesseurs

    T& getPixel(int x, int y ) const;

    void setPixel(int x, int y , T val);

    int getH() const;
    int getW() const;

    int* sortGrayLevel(); // tri les pixels en fonction de leur niveau de gris


    unsigned char median_edge_value();// retourne la valeur de niveau de gris médiane sur la bordure de l'image

    void add_edge (); // fonction qui ajoute à l'image courante une bordure avec une valeur égale à la médiane des valeurs présentent sur la bordure interne

    void set_valued (); // fonction prennant l'image de base et la complétant en ajoutant les lignes et les colonnes nécessaire pour avoir la set-valued map

};

template <typename T>
std::ostream& operator << (std::ostream& os,const Image<T>& i );

int* union_find (int* R , int nbPixels);    // paramètre -> le tableau trié en fonction de ce qu'on veut ->
                                            // pour le max_tree et le min-tree, le tri sera fait en fonction du niveau de gris

int find_root(int* zpar, int n);

// fonction renvoyant le tableau passant en paramètre dans l'ordre inverse (tab_out [0] = tab_in[N-1]...)
int* reverse_order (int* tab_in, int nb_elem);

// fonction pour avoir un arbre avec un seul représentant par noeud
template <typename T>
void canonize_tree(int * parent, int nb_elem,const Image <T>& i);


#include "Image.hpp"

#endif // IMAGE_H
