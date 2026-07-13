/*
 * Entry: 0048a679
 * Name: std::_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::operator*
 * Namespace: std::_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>
 * Signature: BASE_STRUCT * operator*(_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BASE_STRUCT * __thiscall
std::_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::operator*
          (_Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> *this)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  uVar1 = this->_Myoff;
  piVar2 = (int *)this->_padding_;
  uVar5 = uVar1 >> 1;
  if (piVar2 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar2 = (int *)this->_padding_;
    if (piVar2 == (int *)0x0) {
      iVar4 = 0;
      goto LAB_0048a6a5;
    }
  }
  iVar4 = *piVar2;
LAB_0048a6a5:
  if (piVar2 == (int *)0x0) {
    iVar3 = 0;
  }
  else {
    iVar3 = *piVar2;
  }
  if ((uint)(*(int *)(iVar3 + 0x1c) + *(int *)(iVar4 + 0x18)) <= this->_Myoff) {
    _invalid_parameter_noinfo();
  }
  piVar2 = (int *)this->_padding_;
  if (piVar2 == (int *)0x0) {
    iVar4 = 0;
  }
  else {
    iVar4 = *piVar2;
  }
  if (*(uint *)(iVar4 + 0x14) <= uVar5) {
    if (piVar2 == (int *)0x0) {
      iVar4 = 0;
    }
    else {
      iVar4 = *piVar2;
    }
    uVar5 = uVar5 - *(int *)(iVar4 + 0x14);
  }
  if (piVar2 == (int *)0x0) {
    iVar4 = 0;
  }
  else {
    iVar4 = *piVar2;
  }
  return (BASE_STRUCT *)((uVar1 & 1) * 6 + *(int *)(*(int *)(iVar4 + 0x10) + uVar5 * 4));
}
