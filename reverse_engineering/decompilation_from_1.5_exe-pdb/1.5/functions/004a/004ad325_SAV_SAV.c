/*
 * Entry: 004ad325
 * Name: SAV::SAV
 * Namespace: SAV
 * Signature: SAV * SAV(SAV * this, _OBJ76 * param_1, SAVClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SAV * __thiscall SAV::SAV(SAV *this,_OBJ76 *param_1,SAVClass *param_2)

{
  HoverCraft::HoverCraft((HoverCraft *)this,param_1,(HoverCraftClass *)param_2);
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  this->_padding_ = 3;
  this->setAltitude = *(float *)(this->_padding_ + 0x3c0);
  return this;
}
