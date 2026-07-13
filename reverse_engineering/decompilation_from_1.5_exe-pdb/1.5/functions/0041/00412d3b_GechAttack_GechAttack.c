/*
 * Entry: 00412d3b
 * Name: GechAttack::GechAttack
 * Namespace: GechAttack
 * Signature: GechAttack * GechAttack(GechAttack * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GechAttack * __thiscall GechAttack::GechAttack(GechAttack *this,Craft *param_1,GameObject *param_2)

{
  UnitTask::UnitTask((UnitTask *)this,param_1,param_2);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 1;
  *(undefined4 *)&this->field_0x10 = 5;
  return this;
}
