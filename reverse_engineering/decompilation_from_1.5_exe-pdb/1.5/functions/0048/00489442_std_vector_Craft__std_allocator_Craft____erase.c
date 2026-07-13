/*
 * Entry: 00489442
 * Name: std::vector<Craft_*,std::allocator<Craft_*>_>::erase
 * Namespace: std::vector<Craft_*,std::allocator<Craft_*>_>
 * Signature: _Vector_iterator<Craft_*,std::allocator<Craft_*>_> erase(vector<Craft_*,std::allocator<Craft_*>_> * this, _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> param_1, _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Craft_*,std::allocator<Craft_*>_> __thiscall
std::vector<Craft_*,std::allocator<Craft_*>_>::erase
          (vector<Craft_*,std::allocator<Craft_*>_> *this,
          _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> param_1,
          _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> param_2)

{
  bool bVar1;
  Craft **ppCVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar3;
  _Vector_iterator<Craft_*,std::allocator<Craft_*>_> _Var4;
  Craft **in_stack_00000014;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Myptr = (Craft **)this;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            ((_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> *)param_1._padding_,
             (Craft **)param_2._padding_,(_Container_base_aux *)this);
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            (&local_c,in_stack_00000014,(_Container_base_aux *)this);
  bVar1 = _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                    ((_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> *)param_1._padding_,
                     &local_c);
  uVar3 = extraout_EDX;
  if (!bVar1) {
    ppCVar2 = stdext::unchecked_copy<Craft_*_*,Craft_*_*>
                        (local_c._Myptr,this->_Mylast,*(Craft ***)(param_1._padding_ + 4));
    this->_Mylast = ppCVar2;
    uVar3 = extraout_EDX_00;
  }
  _Var4._4_4_ = uVar3;
  _Var4._0_4_ = param_1._padding_;
  return _Var4;
}
