//#include <libpng/png.h>
#include <iostream>

#include "Image.h"
#include "Span.h"
#include "ImageInterpolate.h"

#include "Node.h"
#include "Tree.h"

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


    // même image avec des 2 à la place des 1 qui devrait théoriquement conduire au même résultat ...

//    // 1 ère ligne -> 2 - 2 - 2 - 2 - 2 - 2
//    i.setPixel(0,0,5); i.setPixel(0,1,5); i.setPixel(0,2,5); i.setPixel(0,3,5); i.setPixel(0,4,5); i.setPixel(0,5,5);
//    // 2 ème ligne -> 2 - 0 - 0 - 3 - 3 - 2
//    i.setPixel(1,0,5); i.setPixel(1,1,1); i.setPixel(1,2,1); i.setPixel(1,3,9); i.setPixel(1,4,9); i.setPixel(1,5,5);
//    // 3 ème ligne -> 2 - 0 - 2 - 2 - 3 - 2
//    i.setPixel(2,0,5); i.setPixel(2,1,1); i.setPixel(2,2,5); i.setPixel(2,3,5); i.setPixel(2,4,9); i.setPixel(2,5,5);
//    // 4 ème ligne -> 2 - 0 - 0 - 3 - 3 - 2
//    i.setPixel(3,0,5); i.setPixel(3,1,1); i.setPixel(3,2,1); i.setPixel(3,3,9); i.setPixel(3,4,9); i.setPixel(3,5,5);
//    // 5 ème ligne -> 2 - 2 - 2 - 2 - 2 - 2
//    i.setPixel(4,0,5); i.setPixel(4,1,5); i.setPixel(4,2,5); i.setPixel(4,3,5); i.setPixel(4,4,5); i.setPixel(4,5,5);

            //      AUTRE EXEMPLE (ne pas prendre en compte lors de la lecture)
    // autre exemple d'image -> la même que celle de base mais en retirant la bordure avec les pixels ayant un niveau de gris à 1

//    Image<unsigned char> i(3,4);
//    i.setPixel(0,0,0); i.setPixel(0,1,0); i.setPixel(0,2,3); i.setPixel(0,3,3);
//    i.setPixel(1,0,0); i.setPixel(1,1,4); i.setPixel(1,2,4); i.setPixel(1,3,3);
//    i.setPixel(2,0,0); i.setPixel(2,1,0); i.setPixel(2,2,3); i.setPixel(2,3,3);


    int h(i.getH()),w(i.getW());

    std::cout << "test " << std::endl;

    std::cout << i << std::endl;
//    */

    /*

    // image tirée de l'article "effective component..."
    // ------------------------
    //
    //      Image utilisée surtout pour voir le résultat des calculs des max et min tree sur un exemple concret


    Image <unsigned char> i (2,5);

    // 1 ère ligne -> 3 - 3 - 1 - 4 - 2
    i.setPixel(0,0,3); i.setPixel(0,1,3); i.setPixel(0,2,1); i.setPixel(0,3,4); i.setPixel(0,4,2);
    // 2 ème ligne -> 4 - 1 - 2 - 3 - 1
    i.setPixel(1,0,4); i.setPixel(1,1,1); i.setPixel(1,2,2); i.setPixel(1,3,3); i.setPixel(1,4,1);

    std::cout << "\033[1;42m\t\tImage de base :\033[0m" << std::endl;

    std::cout << i << std::endl;

    int h(i.getH()),w(i.getW());

//    */

    //                      TESTS CRéTION DES MAX ET MIN-TREE


    int nbP = i.getH() * i.getW();



    //-> Min tree -> connexité 2n


    int* parent_minTree = i.computeMinTree();

    Tree*min_tree = new Tree(parent_minTree,nbP,std::string("MinTree"));

    std::cout << *min_tree << std::endl;

    // -> pour le max-tree -> connexité 3^n -1

    int* parent_maxTree = i.computeMaxTree();

    Tree*max_tree = new Tree(parent_maxTree,nbP,std::string("MaxTree"));

    std::cout << *max_tree << std::endl;


    //                      TESTS  TOS (avec la méthode de l'article et la méthode modifiée)



    int * parentTOS = i.computeTreeOfShapes();

    displayTable(parentTOS,h+2,w+2);

    int * parentTOS_perso = i.computeTOS_perso();

    displayTable(parentTOS_perso,h+2,w+2);

    // arbre des formes obtenu en utilisant la méthode modifiée de l'algorithme

    Tree* treeOfShapes = new Tree(parentTOS_perso,(h+2)*(w+2),std::string("Tree of Shapes"));

    std::cout << *treeOfShapes << std::endl;

    Image<unsigned char> i_edge(i);
    i_edge.add_edge();

    i_edge.afficheTree(treeOfShapes);

    i.write("test2.png");


    // test de la méthode writeTree sur le ToS obtenu en appliquand la méthode perso

    i_edge.writeTree(treeOfShapes);

    // test sur une image png complexe

//    Image<unsigned char> google("../../Images_test/g+.png");
//    std::cout << *(google.get_filename()) << std::endl;

//    finalToS("../../Images_test/g+.png");

//    finalToS("../../Images_test/test6.png");

    finalToS("../../Images_test/minus.png");

    // Problème avec le tableau parent semblerait-il, essayer de corriger cela

    return 0;
}

