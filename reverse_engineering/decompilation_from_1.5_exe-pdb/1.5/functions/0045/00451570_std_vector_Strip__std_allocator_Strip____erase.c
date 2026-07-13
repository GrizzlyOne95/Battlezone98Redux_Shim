/*
 * Entry: 00451570
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::erase
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: _Vector_iterator<Strip_*,std::allocator<Strip_*>_> erase(vector<Strip_*,std::allocator<Strip_*>_> * this, _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> param_1, _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Strip_*,std::allocator<Strip_*>_> __thiscall
std::vector<Strip_*,std::allocator<Strip_*>_>::erase
          (vector<Strip_*,std::allocator<Strip_*>_> *this,
          _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> param_1,
          _Vector_const_iterator<Strip_*,std::allocator<Strip_*>_> param_2)

{
  Strip **ppSVar1;
  int iVar2;
  Strip **extraout_EDX;
  Strip **_Dst;
  _Vector_iterator<Strip_*,std::allocator<Strip_*>_> _Var3;
  Strip **in_stack_00000014;
  
  *(undefined4 *)param_1._padding_ = 0;
  if (((this == (vector<Strip_*,std::allocator<Strip_*>_> *)0x0) ||
      ((uint)param_2._padding_ < this->_Myfirst)) || (this->_Mylast < (uint)param_2._padding_)) {
    _invalid_parameter_noinfo();
  }
  *(int *)param_1._padding_ = this->_padding_;
  *(int *)(param_1._padding_ + 4) = param_2._padding_;
  if ((in_stack_00000014 < this->_Myfirst) || (this->_Mylast < in_stack_00000014)) {
    _invalid_parameter_noinfo();
  }
  if ((*(int *)param_1._padding_ == 0) || (*(int *)param_1._padding_ != this->_padding_)) {
    _invalid_parameter_noinfo();
  }
  _Dst = *(Strip ***)(param_1._padding_ + 4);
  if (_Dst != in_stack_00000014) {
    iVar2 = (int)this->_Mylast - (int)in_stack_00000014 >> 2;
    ppSVar1 = _Dst + iVar2;
    if (0 < iVar2) {
      memmove_s(_Dst,iVar2 * 4,in_stack_00000014,iVar2 * 4);
      _Dst = extraout_EDX;
    }
    this->_Mylast = ppSVar1;
  }
  _Var3._4_4_ = _Dst;
  _Var3._0_4_ = param_1._padding_;
  return _Var3;
}
