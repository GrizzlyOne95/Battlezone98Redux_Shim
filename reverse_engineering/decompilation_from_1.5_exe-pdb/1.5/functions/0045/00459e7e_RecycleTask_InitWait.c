/*
 * Entry: 00459e7e
 * Name: RecycleTask::InitWait
 * Namespace: RecycleTask
 * Signature: void InitWait(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::InitWait(RecycleTask *this)

{
  float fVar1;
  
  fVar1 = Get_TimeLocal();
  this->nextCheck = fVar1 + 60.0;
  return;
}
