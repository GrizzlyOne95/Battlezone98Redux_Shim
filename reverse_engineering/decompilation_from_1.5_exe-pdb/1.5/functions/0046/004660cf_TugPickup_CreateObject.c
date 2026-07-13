/*
 * Entry: 004660cf
 * Name: TugPickup::CreateObject
 * Namespace: TugPickup
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl TugPickup::CreateObject(void)

{
  GotoTask *this;
  
  this = operator_new(0x160);
  if (this != (GotoTask *)0x0) {
    GotoTask::GotoTask(this);
    this->_padding_ = (int)&_vftable_;
    return (SObject *)this;
  }
  return (SObject *)0x0;
}
