/*
 * Entry: 0052a8f9
 * Name: BeamGun::BeamGun
 * Namespace: BeamGun
 * Signature: BeamGun * BeamGun(BeamGun * this, _OBJ76 * param_1, BeamGunClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BeamGun * __thiscall BeamGun::BeamGun(BeamGun *this,_OBJ76 *param_1,BeamGunClass *param_2)

{
  GameObject *pGVar1;
  
  Weapon::Weapon((Weapon *)this,param_1,(WeaponClass *)param_2);
  this->_padding_ = (int)&_vftable_;
  if (this->_padding_ == 0) {
    pGVar1 = (GameObject *)0x0;
  }
  else {
    pGVar1 = *(GameObject **)(this->_padding_ + 0xb4);
  }
  this->carrier = pGVar1;
  this->fraction = 0.0;
  this->triggered = false;
  this->go = (_gas_object *)0x0;
  this->ordnance = (Ordnance *)0x0;
  return this;
}
