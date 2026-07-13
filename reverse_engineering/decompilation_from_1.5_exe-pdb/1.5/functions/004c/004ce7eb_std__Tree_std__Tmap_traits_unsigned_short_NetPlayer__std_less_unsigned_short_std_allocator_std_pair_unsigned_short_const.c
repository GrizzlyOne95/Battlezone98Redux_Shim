/*
 * Entry: 004ce7eb
 * Name: std::_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>::iterator::operator*
 * Namespace: std::_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>::iterator
 * Signature: pair<unsigned_short_const_,NetPlayer_*> * operator*(iterator * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<unsigned_short_const_,NetPlayer_*> * __thiscall
std::
_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
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
      goto LAB_004ce759;
    }
  }
  iVar2 = *piVar1;
LAB_004ce759:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x18)) {
    _invalid_parameter_noinfo();
  }
  return (pair<unsigned_short_const_,NetPlayer_*> *)(*(int *)&this->field_0x4 + 0xc);
}
