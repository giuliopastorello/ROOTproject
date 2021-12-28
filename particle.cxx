#include "particletype.h"
#include "resonancetype.h"
#include "particle.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

//#Particle Types in the Array
int Particle::fNParticleType = 0;
//Declare Array
ParticleType* Particle::fParticleType[fMaxNumParticleType]; 
//FindParticle
int Particle::FindParticle(const char* name_)
{
  int n = 0;
  for (int i = 0; i < fNParticleType; ++i){ 
    if ( fParticleType[i]->GetName() == name_) {
      n = i;
      break;
    } else {
      n = -1;
    }
  }
  return n;
} 
//Constructor
Particle::Particle(const char *name_, double P_x = 0, double P_y = 0, double P_z = 0) 
  : fP_x{P_x}, fP_y{P_y}, fP_z{P_z}
{
  if (FindParticle(name_) != -1) {
    fIndex = FindParticle(name_);
  } else {
    std::cout << "Particle Not Found!" << '\n';
  }
}
//AddParticle
void Particle::AddParticleType(const char *name, double mass, int charge, double width = 0) 
{
  if (fNParticleType != 0) {
    if (FindParticle(name) == -1 && fNParticleType < fMaxNumParticleType) {
    if (width == 0 ){ fParticleType[fNParticleType] = new ParticleType(name, mass, charge);} 
    else if (width !=0) {fParticleType[fNParticleType] = new ResonanceType(name, mass, charge, width);}
    ++fNParticleType;  
  } else {
    std::cerr << "Particle Already Present or Max Num Particles Reached! " << name << '\n';
  } 
  } else {
    if (width == 0 ){ fParticleType[fNParticleType] = new ParticleType(name, mass, charge);} 
    else if (width !=0) {fParticleType[fNParticleType] = new ResonanceType(name, mass, charge, width);}
    ++fNParticleType; 
  }
}
//ParticleTypePrint
void Particle::Print1() {
  for (int i = 0; i < fNParticleType; ++i){
    fParticleType[i]->Print();
  }
}
//Prind Index, Name, Momentum COmponents
void Particle::Print2() {
  std::cout << "Index: " << fIndex << '\n';
  std::cout << "Name: " << fParticleType[fIndex]->GetName() << '\n';
  std::cout << "X Momentum:" << fP_x << '\n';
  std::cout << "Y Momentum:" << fP_y << '\n';
  std::cout << "Z Momentum:" << fP_z << '\n';
}
//SETTERS
void Particle::SetIndex (int a) {
    fIndex = a;  
}
//overload SetIndex
void Particle::SetIndex (const char* name) {
    if (FindParticle(name) != -1) {
      fIndex = FindParticle(name);
    } else {
      std::cerr << "Particle Not Found! " << '\n';
    }
}

void Particle::SetP (double px, double py, double pz) {
  fP_x = px;
  fP_y = py;
  fP_z = pz;
}
//GETTERS
double Particle::GetPx() const { return fP_x; }
double Particle::GetPy() const { return fP_y; }
double Particle::GetPz() const { return fP_z; }

const char* Particle::GetName() const {return fParticleType[fIndex]->GetName();}
double Particle::GetMass() const {return fParticleType[fIndex]->GetMass();}
int Particle::GetCharge() const {return fParticleType[fIndex]->GetCharge();}

int Particle::GetIndex() const {return fIndex;}

double Particle::GetEnergy () const {
  double m = Particle::GetMass();
  double p = sqrt(fP_x * fP_x + fP_y * fP_y + fP_z * fP_z);
  return sqrt(m * m + p * p);
}
//Invariant Mass
double Particle::InvMass(Particle &p) const {
  double px = fP_x + p.GetPx();
  double py = fP_y + p.GetPy();
  double pz = fP_z + p.GetPz();
  double psumsquared = px * px + py * py + pz * pz;
  return sqrt(pow(GetEnergy() + p.GetEnergy(), 2.0) - psumsquared);
}
//PART TWO:2 new methods
//Decayment into Two "Daughter" Particles
int Particle::Decay2body(Particle &dau1,Particle &dau2) const {
  if(GetMass() == 0.0){
    printf("Decayment cannot be preformed if mass is zero\n");
    return 1;
  }
  
  double massMot = GetMass();
  double massDau1 = dau1.GetMass();
  double massDau2 = dau2.GetMass();

  if(fIndex > -1){ // add width effect

    // gaussian random numbers

    float x1, x2, w, y1, y2;
    
    double invnum = 1./RAND_MAX;
    do {
      x1 = 2.0 * rand()*invnum - 1.0;
      x2 = 2.0 * rand()*invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while ( w >= 1.0 );
    
    w = sqrt( (-2.0 * log( w ) ) / w );
    y1 = x1 * w;
    y2 = x2 * w;

    massMot += fParticleType[fIndex]->GetWidth() * y1;

  }

  if(massMot < massDau1 + massDau2){
    printf("Decayment cannot be preformed because mass is too low in this channel\n");
    return 2;
  }
  
  double pout = sqrt((massMot*massMot - (massDau1+massDau2)*(massDau1+massDau2))*(massMot*massMot - (massDau1-massDau2)*(massDau1-massDau2)))/massMot*0.5;

  double norm = 2*M_PI/RAND_MAX;

  double phi = rand()*norm;
  double theta = rand()*norm*0.5 - M_PI/2.;
  dau1.SetP(pout*sin(theta)*cos(phi),pout*sin(theta)*sin(phi),pout*cos(theta));
  dau2.SetP(-pout*sin(theta)*cos(phi),-pout*sin(theta)*sin(phi),-pout*cos(theta));

  double energy = sqrt(fP_x*fP_x + fP_y*fP_y + fP_z*fP_z + massMot*massMot);

  double bx = fP_x/energy;
  double by = fP_y/energy;
  double bz = fP_z/energy;

  dau1.Boost(bx,by,bz);
  dau2.Boost(bx,by,bz);

  return 0;
}

void Particle::Boost(double bx, double by, double bz)
{

  double energy = GetEnergy();

  //Boost this Lorentz vector
  double b2 = bx*bx + by*by + bz*bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx*fP_x + by*fP_y + bz*fP_z;
  double gamma2 = b2 > 0 ? (gamma - 1.0)/b2 : 0.0;

  fP_x += gamma2*bp*bx + gamma*bx*energy;
  fP_y += gamma2*bp*by + gamma*by*energy;
  fP_z += gamma2*bp*bz + gamma*bz*energy;
}
