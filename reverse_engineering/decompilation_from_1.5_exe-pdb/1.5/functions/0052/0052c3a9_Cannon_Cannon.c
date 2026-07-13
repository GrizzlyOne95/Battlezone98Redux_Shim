/*
 * Entry: 0052c3a9
 * Name: Cannon::Cannon
 * Namespace: Cannon
 * Signature: Cannon * Cannon(Cannon * this, _OBJ76 * param_1, CannonClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Cannon * __thiscall Cannon::Cannon(Cannon *this,_OBJ76 *param_1,CannonClass *param_2)

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
