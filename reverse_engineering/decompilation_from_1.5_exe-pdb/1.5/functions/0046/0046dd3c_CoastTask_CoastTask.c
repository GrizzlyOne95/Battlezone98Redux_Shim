/*
 * Entry: 0046dd3c
 * Name: CoastTask::CoastTask
 * Namespace: CoastTask
 * Signature: CoastTask * CoastTask(CoastTask * this, Craft * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CoastTask * __thiscall CoastTask::CoastTask(CoastTask *this,Craft *param_1)

{
  UnitTask::UnitTask((UnitTask *)this,param_1,(GameObject *)0x0);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 6;
  return this;
}
