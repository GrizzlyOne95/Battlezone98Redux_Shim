/*
 * Entry: 0047012f
 * Name: UserProcess::PostLoad
 * Namespace: UserProcess
 * Signature: bool PostLoad(UserProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall UserProcess::PostLoad(UserProcess *this)

{
  bool bVar1;
  
  Init(this);
  bVar1 = SObject::PostLoad((SObject *)this);
  return bVar1;
}
