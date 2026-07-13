/*
 * Entry: 0048a9c2
 * Name: std::_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::operator+=
 * Namespace: std::_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>
 * Signature: _Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> * operator+=(_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> * __thiscall
std::_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::operator+=
          (_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> *this,int param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 != (int *)0x0) goto LAB_0048a9dc;
    iVar2 = 0;
  }
  else {
LAB_0048a9dc:
    iVar2 = *piVar1;
  }
  if (piVar1 == (int *)0x0) {
    iVar4 = 0;
  }
  else {
    iVar4 = *piVar1;
  }
  uVar3 = this->_Myoff + param_1;
  if (uVar3 <= (uint)(*(int *)(iVar4 + 0x1c) + *(int *)(iVar2 + 0x18))) {
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *piVar1;
    }
    if (*(uint *)(iVar2 + 0x18) <= uVar3) goto LAB_0048aa10;
  }
  _invalid_parameter_noinfo();
LAB_0048aa10:
  this->_Myoff = this->_Myoff + param_1;
  return this;
}
