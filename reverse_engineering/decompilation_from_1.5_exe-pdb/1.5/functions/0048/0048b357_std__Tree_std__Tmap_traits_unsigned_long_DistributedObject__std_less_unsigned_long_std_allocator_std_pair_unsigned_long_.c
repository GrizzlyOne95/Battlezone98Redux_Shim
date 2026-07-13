/*
 * Entry: 0048b357
 * Name: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::iterator::operator*
 * Namespace: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::iterator
 * Signature: pair<unsigned_long_const_,DistributedObject_*> * operator*(iterator * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<unsigned_long_const_,DistributedObject_*> * __thiscall
std::
_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
::iterator::operator*(iterator *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0048a5d8;
    }
  }
  iVar2 = *piVar1;
LAB_0048a5d8:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x18)) {
    _invalid_parameter_noinfo();
  }
  return (pair<unsigned_long_const_,DistributedObject_*> *)(*(int *)&this->field_0x4 + 0xc);
}
