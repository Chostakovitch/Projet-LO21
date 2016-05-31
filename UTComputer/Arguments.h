#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <memory>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <typeinfo>

/**
 * @brief Wrapper vide de std::vector.
 */
template <typename T>
class Arguments : public std::vector<T> {
public:
    using std::vector<T>::vector;
};

/**
 * @brief Spécialisation du wrapper de vector pour les pointeurs intelligents.
 * @details Ce wrapper ajoute une fonctionnalité de transtypage horizontal. Il tente de caster un vecteur de pointeurs sur T en vecteur sur U.
 * Usuellement, T = Literal. Le polymorphisme s'appliquant, les bons opérateurs de cast des classes filles sont appelés s'ils existent.
 * Le but de cette opération est d'uniformiser le vecteur qui peut contenir des pointeurs sur classes soeurs, nécessitant la création de nouveaux objets
 * et non pas un simple cast dynamique.
 * @exception TypeError si l'opérateur de cast U(T) n'est pas implémenté.
 */
template <typename T>
class Arguments<std::shared_ptr<T>> : public std::vector<std::shared_ptr<T>> {
public:
    using std::vector<std::shared_ptr<T>>::vector;
    /**
     * @brief Affichage d'un vecteur de pointeurs.
     * @return Chaîne formatée.
     */
    std::string toString() const {
        std::ostringstream oss;
        oss << "[";
        for(const auto& e : *this) {
            if(&e != &(this->back())) oss << *e << ", ";
        }
        if(!this->empty()) oss << *(this->back());
        else oss << "Undefined";
        oss << "]";
        return oss.str();
    }
    /**
     * @brief Upcasting d'un vecteur de pointeurs, pas de conversion nécessaires
     */
    template <typename U, typename std::enable_if<std::is_base_of<U, T>::value || std::is_same<U, T>::value>::type>
    operator Arguments<std::shared_ptr<U>>() const {
        Arguments<std::shared_ptr<U>> dest;
        for (auto& arg : *this) {
            dest.push_back(arg);
        }
        return dest;
    }

    /**
     * @brief Cast réel des objets pointés d'un vecteur de pointeurs sur T vers un vecteur de pointeurs sur U
     */
    template <typename U>
    operator Arguments<std::shared_ptr<U>>() const {
        Arguments<std::shared_ptr<U>> dest;
        for (auto& arg : *this) {
            //Si le type réel de l'objet pointé est compatible avec le type de destination, on n'appelle pas d'opérateur de cast
            if(auto ptr = std::dynamic_pointer_cast<U>(arg)) dest.push_back(ptr);
            //Sinon, il faut passer par l'opérateur de cast et construire un nouveau pointeur
            else dest.push_back(std::make_shared<U>((U)*arg));
        }
        return dest;
    }
};

#endif // ARGUMENTS_H
