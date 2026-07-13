/*
 * Entry: 0040eca2
 * Name: AttackTask::PostLoad
 * Namespace: AttackTask
 * Signature: bool PostLoad(AttackTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AttackTask::PostLoad(AttackTask *this)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = ConvertHandle(this->fleeFrom);
  this->fleeFrom = iVar2;
  bVar1 = UnitTask::PostLoad((UnitTask *)this);
  if (this->_padding_ == 0) {
    this->_padding_ = 0xd;
    this->_padding_ = 0xd;
  }
  return bVar1;
}
