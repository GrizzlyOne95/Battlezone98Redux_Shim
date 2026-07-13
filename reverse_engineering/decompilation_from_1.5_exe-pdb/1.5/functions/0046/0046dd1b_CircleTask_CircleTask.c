/*
 * Entry: 0046dd1b
 * Name: CircleTask::CircleTask
 * Namespace: CircleTask
 * Signature: CircleTask * CircleTask(CircleTask * this, Craft * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CircleTask * __thiscall CircleTask::CircleTask(CircleTask *this,Craft *param_1)

{
  UnitTask::UnitTask((UnitTask *)this,param_1,(GameObject *)0x0);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 6;
  return this;
}
