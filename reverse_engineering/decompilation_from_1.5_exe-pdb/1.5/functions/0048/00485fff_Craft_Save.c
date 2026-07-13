/*
 * Entry: 00485fff
 * Name: Craft::Save
 * Namespace: Craft
 * Signature: bool Save(Craft * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Craft::Save(Craft *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::out(param_1,&this->abandoned,4,"abandoned");
  if ((bVar1) && (bVar1 = GameObject::Save((GameObject *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
