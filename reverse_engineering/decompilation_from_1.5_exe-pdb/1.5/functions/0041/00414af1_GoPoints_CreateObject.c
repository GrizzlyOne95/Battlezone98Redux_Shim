/*
 * Entry: 00414af1
 * Name: GoPoints::CreateObject
 * Namespace: GoPoints
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl GoPoints::CreateObject(void)

{
  GotoTask *this;
  
  this = operator_new(0x154);
  if (this != (GotoTask *)0x0) {
    GotoTask::GotoTask(this);
    this->_padding_ = (int)&_vftable_;
    return (SObject *)this;
  }
  return (SObject *)0x0;
}
