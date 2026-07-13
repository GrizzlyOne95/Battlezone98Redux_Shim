/*
 * Entry: 00463097
 * Name: SoldierAttack::SoldierAttack
 * Namespace: SoldierAttack
 * Signature: SoldierAttack * SoldierAttack(SoldierAttack * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SoldierAttack * __thiscall
SoldierAttack::SoldierAttack(SoldierAttack *this,Craft *param_1,GameObject *param_2)

{
  AttackGroup *this_00;
  
  UnitTask::UnitTask((UnitTask *)this,param_1,param_2);
  *(undefined ***)this = &_vftable_;
  this_00 = AttackGroup::Find(param_2);
  *(AttackGroup **)&this->field_0x108 = this_00;
  AttackGroup::Join(this_00,(GameObject *)param_1,(UnitTask *)this);
  *(undefined4 *)&this->field_0xf4 = 0x42200000;
  *(undefined4 *)&this->field_0xc = 1;
  *(undefined4 *)&this->field_0x10 = 1;
  return this;
}
