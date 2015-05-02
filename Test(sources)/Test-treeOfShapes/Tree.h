#ifndef TREE_H
#define TREE_H
#include "Node.h"
#include "iostream"

class Tree
{
private:
    Node* root;
    std::string * tree_name;

public:
    Tree();
    Tree(int* parent, int nbElement,std::string name); // on peut directement créer un arbre à partir du tableau de parent
    ~Tree();
    Tree(Node* n_r);

    Node* getTreeRoot() const;

    void setName (std::string* new_name){tree_name= new_name;}

    std::string* getName() const{return tree_name;}

};

std::ostream& operator << (std::ostream& os,const Tree& t);

#include "Tree.hpp"

#endif // TREE_H


