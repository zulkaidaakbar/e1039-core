#ifndef PHG4CollimatorSteppingAction_h
#define PHG4CollimatorSteppingAction_h

#include <g4main/PHG4SteppingAction.h>

class G4VPhysicalVolume;
class PHG4CollimatorDetector;
class PHG4Hit;
class PHG4HitContainer;
class PHParameters;
class PHG4Shower;

class PHG4CollimatorSteppingAction : public PHG4SteppingAction
{
 public:
  //! constructor
  PHG4CollimatorSteppingAction(PHG4CollimatorDetector *, const PHParameters *parameters);

  //! destructor
  virtual ~PHG4CollimatorSteppingAction();

  //! stepping action
  virtual bool UserSteppingAction(const G4Step *, bool);

  //! reimplemented from base class
  virtual void SetInterfacePointers(PHCompositeNode *);

 private:
  //! pointer to the detector
  PHG4CollimatorDetector *detector_;
  const PHParameters *params;
  //! pointer to hit container
  PHG4HitContainer *hits_;
  PHG4Hit *hit;
  PHG4Shower *saveshower;
  G4VPhysicalVolume *savevolpre;
  G4VPhysicalVolume *savevolpost;
  int savetrackid;
  int saveprestepstatus;
  int savepoststepstatus;
  int active;
  int IsBlackHole;

  int use_g4_steps;
};

#endif  //__G4PHPHYTHIAREADER_H__
