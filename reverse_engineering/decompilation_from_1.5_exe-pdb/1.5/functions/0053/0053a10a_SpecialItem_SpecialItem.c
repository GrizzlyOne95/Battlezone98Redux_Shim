/*
 * Entry: 0053a10a
 * Name: SpecialItem::SpecialItem
 * Namespace: SpecialItem
 * Signature: SpecialItem * SpecialItem(SpecialItem * this, _OBJ76 * param_1, SpecialItemClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpecialItem * __thiscall
SpecialItem::SpecialItem(SpecialItem *this,_OBJ76 *param_1,SpecialItemClass *param_2)

{
  GameObject *pGVar1;
  
  Weapon::Weapon((Weapon *)this,param_1,(WeaponClass *)param_2);
  this->shotTimer = 0.0;
  this->fraction = 0.0;
  this->_padding_ = (int)&_vftable_;
  this->triggered = false;
  this->held = '\0';
  if (this->_padding_ == 0) {
    pGVar1 = (GameObject *)0x0;
  }
  else {
    pGVar1 = *(GameObject **)(this->_padding_ + 0xb4);
  }
  this->carrier = pGVar1;
  this->reticleBase = this->_padding_;
  this->reticleCount = 0;
  return this;
}
