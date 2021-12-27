#include <iostream>
#include "particletype.h"
#include "resonancetype.h"

double ResonanceType::GetWidth () {return fWidth;}
void ResonanceType::Print () {
    ParticleType::Print ();
    std::cout << "Width: " << fWidth << '\n'; 
} 
ResonanceType::ResonanceType (const char* name_, double mass_, int charge_, double width_) :
ParticleType(name_, mass_, charge_), fWidth {width_} {}

