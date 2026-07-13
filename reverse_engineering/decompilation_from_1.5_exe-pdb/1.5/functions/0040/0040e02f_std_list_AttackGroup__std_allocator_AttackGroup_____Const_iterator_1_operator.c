/*
 * Entry: 0040e02f
 * Name: std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Const_iterator<1>::operator++
 * Namespace: std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Const_iterator<1>
 * Signature: _Const_iterator<1> * operator++(_Const_iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Const_iterator<1> * __thiscall
std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Const_iterator<1>::operator++
          (_Const_iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0040e04d;
    }
  }
  iVar2 = *piVar1;
LAB_0040e04d:
  if (this->_Ptr == *(_Node **)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  this->_Ptr = this->_Ptr->_Next;
  return this;
}
