#include "valorationList.h"
#include <iostream>

using namespace std;

ValorationList::ValorationList() {
    valorations = new Valoration[10];
    numValorations = 0;
    size = 0;
}

ValorationList::ValorationList(int size) {
    valorations = new Valoration[size];
    numValorations = 0;
    this->size = size;
}

ValorationList::ValorationList(Valoration *valorations, int numValorations, int size) {
    this->valorations = valorations;
    this->numValorations = numValorations;
    this->size = size;
}

ValorationList::ValorationList(const ValorationList &valorationList) {
    this->valorations = valorationList.valorations;
    this->numValorations = valorationList.numValorations;
    this->size = valorationList.size;
}

Valoration *ValorationList::getValorations() {
    return valorations;
}

int ValorationList::getNumValorations() {
    return numValorations;
}

int ValorationList::getSize() {
    return size;
}

void ValorationList::setValorations(Valoration *valorations) {
    this->valorations = valorations;
}

void ValorationList::setNumValorations(int numValorations) {
    this->numValorations = numValorations;
}

void ValorationList::setSize(int size) {
    this->size = size;
}

ValorationList::~ValorationList() {
    delete[] valorations;
}

void ValorationList::addValoration(Valoration valoration) {
    if (numValorations < size) {
        valorations[numValorations] = valoration;
        numValorations++;
    } else {
        cout << "No se pueden añadir más valoraciones" << endl;
    }
}