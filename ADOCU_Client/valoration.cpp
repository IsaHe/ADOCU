#include "valoration.h"
#include <iostream>
#include <string.h>

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

char *Valoration::jsonifyValoration(User user) const {
    std::string json = "\"valoration\": \"";
    json += user.getUsername();
    json += "\"{";
    json += valoration;
    json += "}";

    char *cstr = new char[json.length() + 1];
    strcpy(cstr, json.c_str());

    return cstr;
}
