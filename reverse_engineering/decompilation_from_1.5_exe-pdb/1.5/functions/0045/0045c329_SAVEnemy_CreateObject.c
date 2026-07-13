/*
 * Entry: 0045c329
 * Name: SAVEnemy::CreateObject
 * Namespace: SAVEnemy
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl SAVEnemy::CreateObject(void)

{
  UnitProcess *this;
  
  this = operator_new(0x58);
  if (this != (UnitProcess *)0x0) {
    UnitProcess::UnitProcess(this);
    this->_padding_ = (int)&_vftable_;
    return (SObject *)this;
  }
  return (SObject *)0x0;
}
