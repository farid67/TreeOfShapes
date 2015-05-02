#ifndef TREE_HPP
#define TREE_HPP
#include "Tree.h"
#include "algorithm"

Tree::Tree()
{
    root = static_cast<Node*> (NULL);
}

Tree::~Tree()
{
}

Node* Tree::getTreeRoot() const
{
    return root;
}

Tree::Tree(Node *n_r)
{
    tree_name =  new std::string();
    root = n_r;
}


Tree::Tree(int *parent, int nbElement,std::string name)
{
    tree_name= new std::string(name);

    int i ;
    std::vector<int> canonic_offset; //tableau qui contiendra les éléments qui apparaissent dans le tableau de parent
    // lecture du tableau de parent (pour la récupération des éléments distincts)
    /*
    for (i = 0; i<  nbElement; i++)
    {
        // récupération de éléments distincts
        if (std::find(canonic_offset.begin(),canonic_offset.end(),parent[i]) == canonic_offset.end())
        {
//            std::cout << "l'élément " << parent[i] << " n'a pas été trouvé" << std::endl;
            canonic_offset.push_back(parent[i]);
        }
    }

    // création des n Node, sachant que n représente le nombre d'éléments du vector
    std::vector <Node*>* Tree_node = new std::vector<Node*>();

    for (i = 0;i < static_cast<int>(canonic_offset.size());i++)
    {
        Tree_node->push_back(new Node(canonic_offset.at(i)));
    }
    */

    // modification -> amélioration temps de calcul
    std::vector <Node*>* Tree_node = new std::vector<Node*>();

    for (i = 0; i<  nbElement; i++)
    {
        // récupération de éléments distincts
        if (std::find(canonic_offset.begin(),canonic_offset.end(),parent[i]) == canonic_offset.end())
        {
//            std::cout << "l'élément " << parent[i] << " n'a pas été trouvé" << std::endl;
            canonic_offset.push_back(parent[i]);
            Tree_node->push_back(new Node(parent[i]));
        }
    }

    std::cout << "il y a " << canonic_offset.size() << " noeuds différents " << std::endl;


    // pour chaque élément dont l'offset est différent de celles des noeuds canoniques, on l'ajoute au noeud correspondant

    for (i = 0; i <nbElement; i++)
    {
        // vérifier qu'il ne s'agit pas d'un noeud canonique
        if (std::find(canonic_offset.begin(),canonic_offset.end(),i) == canonic_offset.end())
        {
            // dans ce cas on l'ajoute au noeud correspondant
            /*
            // parcours du vector
            std::vector<Node*>::iterator it;
            for (it=Tree_node->begin(); it != Tree_node->end();it++)
            {
                if ((*it)->isFather(parent[i]))
                {
                    (*it)->add_element(i);
                }
            }
            */

            // parcours de canonic_offset ->moins de calcul
//            std::vector<int>::iterator it;
//            for (it=canonic_offset.begin(); it != canonic_offset.end();it++)
//            {
//                std::cout << "recherche pour le noeud n°"<< *it << std::endl;
//                if (Tree_node->at(*it)->isFather(parent[i]))
//                {
//                    Tree_node->at(*it)->add_element(i);
//                }
//            }

            int j;
            for (j = 0; j< static_cast<int> (canonic_offset.size());j++)
            {
                if (Tree_node->at(j)->isFather(parent[i]))
                        Tree_node->at(j)->add_element(i);
            }

        }
    }


    // gestion des racines maintenant

    /*
    std::vector<Node*>::iterator it;
    for (it = Tree_node->begin();it != Tree_node->end();it++)
    {
        // verifier la valeur de parent[(*it)->getOffsetRoot]
        if (parent[(*it)->getOffsetRoot()] == (*it)->getOffsetRoot())
        {
            // le noeud est la racine de de l'arbre
            root = *it;
        }

        else
        {
            // ajouter le noeud à la liste des fils de parent[i] et ajouter parent[i] comme étant son fils

            // trouver le noeud père
            std::vector<Node*>::iterator it_fatherSearch;
            for(it_fatherSearch = Tree_node->begin(); it_fatherSearch != Tree_node->end();it_fatherSearch++)
            {
                if ((*it_fatherSearch)->getOffsetRoot() == parent[(*it)->getOffsetRoot()])
                {
                    //père trouvé
                    (*it_fatherSearch)->add_son(*it);
                    (*it)->set_father(*it_fatherSearch);
                }
            }
        }
    }
    */

    // diminution des temps de calcul en ne parcourant que canonic_offset

//    std::vector<int>::iterator it;
//    for (it = canonic_offset.begin();it != canonic_offset.end();it++)
//    {
    for (i=0; i< static_cast<int>(canonic_offset.size());i++)
    {
        // verifier la valeur de parent[(*it)->getOffsetRoot]
        if (parent[Tree_node->at(i)->getOffsetRoot()] == Tree_node->at(i)->getOffsetRoot())
        {
            // le noeud est la racine de de l'arbre
            root = Tree_node->at(i);
        }

        else
        {
            // ajouter le noeud à la liste des fils de parent[i] et ajouter parent[i] comme étant son fils

            // trouver le noeud père
//            std::vector<int>::iterator it_fatherSearch;
//            for(it_fatherSearch = canonic_offset.begin(); it_fatherSearch != canonic_offset.end();it_fatherSearch++)
//            {
            int it_fatherSearch;
            for (it_fatherSearch=0;it_fatherSearch<static_cast<int>(canonic_offset.size());it_fatherSearch++)
            {
                if (Tree_node->at(it_fatherSearch)->getOffsetRoot() == parent[Tree_node->at(i)->getOffsetRoot()])
                {
                    //père trouvé
                    Tree_node->at(it_fatherSearch)->add_son(Tree_node->at(i));
                    Tree_node->at(i)->set_father(Tree_node->at(it_fatherSearch));
                }
            }
        }
    }

}

std::ostream& operator << (std::ostream& os, const Tree& t)
{
    if (t.getName()->size()>0)
        os << "Arbre : " << *(t.getName()) << "\n";
    Node* tmp = t.getTreeRoot();
    os<< *tmp;
    std::vector<Node*>::iterator it;
    for (it= tmp->getSons()->begin();it != tmp->getSons()->end(); it++)
    {
        Tree* new_tree = new Tree(*it);
        operator << (os,*new_tree);
    }
    return os;
}


#endif // TREE_HPP
