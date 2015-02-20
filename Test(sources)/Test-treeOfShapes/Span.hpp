#ifndef SPAN_HPP
#define SPAN_HPP

#include "Span.h"

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
void Span<T>::setSpan(T val)
{
    m_inf_bounds = m_sup_bounds = val;
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
