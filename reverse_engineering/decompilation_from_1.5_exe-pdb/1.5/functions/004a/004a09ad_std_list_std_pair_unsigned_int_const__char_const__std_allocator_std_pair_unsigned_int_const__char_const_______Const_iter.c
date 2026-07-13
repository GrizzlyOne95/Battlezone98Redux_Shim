/*
 * Entry: 004a09ad
 * Name: std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>::_Const_iterator<1>::operator--
 * Namespace: std::list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>::_Const_iterator<1>
 * Signature: _Const_iterator<1> * operator--(_Const_iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Const_iterator<1> * __thiscall
std::
list<std::pair<unsigned_int_const_,char_const_*>,std::allocator<std::pair<unsigned_int_const_,char_const_*>_>_>
::_Const_iterator<1>::operator--(_Const_iterator<1> *this)

{
  _Node *p_Var1;
  int iVar2;
  
  if (this->_padding_ == 0) {
    _invalid_parameter_noinfo();
  }
  p_Var1 = this->_Ptr->_Prev;
  this->_Ptr = p_Var1;
  if ((int *)this->_padding_ == (int *)0x0) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)this->_padding_;
  }
  if (p_Var1 == *(_Node **)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return this;
}
