/*
 * Entry: 0052d742
 * Name: Dispenser::Dispenser
 * Namespace: Dispenser
 * Signature: Dispenser * Dispenser(Dispenser * this, _OBJ76 * param_1, DispenserClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Dispenser * __thiscall Dispenser::Dispenser(Dispenser *this,_OBJ76 *param_1,DispenserClass *param_2)

{
  GameObject *pGVar1;
  
  Weapon::Weapon((Weapon *)this,param_1,(WeaponClass *)param_2);
  this->shotTimer = 0.0;
  this->_padding_ = (int)&_vftable_;
  if (this->_padding_ == 0) {
    pGVar1 = (GameObject *)0x0;
  }
  else {
    pGVar1 = *(GameObject **)(this->_padding_ + 0xb4);
  }
  this->carrier = pGVar1;
  this->triggered = false;
  return this;
}
