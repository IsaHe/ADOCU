#include "valoration.h"
#ifndef VALORATIONLIST_H_
#define VALORATIONLIST_H_

class ValorationList {
    private:
        Valoration *valorations;
        int numValorations;
        int size;
    public:
        ValorationList();
        ValorationList(const ValorationList &valorationList);
        ValorationList(Valoration *valorations, int numValoramiento, int size);
        virtual ~ValorationList();
};

#endif