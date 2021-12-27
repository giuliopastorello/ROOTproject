#ifndef PARTICLETYPE_H
#define PARTICLETYPE_H

class ParticleType { 
  public:
    ParticleType (const char* name_, double mass_, int charge_);
    const char* GetName () const;
    double GetMass () const;
    int GetCharge () const;
    virtual void Print ();
    double GetWidth ();
  private:
    const char* fName;
    const double fMass;
    const int fCharge;
};

#endif