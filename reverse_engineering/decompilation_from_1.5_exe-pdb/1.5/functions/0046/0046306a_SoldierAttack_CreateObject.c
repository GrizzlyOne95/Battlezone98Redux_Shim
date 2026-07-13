/*
 * Entry: 0046306a
 * Name: SoldierAttack::CreateObject
 * Namespace: SoldierAttack
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl SoldierAttack::CreateObject(void)

{
  UnitTask *this;
  
  this = operator_new(0x138);
  if (this != (UnitTask *)0x0) {
    UnitTask::UnitTask(this);
    this->_padding_ = (int)&_vftable_;
    return (SObject *)this;
  }
  return (SObject *)0x0;
}
