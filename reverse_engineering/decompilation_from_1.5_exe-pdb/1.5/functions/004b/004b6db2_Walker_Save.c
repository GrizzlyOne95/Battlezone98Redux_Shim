/*
 * Entry: 004b6db2
 * Name: Walker::Save
 * Namespace: Walker
 * Signature: bool Save(Walker * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Walker::Save(Walker *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::out(param_1,&this->_padding_,4,"abandoned");
  if ((bVar1) && (bVar1 = GameObject::Save((GameObject *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
