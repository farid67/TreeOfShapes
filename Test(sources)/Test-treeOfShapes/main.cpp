#include <iostream>

#include "Image.h"
#include "Span.h"
#include "ImageInterpolate.h"


int main()
{
/*
    Image<unsigned char> i(5,6);

    std::cout << "image de taille " << i.getH() << "*" << i.getW() << std::endl;


    // 1 ère ligne -> 1 - 1 - 1 - 1 - 1 - 1
    i.setPixel(0,0,1); i.setPixel(0,1,1); i.setPixel(0,2,1); i.setPixel(0,3,1); i.setPixel(0,4,1); i.setPixel(0,5,1);
    // 2 ème ligne -> 1 - 0 - 0 - 3 - 3 - 1
    i.setPixel(1,0,1); i.setPixel(1,1,0); i.setPixel(1,2,0); i.setPixel(1,3,3); i.setPixel(1,4,3); i.setPixel(1,5,1);
    // 3 ème ligne -> 1 - 0 - 1 - 1 - 0 - 1
    i.setPixel(2,0,1); i.setPixel(2,1,0); i.setPixel(2,2,1); i.setPixel(2,3,1); i.setPixel(2,4,0); i.setPixel(2,5,1);
    // 4 ème ligne -> 1 - 0 - 0 - 3 - 3 - 1
    i.setPixel(3,0,1); i.setPixel(3,1,0); i.setPixel(3,2,0); i.setPixel(3,3,3); i.setPixel(3,4,3); i.setPixel(3,5,1);
    // 5 ème ligne -> 1 - 1 - 1 - 1 - 1 - 1
    i.setPixel(4,0,1); i.setPixel(4,1,1); i.setPixel(4,2,1); i.setPixel(4,3,1); i.setPixel(4,4,1); i.setPixel(4,5,1);

    std::cout << "test " << std::endl;

    std::cout << i << std::endl;
*/

    // image tirer de l'article "effective component..."
    // ------------------------
    //
    //


    Image <unsigned char> i (2,5);

    // 1 ère ligne -> 3 - 3 - 1 - 4 - 2
    i.setPixel(0,0,3); i.setPixel(0,1,3); i.setPixel(0,2,1); i.setPixel(0,3,4); i.setPixel(0,4,2);
    // 2 ème ligne -> 4 - 1 - 2 - 3 - 1
    i.setPixel(1,0,4); i.setPixel(1,1,1); i.setPixel(1,2,2); i.setPixel(1,3,3); i.setPixel(1,4,1);


    //coloration terminal -> \033 puis 2 entier après un crochet ouvrant : généralement le premier sera 1 et le second la couleur puis m

    std::cout << "\033[1;42m\t\tImage de base :\033[0m" << std::endl;

    std::cout << i << std::endl;

    //                      TESTS CRéTION DES MAX ET MIN-TREE

    /*
    int* r = i.sortGrayLevel();

    // tri croissant sur le niveau de gris, si on donne ce tableau en paramètre de la fonction union_find, on aura en sortie le min-tree
    // -> pour avoir le max_tree on doit faire un reverse_order sur ce tableau

    int nbP = i.getH() * i.getW();

//    /* -> pour le min-tree ( ne semble pas fonctionner correctement
//     *
//     *

    // Fonctionne étrangement -> algorithme que j'ai déroulé à la main et qui donne le même resultat lors de l'execution :
    // à savoir : les éléments sont uniquement chainés en fonction de leur niveau de gris ( a -> b -> c...)
    int *r_reverse = reverse_order(r,nbP);
    for (int i = 0; i < nbP; i++)
    {
        std::cout << r_reverse[i] << " ";
    }

    std::cout << std::endl;


    int* parent =  union_find(r_reverse,nbP);


    for (int i = 0; i < nbP; i++)
    {
        std::cout << parent[i] << " ";
    }
    std::cout << std::endl;

//    */

    /* -> pour le max-tree -> semble fonctionner correctement
     *
     *
    for (int i = 0; i < nbP; i++)
    {
        std::cout << r[i] << " ";
    }

    std::cout << std::endl;
//    std::cout << std::endl;


    int * parent = union_find(r,nbP);

    canonize_tree(parent,nbP,i);

    for (int i = 0; i < nbP; i++)
    {
        std::cout << parent[i] << " ";
    }
    std::cout << std::endl;

//    */


    //                      TEST INTERPOLATIONs

    // test ajout d'une bordure -> fonctionnel

//    /*
    i.add_edge();

    std::cout << "\033[1;32m Image avec bordure : \033[0m" << std::endl;

    std::cout << i << std::endl;

//    */

    // test set-valued map

    std::cout << "Construction de la \033[1;35mset-valued map\033[0m à partir de l'image ayant des bordures" <<std::endl;

    i.set_valued();

    std::cout << i << std::endl;

    // Attention -> pour la version finale on pourra avoir envie de passer l'image de base en paramètre au constructeur de ImageInterpolate
    // dans ce cas, il faudra faire l'opération i.set_valued() dans le constructeur

    // on passe l'image de base dont on a déjà créé la version set-valued

    ImageInterpolate<unsigned char> u(i);

    displayLegend();

    std::cout << "dimension de U " << u.getH() << "*" << u.getW()<< std::endl;

    u.displayImage();

    Image<unsigned char> test;

    std::vector<int> r;

    u.sort(&test,&r);


    // affichage
    std::cout << "affichage de R:" << std::endl;

    std::vector<int>::iterator it;
    for (it = r.begin();it != r.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << test << std::endl;

    return 0;
}

