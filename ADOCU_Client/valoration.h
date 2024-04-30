#ifndef VALORATION_H_
#define VALORATION_H_

class Valoration {
    private:
        char valoration;
    public:
        Valoration();
        Valoration(const Valoration &valoration);
        Valoration(char valoration);
        virtual ~Valoration();
};

#endif