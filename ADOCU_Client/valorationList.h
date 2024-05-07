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
        ValorationList(int size);
        ValorationList(Valoration *valorations, int numValorations, int size);
        ValorationList(const ValorationList &valorationList);
        virtual ~ValorationList();

        Valoration *getValorations();
        int getNumValorations();
        int getSize();
        void setValorations(Valoration *valorations);
        void setNumValorations(int numValorations);
        void setSize(int size);
        void addValoration(Valoration valoration);
};

#endif