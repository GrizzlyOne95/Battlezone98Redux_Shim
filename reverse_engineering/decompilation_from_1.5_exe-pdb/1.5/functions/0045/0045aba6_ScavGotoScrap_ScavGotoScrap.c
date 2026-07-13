/*
 * Entry: 0045aba6
 * Name: ScavGotoScrap::ScavGotoScrap
 * Namespace: ScavGotoScrap
 * Signature: ScavGotoScrap * ScavGotoScrap(ScavGotoScrap * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScavGotoScrap * __thiscall
ScavGotoScrap::ScavGotoScrap(ScavGotoScrap *this,Craft *param_1,GameObject *param_2)

{
  byte bVar1;
  
  GoNear::GoNear((GoNear *)this,param_1,param_2,6.0);
  *(undefined ***)this = &_vftable_;
  bVar1 = (**(code **)(param_1->_padding_ + 4))();
  param_2->locked = param_2->locked | 1 << (bVar1 & 0x1f);
  *(undefined4 *)&this->field_0x100 = 0x40a00000;
  *(undefined4 *)&this->field_0x70 = 0x3f800000;
  *(undefined4 *)&this->field_0x124 = 0;
  return this;
}
