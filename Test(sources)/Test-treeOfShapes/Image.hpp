#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "ImageInterpolate.h"
#include "cassert"
#include "Image.h"
#include "math.h"
#include "algorithm"

template <typename T>
Image<T>::Image():m_pixels(NULL),m_h(0),m_w(0)
{

}

template <typename T>
Image<T>::~Image()
{
    if (m_pixels!=NULL)
    {
        delete[]m_pixels;
    }
}


// constructeur par copie
template <typename T>
Image<T>::Image(const Image<T> &im):m_h(im.getH()),m_w(im.getW())
{
    m_pixels = new T [m_h *m_w];
    int i, j;
    for (i = 0; i < m_h; i++)
    {
        for (j= 0; j< m_w; j++)
        {
            m_pixels[i * m_w  + j ] = im.getPixel(i,j);
        }
    }
}


template <typename T>
Image<T>::Image(int height, int width)
{
    m_pixels = new T[height*width];

    m_h = height;
    m_w = width;
}


template <typename T>
int Image<T>::getH() const
{
    return m_h;
}

template <typename T>
int Image<T>::getW() const
{
    return m_w;
}

// modificateurs

template <typename T>
void Image<T>::setH(int h)
{
    m_h = h;
}

template <typename T>
void Image<T>::setW(int w)
{
    m_w = w;
}

template <typename T>
T Image <T>::operator [](int i)
{
    assert (i < getH()* getW());
    return m_pixels[i];
}

template <typename T>
T& Image<T>::operator [](int i) const
{
    assert(i < getW()* getH());
    return m_pixels[ i];
}

template <typename T>
T& Image<T>::getPixel(int x, int y )const
{
    // x -> ligne, y -> colonne
    return m_pixels[x*getW() + y];
}

template <typename T>
void Image<T>::setPixel(int x, int y, T val)
{
    // x -> ligne , y -> colonne
    m_pixels[x*getW() + y] = val;
}

template <typename T>
T* Image<T>::getPixels()
{
    return m_pixels;
}

template <typename T>
void Image<T>::setPixels(T *t)
{
    m_pixels = t;
}

// tri des pixels en fonction de leur niveau de gris -> le resultat est un tableau contenant les offsets des éléments du plus clair au plus foncé

template <typename T>
int* Image<T>::sortGrayLevel()
{
    int nbPixels = m_h*m_w;

    // parcours de l'image pixel par pixel, puis recherche de la bonne place dans le tableau
    int* table = new int[m_h* m_w];


    // initialisation tableau
    int i,j ;
    for (i= 0; i < nbPixels; i++)
    {
        table[i] = -1;
    }

    table[0] = 0;
    for (i= 1; i < nbPixels; i++)
    {
        j = 0;
        while( ((*this)[i] <= (*this)[table[j]]) && table[j] != -1)
        {
            j++;
        }
        if (table[j] == -1)
        {
            table[j] = i;
        }
        else
        {
            int k;
            for (k = nbPixels -1 ; k > j ; k--)
            {
                table[k] = table[k-1];
            }
            table[k] = i;
        }

    }

    return table;
}


//UNION-FIND

//on utilisera h et w pour vérifier si 2 pixels sont voisins ou non
int* union_find(int *R, int h, int w, TreeType t)
{
    int nbPixels = h * w;

    int* zpar= new int [nbPixels];
    int * parent = new int [nbPixels];

    int i,n,p,r;

    // for all p do zpar(p) <- undef
    for (i = 0 ; i < nbPixels; i++)
    {
        zpar[i] = -1 ;
    }


    // for <- N -1 to 0 do
    for (i = nbPixels -1 ; i >= 0 ; i --)
    {
        p = R[i]; // current pixel
        parent[p] = p; // parent[p] <- p
        zpar[p] = p; // zpar[p] <- p

        // for all n € N(p) such as zpar(n) != undef
        for (n = 0 ; n < nbPixels ; n++)
        {
            if (zpar[n] != -1 && isVoisin(n,p,h,w,t))
            {
                r = find_root(zpar,n);
                if (r != p)
                {
                    parent[r] = p;
                    zpar[r] = p;
                }
            }
        }

    }
    delete[]zpar;

    return parent;
}


// fonction isVoisin (n,p,R,h,w,t)

//n -> offset courant
//p -> pixel dont on veut connaitre le voisin
//h -> hauteur de l'image
//w -> largeur
//t -> type d'arbre pour la connexité

