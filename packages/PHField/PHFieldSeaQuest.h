#ifndef __PHFieldSeaQuest_H__
#define __PHFieldSeaQuest_H__

#include "PHField.h"
#include "PHField3DCartesian.h"

#include <map>
#include <set>

//! untested code - I don't know if this is being used, drop me a line (with the field) and I test this - Chris P.
class PHFieldSeaQuest : public PHField
{
 public:
  PHFieldSeaQuest(const std::string &fmag_name, const std::string &kmag_name);
  virtual ~PHFieldSeaQuest();

  //! access field value
  //! Follow the convention of G4ElectroMagneticField
  //! @param[in]  Point   space time coordinate. x, y, z, t in Geant4/CLHEP units
  //! @param[out] Bfield  field value. In the case of magnetic field, the order is Bx, By, Bz in in Geant4/CLHEP units
  void GetFieldValue(const double Point[4], double *Bfield) const;

 protected:
  float zValues[4];

  PHField3DCartesian fmag;
  PHField3DCartesian kmag;
};

#endif  // __PHFIELD3D_H