#include "valoration.h"
#include <iostream>

using namespace std;

Valoration::Valoration() {
    valoration = '0';
}

Valoration::Valoration(char valoration) {
    this->valoration = valoration;
}

Valoration::Valoration(const Valoration &valoration) {
    this->valoration = valoration.valoration;
}

Valoration::~Valoration() {};

char Valoration::getValoration() {
    return valoration;
}

void Valoration::setValoration(char valoration) {
    this->valoration = valoration;
}