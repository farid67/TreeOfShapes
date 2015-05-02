#ifndef NODE_H
#define NODE_H

#include <vector>
#include "iostream"
#include "sstream"
#include "algorithm"

class Node
{
public:
    Node(int offset_root);
    ~Node();

    void add_element(int offset);

    void add_son (Node* son);

    void set_father (Node* father);

    int getOffsetRoot() const;

    bool isFather (int i) {return i==m_offset_root;}

    std::vector<int>* getElements() const;

    std::vector<Node*>* getSons() const{return m_sons;}

    std::ostringstream* getName() const;

    Node* getFather() const;

    bool contains(int i) { return (std::find(m_elements->begin(),m_elements->end(),i)!=m_elements->end());}

private:
    static int m_compteur;//compteur d'élément pour le nommage des noeuds



    std::ostringstream* m_name;
    int m_offset_root;
    std::vector<int> *m_elements;// le nombre d'éléments sera également connu par ce vector
    Node* m_father;
    std::vector<Node*> *m_sons;

};

std::ostream& operator << (std::ostream& os , const Node& n);

#include "Node.hpp"

#endif // NODE_H
