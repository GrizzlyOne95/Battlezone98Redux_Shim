/*
 * Entry: 0049ad33
 * Name: std::vector<Geizer_*,std::allocator<Geizer_*>_>::erase
 * Namespace: std::vector<Geizer_*,std::allocator<Geizer_*>_>
 * Signature: _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> erase(vector<Geizer_*,std::allocator<Geizer_*>_> * this, _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> param_1, _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> __thiscall
std::vector<Geizer_*,std::allocator<Geizer_*>_>::erase
          (vector<Geizer_*,std::allocator<Geizer_*>_> *this,
          _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> param_1,
          _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> param_2)

{
  bool bVar1;
  Geizer **ppGVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar3;
  _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> _Var4;
  Geizer **in_stack_00000014;
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Myptr = (Geizer **)this;
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
            ((_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> *)param_1._padding_,
             (Geizer **)param_2._padding_,(_Container_base_aux *)this);
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
            (&local_c,in_stack_00000014,(_Container_base_aux *)this);
  bVar1 = _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator==
                    ((_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> *)param_1._padding_
                     ,&local_c);
  uVar3 = extraout_EDX;
  if (!bVar1) {
    ppGVar2 = stdext::unchecked_copy<Geizer_*_*,Geizer_*_*>
                        (local_c._Myptr,this->_Mylast,*(Geizer ***)(param_1._padding_ + 4));
    this->_Mylast = ppGVar2;
    uVar3 = extraout_EDX_00;
  }
  _Var4._4_4_ = uVar3;
  _Var4._0_4_ = param_1._padding_;
  return _Var4;
}
