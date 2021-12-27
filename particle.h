#ifndef PARTICLE_H
#define PARTICLE_H

#include "particletype.h"
#include "resonancetype.h"

class Particle {
    static const int fMaxNumParticleType = 10;
    static ParticleType* fParticleType[fMaxNumParticleType];
    static int fNParticleType;
    int fIndex;
    double fP_x, fP_y, fP_z;
    static int FindParticle (const char* name_); 
    void Boost(double bx, double by, double bz);
  public:
    Particle() = default;
    Particle (const char* name_, double P_x, double P_y, double P_z);
    static void AddParticleType (const char* , double, int, double);
    int GetIndex () const;
    static void Print1();
    void Print2();
    double GetPx () const;
    double GetPy () const;
    double GetPz () const;
    void SetP (double, double, double);
    const char* GetName () const;
    double GetMass () const;
    int GetCharge () const;
    void SetIndex (int);
    void SetIndex (const char* );
    double GetEnergy () const;
    double InvMass (Particle &p) const;
    int Decay2body(Particle &dau1,Particle &dau2) const;
};


#endif