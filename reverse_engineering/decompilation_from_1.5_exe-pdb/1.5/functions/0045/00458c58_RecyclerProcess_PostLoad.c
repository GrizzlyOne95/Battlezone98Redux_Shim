/*
 * Entry: 00458c58
 * Name: RecyclerProcess::PostLoad
 * Namespace: RecyclerProcess
 * Signature: bool PostLoad(RecyclerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall RecyclerProcess::PostLoad(RecyclerProcess *this)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = ConvertHandle(this->whoHandle);
  this->whoHandle = iVar2;
  bVar1 = SObject::PostLoad((SObject *)this);
  return bVar1;
}
