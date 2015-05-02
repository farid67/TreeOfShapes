#ifndef SPAN_HPP
#define SPAN_HPP

#include "Span.h"
#include "algorithm"


template <typename T>
Span<T>::Span():m_inf_bounds (0), m_sup_bounds(0)
{
}

template <typename T>
Span<T>::Span(T min, T max): m_inf_bounds (min), m_sup_bounds(max)
{

}


template <typename T>
Span<T>::Span(T uniq_val) :m_inf_bounds (uniq_val),m_sup_bounds(uniq_val)
{

}

template <typename T>
Span<T>::Span(const Span<T> &s)
{
    m_inf_bounds = s.getInfBounds();
    m_sup_bounds = s.getSupBounds();
}

template <typename T>
Span<T>::~Span()
{

}


template <typename T>
void Span<T>::setSpan(T t1, T t2)
{
    if (t2>t1)
    {
        m_inf_bounds = t1;
        m_sup_bounds = t2;
    }
    else
    {
        m_inf_bounds = t2;
        m_sup_bounds = t1;
    }
}


template <typename T>
void Span<T>:: setSpan (const Span<T>& t1, const Span<T>& t2)
{
    T tmp_tab[4] = {t1.getInfBounds(),t1.getSupBounds(),t2.getInfBounds(),t2.getSupBounds()};
    std::sort(tmp_tab,tmp_tab+(2*2));
    m_inf_bounds = tmp_tab[0];
    m_sup_bounds = tmp_tab[3];
}

template <typename T>
void Span<T>:: setSpan (const Span<T>& t1, const Span<T>& t2, const Span<T>& t3)
{
    //on trie le tableau -> gain en simplicité
    T tmp_tab[6] = {t1.getInfBounds(),t1.getSupBounds(),t2.getInfBounds(),t2.getSupBounds(),t3.getInfBounds(),t3.getSupBounds()};
    std::sort(tmp_tab,tmp_tab+(2*3));
    m_inf_bounds = tmp_tab[0];
    m_sup_bounds = tmp_tab[5];
}

template <typename T>
void Span<T>:: setSpan (const Span<T> &t1, const Span<T> &t2, const Span<T> &t3, const Span<T> &t4)
{
    //on trie le tableau -> gain en simplicité
    T tmp_tab[8] = {t1.getInfBounds(),t1.getSupBounds(),t2.getInfBounds(),t2.getSupBounds(),t3.getInfBounds(),t3.getSupBounds(),t4.getInfBounds(),t4.getSupBounds()};
    std::sort(tmp_tab,tmp_tab+(2*4));
    m_inf_bounds = tmp_tab[0];
    m_sup_bounds = tmp_tab[7];
}

template <typename T>
void Span<T>::setSpan(T val)
{
    m_inf_bounds = val;
    m_sup_bounds = val;
}

template <typename T>
T Span<T>::getInfBounds() const
{
    return m_inf_bounds;
}

template <typename T>
T Span<T>::getSupBounds() const
{
    return m_sup_bounds;
}

template <typename T>
std::ostream& operator << (std::ostream& os, const Span<T> &s  )
{
    os << "[";
    if(s.getInfBounds() == s.getSupBounds())
    {
        os << " " << static_cast<int> (s.getInfBounds()) << " " ;
    }
    else
    {
        os << static_cast<int> (s.getInfBounds()) << ";" << static_cast<int>(s.getSupBounds()) ;
    }
    os << "]";
    return os;
}

#endif // SPAN_HPP
