/*
 * Entry: 00459f09
 * Name: RecycleTask::CleanStuck
 * Namespace: RecycleTask
 * Signature: void CleanStuck(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::CleanStuck(RecycleTask *this)

{
  float *pfVar1;
  float fVar2;
  
  fVar2 = Get_TimeLocal();
  this->nextStuck = fVar2 + 5.0;
  pfVar1 = (float *)(**(code **)(this->me->_padding_ + 0xc))();
  (this->lastStuck).x = *pfVar1;
  (this->lastStuck).y = pfVar1[1];
  (this->lastStuck).z = pfVar1[2];
  return;
}
