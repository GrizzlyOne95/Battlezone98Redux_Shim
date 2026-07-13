/*
 * Entry: 004103e2
 * Name: BuildGoto::CreateObject
 * Namespace: BuildGoto
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl BuildGoto::CreateObject(void)

{
  GotoTask *this;
  
  this = operator_new(0x15c);
  if (this != (GotoTask *)0x0) {
    GotoTask::GotoTask(this);
    this->_padding_ = (int)&_vftable_;
    return (SObject *)this;
  }
  return (SObject *)0x0;
}
