/*
 * Entry: 0046939a
 * Name: UnitProcess::PostLoad
 * Namespace: UnitProcess
 * Signature: bool PostLoad(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall UnitProcess::PostLoad(UnitProcess *this)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = ConvertHandle(this->saveWho);
  this->saveWho = iVar2;
  iVar2 = ConvertHandle(this->whoHandle);
  this->whoHandle = iVar2;
  this->me->_padding_ = this->independence;
  bVar1 = SObject::PostLoad((SObject *)this);
  return bVar1;
}
