/*
 * Entry: 0045bd29
 * Name: SAVAttackPersonTask::~SAVAttackPersonTask
 * Namespace: SAVAttackPersonTask
 * Signature: void ~SAVAttackPersonTask(SAVAttackPersonTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SAVAttackPersonTask::~SAVAttackPersonTask(SAVAttackPersonTask *this)

{
  *(undefined ***)this = &_vftable_;
  CleanState(this);
  *(undefined4 *)&this->field_0xc = 0xd;
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
