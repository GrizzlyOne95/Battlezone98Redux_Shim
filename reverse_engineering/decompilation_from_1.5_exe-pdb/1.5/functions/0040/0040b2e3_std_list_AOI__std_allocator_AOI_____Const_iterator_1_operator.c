/*
 * Entry: 0040b2e3
 * Name: std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator++
 * Namespace: std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>
 * Signature: _Const_iterator<1> operator++(_Const_iterator<1> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Const_iterator<1> __thiscall
std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator++
          (_Const_iterator<1> *this,int param_1)

{
  _Node *extraout_EDX;
  _Const_iterator<1> _Var1;
  
  *(int *)param_1 = this->_padding_;
  *(_Node **)(param_1 + 4) = this->_Ptr;
  operator++(this);
  _Var1._Ptr = extraout_EDX;
  _Var1._padding_ = param_1;
  return _Var1;
}
