/*
 * Entry: 004675a5
 * Name: TurretAttack::CreateObject
 * Namespace: TurretAttack
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl TurretAttack::CreateObject(void)

{
  UnitTask *this;
  
  this = operator_new(0x140);
  if (this != (UnitTask *)0x0) {
    UnitTask::UnitTask(this);
    this->_padding_ = (int)&_vftable_;
    return (SObject *)this;
  }
  return (SObject *)0x0;
}
