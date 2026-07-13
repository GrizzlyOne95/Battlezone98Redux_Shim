/*
 * Entry: 0046dcd9
 * Name: SitTask::SitTask
 * Namespace: SitTask
 * Signature: SitTask * SitTask(SitTask * this, Craft * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SitTask * __thiscall SitTask::SitTask(SitTask *this,Craft *param_1)

{
  UnitTask::UnitTask((UnitTask *)this,param_1,(GameObject *)0x0);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 6;
  return this;
}
