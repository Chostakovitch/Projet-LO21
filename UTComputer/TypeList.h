/**
  * @file TypeList.h Fichier de référence pour les listes de types.
  */

#ifndef TYPELIST_H
#define TYPELIST_H

/**
 * @brief Cette classe utilise la programmation pour représenter une liste de types ordonnée.
 */
template <typename H, typename T>
struct TypeList {
    typedef H Head;
    typedef T Tail;
};

/**
 * @brief Liste de types vide.
 */
struct Null_TypeList { };

template <class T1>
/**
 * @brief Liste de types à 1 élément.
 */
struct cons<T1, Null_TypeList, Null_TypeList, Null_TypeList, Null_TypeList, Null_TypeList> {
    typedef TypeList<T1, Null_TypeList> type;
};

template <class T1, class T2>
/**
 * @brief Liste de types à 2 éléments.
 */
struct cons<T1, T2, Null_TypeList, Null_TypeList, Null_TypeList, Null_TypeList> {
    typedef TypeList<T1, TypeList<T2, Null_TypeList>> type;
};

template <class T1, class T2, class T3>
/**
 * @brief Liste de types à 3 éléments.
 */
struct cons<T1, T2, T3, Null_TypeList, Null_TypeList, Null_TypeList> {
    typedef TypeList<T1, TypeList<T2, TypeList<T3, Null_TypeList>>> type;
};

template <class T1, class T2, class T3, class T4>
/**
 * @brief Liste de types à 4 éléments.
 */
struct cons<T1, T2, T3, T4, Null_TypeList, Null_TypeList> {
    typedef TypeList<T1, TypeList<T2, TypeList<T3, TypeList<T4, Null_TypeList>>>> type;
};

template <class T1, class T2, class T3, class T4, class T5>
/**
 * @brief Liste de types à 5 éléments.
 */
struct cons<T1, T2, T3, T4, T5, Null_TypeList> {
    typedef TypeList<T1, TypeList<T2, TypeList<T3, TypeList<T4, TypeList<T5, Null_TypeList>>>>> type;
};

template <class T1, class T2, class T3, class T4, class T5, class T6>
/**
 * @brief Liste de types à 6 éléments.
 */
struct cons {
    typedef TypeList<T1, TypeList<T2, TypeList<T3, TypeList<T4, TypeList<T5, TypeList<T6, Null_TypeList>>>>>> type;
};
#endif // TYPELIST_H
