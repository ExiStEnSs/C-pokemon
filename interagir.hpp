#ifndef INTERAGIR_HPP
#define INTERAGIR_HPP
#include <string>

class Interagir {
public:
    virtual ~Interagir() = default;
    virtual std::string interaction() const = 0;
};
#endif