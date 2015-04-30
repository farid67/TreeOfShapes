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

    int h(im.getH()),w(im.getW());// ligne inutile normalement car on fait appel au constructeur par copie de toutes manières


    d_1Faces_H = new Span<T> [h * (w+1)];
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

    // modification des dimensions de U en fonction de la set-valued-map


    this->setH(2*h +1);
    this->setW(2*w +1);

}

// destructeur
template <typename T>
ImageInterpolate<T>::~ImageInterpolate()
{
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

    int i,j,h ((im.getH()-1) / 2),w((im.getW()-1)/2);
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
            os << static_cast <int>(im.getPixels()[i*w+j]) << "   ";
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


// -> PROBLEME : lors de l'appel à l'opertor << sur un objet de type ImageInterpolate, le compilateur ne sait pas si l'objet est de
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
    // on repart avec les dimensions de la set-valued map, elles sont plus agréables à utilisées pour l'affichage des pixels
    int i,j,h ((this->getH()-1 )/2),w((this->getW()-1)/2);



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
            std::cout << "\033[1;31m" << static_cast <int>(this->getPixels()[i*w+j]) << "\033[0m   ";
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



// SORT procedure

template <typename T>
void ImageInterpolate<T>::sort(Image<T>* im, std::vector<int>* R, TreeType t)
{

    //                  INITIALISATIONS

    // modification des dimensions de im pour qu'elle est la même taille que U (dans notre cas U = this)
    im->setH(this->getH());
    im->setW(this->getW());

    T* new_pixels = new T[this->getH()*this->getW()];
    im->setPixels(new_pixels);

                                                        // création de q

    // q sera un tableau de 255 listes contenant des entiers (les offsets de l'image U)
    // 255 listes pour avoir une liste par niveau de gris
    std::list<int> * q = new std::list<int>[256];


                                                        // creation de deja_vu
    // nbp -> nombre d'element de l'image U
    int nbp = this->getH()*this->getW();
    bool* deja_vu = new bool[nbp];
    // + initialisation de tous les éléments du tableau à faux
    for (int i = 0; i < nbp; i++)
    {
        deja_vu[i] = false;
    }

    // création d'un tableau qui contient uniquement des intervalles avec les valeurs correspondantes à une lecture linéaire de U
    std::vector<Span<T> > *U = standardize();


    /*
    //                      AFFICHAGE du résultat de la fonction standardize sur une image interpolée

    // test sur la fonction standardize sur l'image interpolée
    typename std::vector<Span<T> >::iterator it ;

    int compteur =0;

    for (it = U->begin(); it != U->end() ;it++)
    {
        std::cout << *it << " ";
        compteur ++;
        if (compteur % this->getW() == 0)
        {
            std::cout << std::endl;
        }
    }

    // fin test affichage

    */

    int p_inf,h;
    T l;


    // p_inf correspond au premier point lors du parcours de l'image avec bordure
    // Largeur + 1 élément => coin supérieur gauche de l'image avec bordure
    p_inf = this->getW() + 1;
    // revient à faire PUSH[q[l_inf],p_inf]
    push(q,U->at(p_inf).getInfBounds(),p_inf);

    deja_vu[p_inf] = true;

    // grey level of p_inf
    T l_inf = U->at(p_inf).getInfBounds();

    l = l_inf;

//    int n;

    std::cout << "nombre de pixels à écrire " << U->size() << std::endl;
    int total = U->size();
    int compteur =0;
    int pourcentage = 0;
    std::cout << "0% ..." << std::endl;
    // estimation du temps
    while (!is_empty(q))
    {
//        std::cout << "size of q "<< q->size() << std::endl;
        h = priority_pop(q,&l);
        im->getPixels()[h] = l;
        R->push_back(h);
        compteur ++;
        if (compteur >= (total/100))
        {
            pourcentage++;
            std::cout << pourcentage <<"%" << std::endl;
            compteur = 0;
        }
        // pour afficher le pourcentage , on calcule

//        display_q(q);

        // pour tout n € N(h) tel que deja_vu[n] = faux
//        for (n = 0; n < nbp; n++)
//        {
//            if (!deja_vu[n] && isVoisin(n,h,this->getH(),this->getW(),t))
//            {
//                priority_push(q,n,U,l);
//                deja_vu[n] = true;
//            }
//        }

        // autre version de la boucle ci-dessus (pour améliorer la complexité)

//        std::cout << "version modif" << std::endl;
        std::list<int>* p_voisin = getVoisin(h,this->getH(),this->getW(),t); // on peut même faire un vector si on souhaite

        std::list<int>::iterator n;
//        std::cout << "voisins :";
        for (n = p_voisin->begin(); n != p_voisin->end();n++)
        {
//            std::cout << *n << " " ;
            if (!deja_vu[*n])
            {
                priority_push(q,*n,U,l);
                deja_vu[*n] = true;
            }
        }
//        std::cout << std::endl;

    }
//    std::cout << "100%" << std::endl;
}

// display_q -> fonction servant à avoir un aperçu du contenu de q
void display_q(std::list<int> *q )
{
    int i;
    for (i=0; i < 256; i ++)
    {
        if (!q[i].empty())
        {
            std::cout << "[" << i << "] : ";
            // affichage des valeurs contenue dans la liste q[i]
            typename std::list<int> ::iterator it;
            for (it = q[i].begin(); it!= q[i].end(); it++)
            {
                std::cout << *it << " -> ";
            }
            std::cout << std::endl;
        }
    }
}


//standardize -> prend U et renvoie un tableau linéaire contenant chaque case présent dans l'image de façon linéaire
template <typename T>
std::vector<Span<T> > *ImageInterpolate<T>::standardize()
{
//    int nbp = this->getH()*this->getW();
    std::vector<Span<T> > *tab = new std::vector<Span<T> > ;

    int i,j,h ((this->getH()-1 )/2),w((this->getW()-1)/2);

    for (i = 0 ; i < h; i++)
    {
        for (j= 0; j< w; j++)
        {
            tab->push_back(this->getD_0Face()[i*(w+1)+j]);
            tab->push_back(this->getD_1FaceV()[i*w+j]);
        }
        tab->push_back(this->getD_0Face()[i*(w+1)+w]);

        for (j= 0 ; j < w; j++)
        {
            tab->push_back(this->getD_1FaceH()[i*(w+1) + j]);
            tab->push_back(*(new Span<T>(this->getPixels()[i*w+j])));
        }

        tab->push_back(this->getD_1FaceH()[i*(w+1) + w]);
    }
    for (j= 0; j < w; j++)
    {
        tab->push_back(this->getD_0Face()[h * (w+1) + j ]);
        tab->push_back(this->getD_1FaceV()[h * w + j ]);
    }
    tab->push_back(this->getD_0Face()[h * (w+1) + w ]);

    return tab;
}

// Push procedure
template <typename T>
void push(std::list<int>* q ,T l,int p)
{
    // ajoute l'offset p à la position l du tableau de listes
    q[static_cast<int>(l)].push_back(p);
}


// is_empty procedure
bool is_empty (std::list<int>* q)
{
    int i;
    for (i = 0; i < 256; i ++)
    {
        if (!q[i].empty())
            return false;
    }
    return true;
}


// priority_push
template <typename T>
void priority_push(std::list<int>* q, int h, std::vector<Span<T> >* U, T l )
{
    T lower,upper,l_;
    lower = U->at(h).getInfBounds();
    upper = U->at(h).getSupBounds();

    if (static_cast<int>(lower) > static_cast<int>(l))
    {
        l_ = lower;
    }

    else if (static_cast<int>(upper) < static_cast<int>(l))
    {
        l_ = upper;
    }
    else
        l_ = l;

//    std::cout << "la fonction priority_push demande de faire un push pour le niveau de gris " << static_cast<int>(l_) << " avec l'offset : " << h << std::endl;

    push(q,l_,h);
}

// priority_pop
template <typename T>
int priority_pop (std::list<int>* q,T* l)
{
    int grey_level = static_cast<int>(*l);
//    std::cout << "\t\tniveau de gris en entrée " << grey_level << std::endl ;
    if (q[grey_level].empty())
    {
        bool found = false;
        int compteur = 1;
        // check l sup
        while (!found)
        {
            // going up
            if (grey_level + compteur < 256)
            {
                if (!q[grey_level + compteur].empty())
                {
                    *l = static_cast<T>(grey_level+compteur);
                    int return_val = q[grey_level + compteur].front();
                    q[grey_level + compteur].pop_front();
                    return return_val;
                }
            }
            // going down
            if(grey_level -compteur >= 0)
            {
                if (!q[grey_level-compteur].empty())
                {
                    *l = static_cast<T>(grey_level-compteur);
                    int return_val = q[grey_level - compteur].front();
                    q[grey_level - compteur].pop_front();
                    return return_val;
                }
            }
            //increasing compteur
            compteur ++;
        }
    }

    // cas non vide

    int return_val = q[grey_level].front();
    q[grey_level].pop_front();
    return return_val;
}

// UN_INTERPOLATE procedure pour le tableau R

template <typename T>
int *ImageInterpolate<T>::R_un_interpolate(int *table, int* corresponding_table)
{

    // si on considère que l'image de base est l'image à laquelle on a ajouté une bordure, l'équation est la suivante:
    // new_h (image interpolate =  4 * h (image de base) -1

    int h = (this->getH() +1) / 4;
    int w = (this->getW() +1) / 4;

    int *return_tab = new int[h*w];

    int i,j;

    int current_offset(0),current_tab_offset(0);

    for (i= 0;i < this->getH() ;i ++)
    {
        for (j= 0;j < this->getW();j++)
        {

                if (corresponding_table[table[current_offset]] != -1)
                {
                    return_tab[current_tab_offset]=corresponding_table[table[current_offset]];
                    current_tab_offset ++;
                }
                current_offset++;
        }
    }
    return return_tab;

}

template <typename T>
int* ImageInterpolate<T>::parent_un_interpolate(int *table, int *corresponding_table)
{
    int h = (this->getH() +1) / 4;
    int w = (this->getW() +1) / 4;

//    std::cout << "dimension du tableau " << h << "*"<< w << std::endl;

    int *return_tab = new int[h*w];

    int i,j;

    int current_offset(0),current_tab_offset(0);

    for (i= 0;i < this->getH() ;i ++)
    {
        for (j= 0;j < this->getW();j++)
        {
                if (corresponding_table[current_offset] != -1)
                {
                    return_tab[current_tab_offset]= corresponding_table[table[current_offset]];
                    current_tab_offset ++;
                }
                current_offset++;
        }
    }
    return &return_tab[0];
}


// fonction à utiliser pour récupérer une correspondance avec l'image de base à laquelle on a ajoutée une bordure

template <typename T>
int* ImageInterpolate<T>::corresponding()
{
    int* corresponding_tab = new int [this->getH() * this->getW()];

    int i,j,compteur(0),compteur_true_element(0);


    // init all elements of the tab to -1
    for (i = 0;i < this->getH(); i++)
    {
        for (j = 0; j< this->getW(); j++)
        {
            corresponding_tab[compteur]= -1;
            if ((i-1)%4  == 0 && (j-1)%4 == 0)// on ne récupère que les éléments issus de l'image de départ à laquelle on a ajouté la bordure
            {
                corresponding_tab[compteur] = compteur_true_element;
                compteur_true_element++;
            }
            compteur ++;
        }
    }

    return corresponding_tab;
}


#endif // IMAGEINTERPOLATE_HPP
