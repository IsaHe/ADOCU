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

char Valoration::getValoration() const {
    return valoration;
}

void Valoration::setValoration(char valoration) {
    this->valoration = valoration;
}

char *Valoration::jsonifyValoration() const {
    char *json = new char[7];
    json[0] = 'v';
    json[1] = 'a';
    json[2] = 'l';
    json[3] = '{';
    json[4] = valoration;
    json[5] = '}';
    json[6] = '\0';
    return json;
}
