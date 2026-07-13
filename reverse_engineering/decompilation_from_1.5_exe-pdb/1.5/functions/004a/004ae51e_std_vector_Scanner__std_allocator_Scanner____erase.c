/*
 * Entry: 004ae51e
 * Name: std::vector<Scanner_*,std::allocator<Scanner_*>_>::erase
 * Namespace: std::vector<Scanner_*,std::allocator<Scanner_*>_>
 * Signature: _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> erase(vector<Scanner_*,std::allocator<Scanner_*>_> * this, _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> param_1, _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> __thiscall
std::vector<Scanner_*,std::allocator<Scanner_*>_>::erase
          (vector<Scanner_*,std::allocator<Scanner_*>_> *this,
          _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> param_1,
          _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> param_2)

{
  bool bVar1;
  Scanner **ppSVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar3;
  _Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> _Var4;
  Scanner **in_stack_00000014;
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Myptr = (Scanner **)this;
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>::
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>
            ((_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> *)param_1._padding_,
             (Scanner **)param_2._padding_,(_Container_base_aux *)this);
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>::
  _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>
            (&local_c,in_stack_00000014,(_Container_base_aux *)this);
  bVar1 = _Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_>::operator==
                    ((_Vector_const_iterator<Scanner_*,std::allocator<Scanner_*>_> *)
                     param_1._padding_,&local_c);
  uVar3 = extraout_EDX;
  if (!bVar1) {
    ppSVar2 = stdext::unchecked_copy<Scanner_*_*,Scanner_*_*>
                        (local_c._Myptr,this->_Mylast,*(Scanner ***)(param_1._padding_ + 4));
    this->_Mylast = ppSVar2;
    uVar3 = extraout_EDX_00;
  }
  _Var4._4_4_ = uVar3;
  _Var4._0_4_ = param_1._padding_;
  return _Var4;
}