bool isVoisin(int n, int p, int h , int w , TreeType t)
{

    switch (t)
    {
    case MinTree : // connexité ->
        if (n/w == p/w)// test sur la même ligne
            return (n == p-1 || n == p+1);// à droite ou à gauche
        else return(std::abs(p - n) == w ); // sinon test si n est "juste" au-dessus ou "juste "en-dessous" de p
        break;
    case MaxTree :
        if (n/w == p/w ) // si les 2 pixels sont sur la même ligne
            return (n == p-1 || n == p+1);
        if (n/w == p/w -1 )// ligne du dessus
            return (n == p-w-1 || n == p-w+1 || n == p-w);
        if (n/w == p/w + 1)
            return (n == p+w-1 || n == p+w+1 || n == p+w);
        return false;
        break;
    default:
        return false;
        break;
    }
}


// FIND_ROOT

int find_root(int *zpar, int n)
{
    if (zpar[n] == n)
    {
        return n;
    }
    zpar[n] = find_root(zpar,zpar[n]);
    return zpar[n];
}

// REVERSE_ORDER

int* reverse_order (int *tab_in, int nb_elem)
{
    int i;
    int* tab_out = new int[nb_elem];
    for (i = 0; i < nb_elem; i++)
    {
        tab_out[i] = tab_in[nb_elem-i - 1];
    }
    return tab_out;
}


// CANONIZE_TREE -> to get the tree with only one represent by node
template <typename T>
void canonize_tree(int * parent,int nb_elem, const Image<T> & im, int * r)
{

    // modification apportée à la fonction canonize, on la réapplique tant que le résultat n'est pas stable
    int p,q ;
    bool change = false;

    for (p = nb_elem-1 ; p >= 0;p--)
    {
        q = parent[r[p]];
        if (im[parent[q]] == im[q])
        {
            if (parent[r[p]] != parent[q])
                change = true;
            parent[r[p]] = parent[q];
        }
    }

    if (change)
    {
        canonize_tree(parent,nb_elem,im,r);
    }
}


//      FONCTION pour INTERPOLATE de l'image

// fonction median_edge_value

template <typename T>
T Image<T>::median_edge_value()
{
    int i, h(getH()), w(getW());

    // création du tableau qui sera trié

    int size(2*h+ 2*(w-2)),compteur(0);
    T tmp[size];

    // si on ne prend pas les 4 coins de l'image on ne va que de 1 à la largeur moins 1 pixel
    for (i = 1; i < w-1; i ++)
    {
        tmp[compteur] = getPixel(0,i);
        tmp[compteur+1] = getPixel(h-1,i);
        compteur += 2;
    }

    for (i = 0; i < h; i++)
    {
        tmp[compteur] = getPixel(i,0);
        tmp[compteur +1]= getPixel(i,w-1);
        compteur +=2;
    }

    // tri du tableau

    std::sort(tmp,tmp+size);

    // récupération de la bonne valeur
    if (size % 2 == 1)
    {
        return tmp[size/2];
    }
    else
    {
        int sum = static_cast<int>(tmp[size/2 - 1]) + static_cast<int> (tmp[size/2 ]);
        sum/= 2;
        return static_cast<T> (sum);
    }
}

// fonction add_edge pour ajouter une bordure externe à l'image

template <typename T>
void Image<T>::add_edge()
{
    // censé être une variable de type T
    T edge_val = median_edge_value();
    // modification de la taille de l'image -> ajout de 2 lignes et de 2 colonnes

//    std::cout << "valeur médiane bordure interne " << static_cast<int>(edge_val) << std::endl;

    // ajout de 2 lignes et de 2 colonnes
    T* new_pixels = new T [(m_h+2) * (m_w +2)];

    // copie des valeurs à partir du tableau de base

    int i, j;

    for (i = 0; i < m_h+2; i ++ )
    {
        for (j = 0 ; j < m_w +2; j++)
        {
            if ( i == 0 || i == (m_h +1) || j == 0 || j == (m_w +1 )) // si on se trouve sur une "nouvelle" bordure, on met la valeur médiane
            {
                new_pixels[i * (m_w + 2) + j ] =  edge_val;
            }
            // sinon on récupère la valeur présente dans l'image de base
            // new_pixels[i,j] = im[i-1 ; j +1]
            else
            {
                new_pixels[i * (m_w +2 ) + j ] = getPixel(i-1,j-1);
            }

        }
    }




    //suppression du tableau représentant l'image de base
    delete []m_pixels;

    // le nouveau tableau sera le tableau créer dans la fonction
    m_pixels = new_pixels;

    // ajout des 2 lignes et des 2 colonnes dans les données de base de l'image pour ne plus avoir d'erreurs
    m_w += 2;
    m_h += 2;

}


// set-valued map

