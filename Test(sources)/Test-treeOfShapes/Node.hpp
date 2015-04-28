#ifndef NODE_HPP
#define NODE_HPP
#include "Node.h"

int Node::m_compteur = 0;

Node::Node(int offset_root)
{
    m_offset_root = offset_root;
    // création du vector d'éléments
    m_elements = new std::vector<int>();
    //création du vector de Fils ...et initialisation du père à NULL
    m_sons = new std::vector<Node*>();

    m_father = static_cast<Node*>(NULL);

    // ajout de l'élément au tableau d'élément

    m_elements->push_back(m_offset_root);

    m_name = new std::ostringstream();

    (*m_name) << "Node_" << m_compteur;

    m_compteur ++;

}

Node::~Node()
{
}

void Node::add_element(int offset)
{
    m_elements->push_back(offset);
}

void Node::add_son(Node *son)
{
    m_sons->push_back(son);
}

void Node::set_father(Node *father)
{
    m_father=father;
}

int Node::getOffsetRoot() const
{
    return m_offset_root;
}

std::vector<int>* Node::getElements() const
{
    return m_elements;
}


std::ostringstream* Node::getName() const
{
    return m_name;
}


Node* Node::getFather()const
{
    return m_father;
}


std::ostream& operator << (std::ostream& os, const Node& n)
{
    os << n.getName()->str();
    os << " racine du noeud à l'adresse " << n.getOffsetRoot();
    os << "\t Nombre d'éléments : " << n.getElements()->size();
    os << "\n\t Famille : " ;
    os << "\n\t\t Père de : " ;
    std::vector<Node*>::iterator it;
    std::vector<Node*>* node_list = n.getSons();
    if (node_list->size() == 0)
    {
        os << "personne" ;
    }
    else
    {
        for (it = node_list->begin();it != node_list->end(); it++)
        {
            os << (*it)->getName()->str() << " ";
        }
    }

    os << "\n\t\t Fils de ";
    if (n.getFather() == NULL)
        os << "personne";
    else
        os << n.getFather()->getName()->str();


    os << "\n" ;
    return os;
}

#endif // NODE_HPP
