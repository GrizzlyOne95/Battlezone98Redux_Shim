/*
 * Entry: 00456eec
 * Name: PatrolTask::PostLoad
 * Namespace: PatrolTask
 * Signature: bool PostLoad(PatrolTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall PatrolTask::PostLoad(PatrolTask *this)

{
  bool bVar1;
  
  bVar1 = UnitTask::PostLoad((UnitTask *)this);
  return bVar1;
}
