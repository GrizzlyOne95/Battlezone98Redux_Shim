/*
 * Entry: 0052c7a2
 * Name: ChargeGun::ChargeGun
 * Namespace: ChargeGun
 * Signature: ChargeGun * ChargeGun(ChargeGun * this, _OBJ76 * param_1, ChargeGunClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ChargeGun * __thiscall ChargeGun::ChargeGun(ChargeGun *this,_OBJ76 *param_1,ChargeGunClass *param_2)

{
  int iVar1;
  OrdnanceData *pOVar2;
  OrdnanceData *pOVar3;
  OrdnanceClass *pOVar4;
  
  Cannon::Cannon((Cannon *)this,param_1,(CannonClass *)param_2);
  this->go = (_gas_object *)0x0;
  this->_padding_ = (int)&_vftable_;
  this->emptyLevel = param_2->ordnanceData;
  iVar1 = param_2->ordnanceCount;
  pOVar2 = this->emptyLevel;
  pOVar3 = param_2->ordnanceData;
  this->chargeLevel = pOVar2;
  this->fullLevel = pOVar3 + iVar1;
  pOVar4 = pOVar2->ordnanceClass;
  this->salvoCount = 0;
  this->_padding_ = (int)pOVar4;
  return this;
}