template <typename T>
void Image<T>::set_valued()
{
    // création d'un nouveau tableau

    // nouvelle largeur et hauteur
    int new_h  (m_h + (m_h -1)), new_w = (m_w + (m_w - 1));

    // on considère qu'à la création du tableau, il est forcément rempli avec des 0
    T* set_val = new T [new_h * new_w];

    int i, j ;
    // init de chaque case à 0;
    for (i  = 0;i < new_h;i ++)
    {
        for (j = 0; j < new_w; j++)
        {
            set_val[i*new_w + j] = static_cast<T>(0);
        }
    }


    int val;

    for (i  = 0;i < new_h;i ++)
    {
        for (j = 0; j < new_w; j++)
        {
            if ( i%2 == 0 && j%2 == 0)
            {
                // on fixe la valeur courante
                val = m_pixels [(i/2)*m_w + (j/2)];
                set_val[i*(new_w)+j] = val;

                //on vérifier les 8 cases autour pour éventuellement remplacer la valeur qui y est

                if (j -1 > 0) // la case en question existe
                {
                    // tester si la valeur présente est inférieur à la valeur de la case courante -> on remplace si c'est le cas
                    if (set_val[i* new_w + j -1 ] < val )
                        set_val[i * new_w + j -1 ] = val;

                    // vérifier si la case au-dessus existe aussi
                    if (i-1 > 0)
                    {
                        //si c'est le cas on peut directement fixer la case N-O
                        if (set_val[ (i-1) * new_w + j - 1 ] < val)
                            set_val[(i-1) * new_w + j -1 ] = val;
                    }

                    // vérifier si la case en-dessous existe aussi
                    if (i+1 < new_h)
                    {
                        //si c'est le cas on peut directement fixer la case S-O
                        if (set_val[ (i+1) * new_w + j - 1 ] < val)
                            set_val[(i+1) * new_w + j -1 ] = val;
                    }
                }

                if (j+1 < new_w) // la case à droite existe bien
                {
                    if (set_val[i* new_w + j+1 ] < val )
                        set_val[i * new_w + j +1 ] = val;

                    if (i-1 > 0)
                    {
                        //si c'est le cas on peut directement fixer la case N-E
                        if (set_val[ (i-1) * new_w + j +1 ] < val)
                            set_val[(i-1) * new_w + j+1 ] = val;
                    }

                    // vérifier si la case en-dessous existe aussi
                    if (i+1 < new_h)
                    {
                        //si c'est le cas on peut directement fixer la case S-E
                        if (set_val[ (i+1) * new_w + j + 1 ] < val)
                            set_val[(i+1) * new_w + j +1 ] = val;
                    }
                }

                // vérification au-dessus
                if (i-1 > 0 )
                    if (set_val[ (i-1) * new_w + j  ] < val)
                        set_val[(i-1) * new_w + j ] = val;
                // vérification en-dessous
                if (i+1 < new_h)
                    if (set_val[ (i+1) * new_w + j ] < val)
                        set_val[(i+1) * new_w + j ] = val;

            }
        }
    }

    // on supprime ensuite le tableau précédent -> m_pixels

    delete [] m_pixels;

    m_pixels = set_val;

    m_h = new_h;
    m_w = new_w;

}

template <typename T>
Image<T>* set_valuedMap(const Image<T>& i)
{
    // création de la nouvelle image
    Image<T>* returned_image = new Image<T>(i);

    returned_image->set_valued();

    return returned_image;
}


template <typename T>
int* Image<T>::computeMinTree()
{
    // on commence par trier l'image en fonction du niveau de gris
    // le tableau obtenu sera une liste d'offset, du pixel le plus clair au pixel le plus sombre

    int *r = sortGrayLevel();

    //calcul le nombre de pixels de l'image
    int nbP = getH() * getW();

    int* parent = union_find(r,getH(),getW(),MinTree);

    canonize_tree(parent,nbP,*this,r);

    return parent;
}


template <typename T>
int* Image<T>::computeMaxTree()
{
    //calcul le nombre de pixels de l'image
    int nbP = getH() * getW();


    int *r = reverse_order(sortGrayLevel(),nbP);



    int* parent = union_find(r,getH(),getW(),MaxTree);

    canonize_tree(parent,nbP,*this,r);

    return parent;
}

