/*
 * Entry: 0040c7e9
 * Name: ArmoryProcess::PostLoad
 * Namespace: ArmoryProcess
 * Signature: bool PostLoad(ArmoryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ArmoryProcess::PostLoad(ArmoryProcess *this)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = ConvertHandle(this->whoHandle);
  this->whoHandle = iVar2;
  bVar1 = SObject::PostLoad((SObject *)this);
  return bVar1;
}
