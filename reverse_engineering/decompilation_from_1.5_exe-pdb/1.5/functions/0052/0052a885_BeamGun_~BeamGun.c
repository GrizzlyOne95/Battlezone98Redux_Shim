/*
 * Entry: 0052a885
 * Name: BeamGun::~BeamGun
 * Namespace: BeamGun
 * Signature: void ~BeamGun(BeamGun * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BeamGun::~BeamGun(BeamGun *this)

{
  Ordnance *pOVar1;
  
  pOVar1 = this->ordnance;
  this->_padding_ = (int)&_vftable_;
  if (pOVar1 != (Ordnance *)0x0) {
    if (pOVar1->ordnanceClass->sig == 0x4245414d) {
      pOVar1[1].euler.v_mag = -NAN;
    }
    this->ordnance = (Ordnance *)0x0;
  }
  Weapon::~Weapon((Weapon *)this);
  return;
}
