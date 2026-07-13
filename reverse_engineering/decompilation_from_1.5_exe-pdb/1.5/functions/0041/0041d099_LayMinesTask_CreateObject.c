/*
 * Entry: 0041d099
 * Name: LayMinesTask::CreateObject
 * Namespace: LayMinesTask
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl LayMinesTask::CreateObject(void)

{
  GotoTask *this;
  
  this = operator_new(0x17c);
  if (this != (GotoTask *)0x0) {
    GotoTask::GotoTask(this);
    this->_padding_ = (int)&_vftable_;
    return (SObject *)this;
  }
  return (SObject *)0x0;
}
