/*
 * Entry: 00463126
 * Name: SoldierRetreat::SoldierRetreat
 * Namespace: SoldierRetreat
 * Signature: SoldierRetreat * SoldierRetreat(SoldierRetreat * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SoldierRetreat * __thiscall
SoldierRetreat::SoldierRetreat(SoldierRetreat *this,Craft *param_1,GameObject *param_2)

{
  GotoTask::GotoTask((GotoTask *)this,param_1,param_2);
  *(undefined ***)this = &_vftable_;
  this->field_0x142 = 1;
  return this;
}
