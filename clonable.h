#ifndef CLONABLE_H
#define CLONABLE_H

class Clonable
{
public:
    virtual Clonable* clone() =0;
};

#endif
