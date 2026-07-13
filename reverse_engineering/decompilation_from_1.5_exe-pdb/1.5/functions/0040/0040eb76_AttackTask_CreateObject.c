/*
 * Entry: 0040eb76
 * Name: AttackTask::CreateObject
 * Namespace: AttackTask
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl AttackTask::CreateObject(void)

{
  UnitTask *this;
  
  this = operator_new(0x144);
  if (this != (UnitTask *)0x0) {
    UnitTask::UnitTask(this);
    this->_padding_ = (int)&_vftable_;
    return (SObject *)this;
  }
  return (SObject *)0x0;
}
