/*
 * Entry: 0041528b
 * Name: HuntTask::PostLoad
 * Namespace: HuntTask
 * Signature: bool PostLoad(HuntTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall HuntTask::PostLoad(HuntTask *this)

{
  bool bVar1;
  
  bVar1 = UnitTask::PostLoad((UnitTask *)this);
  return bVar1;
}
