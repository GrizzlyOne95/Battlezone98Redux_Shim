/*
 * Entry: 004630f9
 * Name: SoldierRetreat::CreateObject
 * Namespace: SoldierRetreat
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl SoldierRetreat::CreateObject(void)

{
  GotoTask *this;
  
  this = operator_new(0x150);
  if (this != (GotoTask *)0x0) {
    GotoTask::GotoTask(this);
    this->_padding_ = (int)&_vftable_;
    return (SObject *)this;
  }
  return (SObject *)0x0;
}
