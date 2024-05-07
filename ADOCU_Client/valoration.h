#ifndef VALORATION_H_
#define VALORATION_H_

class Valoration {
    private:
        char valoration;
    public:
        Valoration();
        Valoration(char valoration);
        Valoration(const Valoration &valoration);
        virtual ~Valoration();

        char getValoration();
        void setValoration(char valoration);
};

#endif