template <typename T>
int* Image<T>::computeTreeOfShapes()
{
    // dans cette fonction on suit exactement ce qui a été fait dans l'article

    // on ajoute une bordure externe à l'image courante
    Image<T> init (*this);
    init.add_edge();

    // this sera toujours l'image de base avec la bordure externe
    // on effectue ensuite la set_valued map sur cette image
    Image<T>* set_valuedIm = set_valuedMap(static_cast<const Image<T>&>(init));

    // on passe à la représentation de l'image suivant la grille de Khalimsky (interpolation fonction)

    ImageInterpolate<T> u (*set_valuedIm);

    // affichage de la légende ainsi que l'image Interpolate (avec couleurs pour y voir quelque chose)

    displayLegend();
    u.displayImage();

    // on crée ensuite l'image U exposant b qui contiendra le résultat de la procédure sort
    Image<T> u_b;
    // et r qui contiendra également le résultat de la procédure sort
    std::vector<int> r;

    u.sort(&u_b,&r,MinTree);// le type d'arbre ne change pas l'arbre obtenu (ce qui est modifié est le sens de parcour des pixels)

    int *parent = union_find(&r[0],u_b.getH(),u_b.getW(),MinTree); //UNION-FIND

    canonize_tree(parent,u_b.getH()*u_b.getW(),u_b,&r[0]); // canonize_tree

    // PHASE de DESINTERPOLATION

    // création du tableau de correspondance entre les éléments de l'image interpolate et l'image de base
    // tableau donne -1 si le pixel a été crée durant la phase d'interpolation et l'offset correspondant dans l'image de base sinon

    int*corresponding_table = u.corresponding();


    int* r_clean = u.R_un_interpolate(&r[0],corresponding_table);


//    displayTable(r_clean,init->getH(),init->getW());

    int * parent_clean = u.parent_un_interpolate(parent,corresponding_table);

    return parent_clean;

}

template <typename T>
int* Image<T>::computeTOS_perso()
{
    //les premières étapes sont les mêmes
    // on ajoute une bordure externe à l'image courante
    Image<T> init(*this);
    init.add_edge();


    // this sera toujours l'image de base avec la bordure externe
    // on effectue ensuite la set_valued map sur cette image
    Image<T>* set_valuedIm = set_valuedMap(static_cast<const Image<T>&>(init));


    // on passe à la représentation de l'image suivant la grille de Khalimsky (interpolation fonction)

    ImageInterpolate<T> u (*set_valuedIm);

    // affichage de la légende ainsi que l'image Interpolate (avec couleurs pour y voir quelque chose)

    displayLegend();
    u.displayImage();

    // on crée ensuite l'image U exposant b qui contiendra le résultat de la procédure sort
    Image<T> u_b;
    // et r qui contiendra également le résultat de la procédure sort
    std::vector<int> r;

    u.sort(&u_b,&r,MinTree);// le type d'arbre ne change pas l'arbre obtenu (ce qui est modifié est le sens de parcour des pixels)

    // ici on choisi de commencer par effectuer la désinterpolation de R qui donne un résultat correct sur les tests
    // -> r_clean correspond bien à un parcours en profondeur de l'arbre des formes

    int* corresponding_table = u.corresponding();

    int * r_clean = u.R_un_interpolate(&r[0],corresponding_table);

    // on effectue le union-find sur CE TABLEAU (r_clean)

    int* parent_clean = union_find(r_clean,init.getH(),init.getW(),MinTree);

    // on effectue la canonization maintenant

    canonize_tree(parent_clean,init.getH()*init.getW(),init,r_clean);

    return parent_clean;
}



template <typename T>
void Image<T>::afficheNode(Node *n)
{
    int x,y;
    int current_offset=0;
    for (x = 0; x < getH(); x++)
    {
        for (y =0; y < getW(); y ++)
        {
            if (n->contains(current_offset))
            {
                // test si c'est la racine
                if (n->getOffsetRoot() == current_offset)
                {
                    std::cout << "\033[1;41m" << static_cast<int>(getPixel(x,y)) << "\033[0m "; // background red
                }
                //
                else
                {
                    std::cout << "\033[1;31m" << static_cast<int>(getPixel(x,y)) << "\033[0m ";
                }
            }
            else
            {
                std::cout << static_cast<int>(getPixel(x,y)) << " ";
            }
            current_offset++;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template <typename T>
void Image<T>::afficheTree(Tree *t)
{
    if (t->getName()->size()>0)
        std::cout << "Arbre : " << *(t->getName()) << "\n";
    Node* tmp = t->getTreeRoot();
    afficheNode(tmp);
    std::vector<Node*>::iterator it;
    for (it= tmp->getSons()->begin();it != tmp->getSons()->end(); it++)
    {
        Tree* new_tree = new Tree(*it);
        afficheTree(new_tree);
    }
}


template <typename T>
std::ostream & operator<< (std::ostream& os, const Image<T>& i)
{
    int x,y;
    for (x = 0; x < i.getH(); x++)
    {
        for (y =0; y < i.getW(); y ++)
        {
            os << static_cast<int>(i.getPixel(x,y)) << " ";
        }
        os << std::endl;
    }

    return os;
}


// afficher tous types de tableau, parent ou r avec le même format que l'image pour essayer d'y voir quelque chose
void displayTable(int* table, int h, int w)
{
    std::cout << std::endl;

    int x(0),y(0);
    for(x = 0; x < h; x++)
    {
        for (y = 0; y < w; y++)
        {
            std::cout << table[x*w + y] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}



#endif // IMAGE_HPP
