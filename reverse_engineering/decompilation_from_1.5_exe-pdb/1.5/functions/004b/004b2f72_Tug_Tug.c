/*
 * Entry: 004b2f72
 * Name: Tug::Tug
 * Namespace: Tug
 * Signature: Tug * Tug(Tug * this, _OBJ76 * param_1, TugClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Tug * __thiscall Tug::Tug(Tug *this,_OBJ76 *param_1,TugClass *param_2)

{
  float fVar1;
  int *extraout_EDX;
  
  HoverCraft::HoverCraft((HoverCraft *)this,param_1,(HoverCraftClass *)param_2);
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  this->cargo = (GameObject *)0x0;
  this->hitchTug = (_OBJ76 *)0x0;
  this->hitchCargo = (_OBJ76 *)0x0;
  FindHitch((_OBJ76 *)this->_padding_,&this->hitchTug);
  if (*extraout_EDX == 0) {
    *extraout_EDX = this->_padding_;
  }
  this->_padding_ = 0;
  fVar1 = (float)param_2[1]._padding_;
  this->animHandle = -1;
  this->dockSpeed = fVar1;
  this->timeDeploy = 0.1;
  this->timeUndeploy = 0.1;
  return this;
}
