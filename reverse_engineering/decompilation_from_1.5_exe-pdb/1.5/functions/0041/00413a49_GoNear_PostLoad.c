/*
 * Entry: 00413a49
 * Name: GoNear::PostLoad
 * Namespace: GoNear
 * Signature: bool PostLoad(GoNear * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GoNear::PostLoad(GoNear *this)

{
  bool bVar1;
  
  bVar1 = UnitTask::PostLoad((UnitTask *)this);
  return bVar1;
}
