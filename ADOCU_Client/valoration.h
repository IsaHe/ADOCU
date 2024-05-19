#ifndef VALORATION_H_
#define VALORATION_H_

#include "user.h"

class Valoration {
    private:
        char valoration;
    public:
        Valoration();
        Valoration(char valoration);
        Valoration(const Valoration &valoration);
        virtual ~Valoration();

        char getValoration() const;
        void setValoration(char valoration);

        char *jsonifyValoration(User user) const;
};

#endif