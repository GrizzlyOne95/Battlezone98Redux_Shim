/*
 * Entry: 00485fc4
 * Name: Craft::PostLoad
 * Namespace: Craft
 * Signature: bool PostLoad(Craft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Craft::PostLoad(Craft *this)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = ConvertHandle(this->abandoned);
  this->abandoned = iVar2;
  bVar1 = GameObject::PostLoad((GameObject *)this);
  (**(code **)(this->_padding_ + 0xa0))(this->_padding_);
  return bVar1;
}
