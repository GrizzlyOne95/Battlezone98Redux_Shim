/*
 * Entry: 0045b587
 * Name: RescueTask::CreateObject
 * Namespace: RescueTask
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl RescueTask::CreateObject(void)

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
