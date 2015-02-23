#ifndef SPAN_H
#define SPAN_H

#include "iostream"

template <typename T>
class Span
{
private:
    T m_inf_bounds;
    T m_sup_bounds;

public:
    Span ();
    Span (T min, T max);
    Span (T uniq_val); // dans le cas où on souhaite créer un intervalle avec une seule valeur -> par exemple lorsqu'on se trouve sur une bordure
    ~Span();

    void setSpan(T t1, T t2);
    void setSpan(T val);// modification de l'intervalle pour qu'il ne contienne qu'une valeur

    // variantes pour le calculs des d0-Faces dans l'image interpolate
    // uniquement une variante avec tri + récupération des valeurs extremes
    void setSpan(const Span<T>& t1,const Span<T>& t2);
    void setSpan(const Span<T>& t1,const Span<T>& t2, const Span<T>& t3);
    void setSpan (const Span<T>& t1, const Span<T>& t2, const Span<T>& t3, const Span<T>& t4);

    T getInfBounds() const ;
    T getSupBounds () const ;

};


template <typename T>
std::ostream& operator << (std::ostream& os, const Span<T>& s );



#include "Span.hpp"

#endif // SPAN_H
