/*
 * Entry: 00463176
 * Name: SoldierReturn::SoldierReturn
 * Namespace: SoldierReturn
 * Signature: SoldierReturn * SoldierReturn(SoldierReturn * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SoldierReturn * __thiscall
SoldierReturn::SoldierReturn(SoldierReturn *this,Craft *param_1,GameObject *param_2)

{
  GotoTask::GotoTask((GotoTask *)this,param_1,param_2);
  *(undefined ***)this = &_vftable_;
  this->field_0x142 = 1;
  return this;
}
