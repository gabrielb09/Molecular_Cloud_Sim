#ifndef CloudPhysicsList_H
#define CloudPhysicsList_H 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class CloudPhysicsList: public G4VModularPhysicsList
{
public:
  CloudPhysicsList();
  virtual ~CloudPhysicsList();

public:
  // SetCuts()
  virtual void SetCuts();


};

#endif
