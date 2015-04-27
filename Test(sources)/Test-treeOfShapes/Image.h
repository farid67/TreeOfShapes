#ifndef IMAGE_H
#define IMAGE_H

#include "iostream"
#include "Tree.h"
#include "sstream"


#include <png++/png.hpp>
#include <png++/image.hpp>
#include <png++/gray_pixel.hpp>
#include <png++/end_info.hpp> // pour la destruction ?
//#include "png.h"


enum TreeType {MinTree, MaxTree};


template <typename T>
class Image
{
private:

    T* m_pixels; // un tableau sera un tableau de pixels
    int m_h; // height
    int m_w; // width

    std::string* m_filename; // dans le cas où l'image est créée à partir d'un fichier

public:
    Image();

    Image (int height, int width);
    // constructeur par copie -> utile pour créer les images de type U (interpolate)

    Image (const Image<T>& im);

    // ajout constructeur qui construit une image à partir du fichier png

    Image(const std::string& filename);

    ~Image();

    T operator[](int i); // modificateurs
    T& operator [] (int i) const; // accesseurs

    T* getPixels();
    void setPixels(T* t);


    T& getPixel(int x, int y ) const;

    void setPixel(int x, int y , T val);

    int getH() const;
    int getW() const;

    void setH(int H);
    void setW(int w);

    std::string *get_filename() const;

    void set_filename(const std::string& name);

    int* sortGrayLevel(); // tri les pixels en fonction de leur niveau de gris


    T median_edge_value();// retourne la valeur de niveau de gris médiane sur la bordure de l'image

    void add_edge (); // fonction qui ajoute à l'image courante une bordure avec une valeur égale à la médiane des valeurs présentent sur la bordure interne

    void set_valued (); // fonction prennant l'image de base et la complétant en ajoutant les lignes et les colonnes nécessaire pour avoir la set-valued map

    // on fait également une version de set_valued qui renvoie une image et ne modifie pas l'image courante
    // cf fonction en-dehors de la classe

    int* computeMinTree();// fonction globale calculant le min tree de l'image courante

    int* computeMaxTree();

    void afficheNode(Node* n);// affiche les différentes composantes connexes de l'image

    void afficheTree(Tree* t);// affiche toutes les composantes sur l'image avec les liens de parenté

    void writeNode(Node* n); // même fonction que pour AfficheNode, mais on écrit le contenu du noeud dans une image

    void writeTree(Tree* t); // pareil que pour writeNode mais sur un arbre entier

    int* computeTreeOfShapes();// fonction qui est censé calculer l'arbre de parenté de l'image courante en suivant l'agorithme de l'article

    int* computeTOS_perso(); // fonction qui compute le TOS mais en modifiant l'ordre des étapes de l'algorithme

    void write (const std::string& filename);


};

// version finale (en utilisant la version perso de compute ToS)
void finalToS(const std::string &filename);

template <typename T>
std::ostream& operator << (std::ostream& os,const Image<T>& i );

int* union_find (const int *R , int h, int w, TreeType t);    // paramètre -> le tableau trié en fonction de ce qu'on veut ->
                                                        // pour le max_tree et le min-tree, le tri sera fait en fonction du niveau de gris

bool isVoisin(int n, int p, int h, int w, TreeType t);

int find_root(int* zpar, int n);

// fonction renvoyant le tableau passant en paramètre dans l'ordre inverse (tab_out [0] = tab_in[N-1]...)
int* reverse_order (int* tab_in, int nb_elem);

// fonction pour avoir un arbre avec un seul représentant par noeud
template <typename T>
void canonize_tree(int * parent, int nb_elem,const Image <T>& i, int * r);

template <typename T>
Image<T>* set_valuedMap(const Image<T>& i);


void displayTable (int* r , int height,int width);


#include "Image.hpp"

#endif // IMAGE_H
