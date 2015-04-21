#ifndef IMAGE_HPP
#define IMAGE_HPP

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
    int* zpar = new int[nbPixels];
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
//    for (i = 0; i < nbPixels; i++)
//    {
//        std::cout << zpar[i] << " ";
//    }
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



#endif // IMAGE_HPP
