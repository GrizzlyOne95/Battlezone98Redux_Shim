/*
 * Entry: 00466ec4
 * Name: TugFriend::CreateObject
 * Namespace: TugFriend
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl TugFriend::CreateObject(void)

{
  TugProcess *this;
  
  this = operator_new(0x4c);
  if (this != (TugProcess *)0x0) {
    TugProcess::TugProcess(this);
    this->_padding_ = (int)&_vftable_;
    return (SObject *)this;
  }
  return (SObject *)0x0;
}
