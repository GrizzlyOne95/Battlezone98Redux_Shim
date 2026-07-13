/*
 * Entry: 00457d08
 * Name: PersonEnemy::CreateObject
 * Namespace: PersonEnemy
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl PersonEnemy::CreateObject(void)

{
  PersonProcess *this;
  
  this = operator_new(0x80);
  if (this != (PersonProcess *)0x0) {
    PersonProcess::PersonProcess(this);
    this->_padding_ = (int)&_vftable_;
    return (SObject *)this;
  }
  return (SObject *)0x0;
}
