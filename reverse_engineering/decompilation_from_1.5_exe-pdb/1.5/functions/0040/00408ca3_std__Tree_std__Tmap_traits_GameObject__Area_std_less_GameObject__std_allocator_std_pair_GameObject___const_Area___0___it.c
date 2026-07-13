/*
 * Entry: 00408ca3
 * Name: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::iterator::operator->
 * Namespace: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::iterator
 * Signature: pair<GameObject_*_const,Area> * operator->(iterator * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<GameObject_*_const,Area> * __thiscall
std::
_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
::iterator::operator->(iterator *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00405ec5;
    }
  }
  iVar2 = *piVar1;
LAB_00405ec5:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x18)) {
    _invalid_parameter_noinfo();
  }
  return (pair<GameObject_*_const,Area> *)(*(int *)&this->field_0x4 + 0xc);
}
