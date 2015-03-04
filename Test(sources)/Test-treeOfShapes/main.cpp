#include <iostream>

#include "Image.h"
#include "Span.h"
#include "ImageInterpolate.h"


int main()
{
//    /*
    // Image tirée de l'article de base : "A quasi linear algorithm to compute the tree of shapes.."
    Image<unsigned char> i(5,6);

    std::cout << "image de taille " << i.getH() << "*" << i.getW() << std::endl;


    // 1 ère ligne -> 1 - 1 - 1 - 1 - 1 - 1
    i.setPixel(0,0,1); i.setPixel(0,1,1); i.setPixel(0,2,1); i.setPixel(0,3,1); i.setPixel(0,4,1); i.setPixel(0,5,1);
    // 2 ème ligne -> 1 - 0 - 0 - 3 - 3 - 1
    i.setPixel(1,0,1); i.setPixel(1,1,0); i.setPixel(1,2,0); i.setPixel(1,3,3); i.setPixel(1,4,3); i.setPixel(1,5,1);
    // 3 ème ligne -> 1 - 0 - 1 - 1 - 3 - 1
    i.setPixel(2,0,1); i.setPixel(2,1,0); i.setPixel(2,2,1); i.setPixel(2,3,1); i.setPixel(2,4,3); i.setPixel(2,5,1);
    // 4 ème ligne -> 1 - 0 - 0 - 3 - 3 - 1
    i.setPixel(3,0,1); i.setPixel(3,1,0); i.setPixel(3,2,0); i.setPixel(3,3,3); i.setPixel(3,4,3); i.setPixel(3,5,1);
    // 5 ème ligne -> 1 - 1 - 1 - 1 - 1 - 1
    i.setPixel(4,0,1); i.setPixel(4,1,1); i.setPixel(4,2,1); i.setPixel(4,3,1); i.setPixel(4,4,1); i.setPixel(4,5,1);

    int h(i.getH()),w(i.getW());

    std::cout << "test " << std::endl;

    std::cout << i << std::endl;
//    */

    /*

    // image tirer de l'article "effective component..."
    // ------------------------
    //
    //


    Image <unsigned char> i (2,5);

    // 1 ère ligne -> 3 - 3 - 1 - 4 - 2
    i.setPixel(0,0,3); i.setPixel(0,1,3); i.setPixel(0,2,1); i.setPixel(0,3,4); i.setPixel(0,4,2);
    // 2 ème ligne -> 4 - 1 - 2 - 3 - 1
    i.setPixel(1,0,4); i.setPixel(1,1,1); i.setPixel(1,2,2); i.setPixel(1,3,3); i.setPixel(1,4,1);

    std::cout << "\033[1;42m\t\tImage de base :\033[0m" << std::endl;

    std::cout << i << std::endl;

    int h(i.getH()),w(i.getW());

    */

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
    // dans ce cas, il faudra faire les opérations add_edge() et set_valued() dans le constructeur

    // on passe l'image de base dont on a déjà créé la version set-valued

    ImageInterpolate<unsigned char> u(i);

    displayLegend();

    std::cout << "dimension de U " << u.getH() << "*" << u.getW()<< std::endl;

    // vérifier que l'image obtenue après interpolation correspond bien à ce qui est attendu

    u.displayImage();



    Image<unsigned char> test;

    std::vector<int> r;


    // utilisation de la procédure Sort en passant en paramètre une image vide (dont on modifiera les dimensions pour qu'elle est les
    // même dimension que l'image interpolée ainsi qu'un tableau R qui contiendra les éléments suivant la relation de parenté que l'on
    // souhaite mettre en place

    u.sort(&test,&r);

    // affichage
    std::cout << "affichage de R:" << std::endl;

    std::vector<int>::iterator it;
    int compteur(0);
    for (it = r.begin();it != r.end(); it++)
    {
        std::cout << *it << " ";
        compteur ++;
        if (compteur == test.getW())
        {
            compteur =0;
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;

    std::cout << "affichage de U(indice b) -> retour de la fonction sort" <<std::endl;

    std::cout << test << std::endl;

    //  application de la fonction union_find sur R qui est un des retours de la fonction sort
    int nbp = test.getH() * test.getW();

    // pour ne pas avoir de problème de type, on doit passer en paramètre à la fonction union_find un tableau d'entier,
    // or R est dans notre cas un vector<int>, on passe alors le pointeur vers le premier élément du vector ce qui donnera un int*
    int * parent = union_find(&r[0],nbp);

    /*
    std::cout << "affichage du tableau parent : " << std::endl;

    int j;
    for (j=0; j < nbp; j++)
    {
        if (j%test.getW() == 0)
        {
            std::cout << std::endl;
        }
        std::cout << parent[j] << " ";
    }
    std::cout << std::endl;
    */

    // canonicalize_tree

    canonize_tree(parent,nbp,test);

    /*

    std::cout << "affichage du tableau parent (canonicalize version): " << std::endl;

    for (j=0; j < nbp; j++)
    {
        if (j%test.getW() == 0)
        {
            std::cout << std::endl;
        }
        std::cout << parent[j] << " ";
    }
    std::cout << std::endl;

    */


    // un_interpolate(R,parent)
    // -> revient à récupérer l'application inverse de l'interpolation sur R et celle sur parent

    int* R_un_interpolate  = u.un_interpolate(&r[0]);

    int* parent_un_interpolate = u.un_interpolate(parent);

    // affichage des 2 tableaux en fonctions des dimensions de l'image de base -> contenues ici dans h et w

    int x,y;

    std::cout << std::endl << "R final " << std::endl;

    for(x = 0; x < h; x++)
    {
        for (y = 0; y < w; y++)
        {
            std::cout << R_un_interpolate[x*w + y] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << "parent final"<< std::endl;

    for(x = 0; x < h; x++)
    {
        for (y = 0; y < w; y++)
        {
            std::cout << parent_un_interpolate[x*w + y] << " ";
        }
        std::cout << std::endl;
    }


    return 0;
}

