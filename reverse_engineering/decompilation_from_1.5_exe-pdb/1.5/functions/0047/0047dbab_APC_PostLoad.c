/*
 * Entry: 0047dbab
 * Name: APC::PostLoad
 * Namespace: APC
 * Signature: bool PostLoad(APC * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall APC::PostLoad(APC *this)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = ConvertHandle(this->_padding_);
  this->_padding_ = iVar2;
  bVar1 = GameObject::PostLoad((GameObject *)this);
  (**(code **)(this->_padding_ + 0xa0))(this->_padding_);
  return bVar1;
}
