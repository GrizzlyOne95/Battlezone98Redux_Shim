/*
 * Entry: 00405ea7
 * Name: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::const_iterator::operator*
 * Namespace: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::const_iterator
 * Signature: pair<GameObject_*_const,Area> * operator*(const_iterator * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<GameObject_*_const,Area> * __thiscall
std::
_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
::const_iterator::operator*(const_iterator *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00405ec5;
    }
  }
  iVar2 = *piVar1;
LAB_00405ec5:
  if (this->_Ptr == *(_Node **)(iVar2 + 0x18)) {
    _invalid_parameter_noinfo();
  }
  return &this->_Ptr->_Myval;
}
