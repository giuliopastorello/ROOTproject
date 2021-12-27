#ifndef RESONANCETYPE_H
#define RESONANCETYPE_H

#include "particletype.h"

class ResonanceType : public ParticleType {
  public:   
    virtual double GetWidth (); 
    void Print () override;
    ResonanceType (const char* , double, int, double);
  private:
    const double fWidth;
};

#endif