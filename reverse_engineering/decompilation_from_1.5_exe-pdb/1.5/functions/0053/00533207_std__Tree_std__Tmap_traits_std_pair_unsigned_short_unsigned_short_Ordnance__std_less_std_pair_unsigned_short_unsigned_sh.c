/*
 * Entry: 00533207
 * Name: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::iterator::operator*
 * Namespace: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::iterator
 * Signature: pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> * operator*(iterator * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> * __thiscall
std::
_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
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
      goto LAB_00532f1c;
    }
  }
  iVar2 = *piVar1;
LAB_00532f1c:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x18)) {
    _invalid_parameter_noinfo();
  }
  return (pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> *)
         (*(int *)&this->field_0x4 + 0xc);
}
