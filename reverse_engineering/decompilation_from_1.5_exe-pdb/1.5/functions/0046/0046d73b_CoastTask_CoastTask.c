/*
 * Entry: 0046d73b
 * Name: CoastTask::CoastTask
 * Namespace: CoastTask
 * Signature: CoastTask * CoastTask(CoastTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CoastTask * __thiscall CoastTask::CoastTask(CoastTask *this)

{
  UnitTask::UnitTask((UnitTask *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
