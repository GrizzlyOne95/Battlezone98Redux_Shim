/*
 * Entry: 0047daf5
 * Name: APC::APC
 * Namespace: APC
 * Signature: APC * APC(APC * this, _OBJ76 * param_1, APCClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

APC * __thiscall APC::APC(APC *this,_OBJ76 *param_1,APCClass *param_2)

{
  float fVar1;
  
  HoverCraft::HoverCraft((HoverCraft *)this,param_1,(HoverCraftClass *)param_2);
  this->_padding_ = 0;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  fVar1 = param_2->reloadRange;
  this->soldierDelay = 0.0;
  this->soldierCount = (int)fVar1;
  this->reloadDelay = 0.0;
  return this;
}
