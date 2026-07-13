/*
 * Entry: 00498285
 * Name: std::vector<GameObject_*,std::allocator<GameObject_*>_>::erase
 * Namespace: std::vector<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> erase(vector<GameObject_*,std::allocator<GameObject_*>_> * this, _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> param_1, _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> __thiscall
std::vector<GameObject_*,std::allocator<GameObject_*>_>::erase
          (vector<GameObject_*,std::allocator<GameObject_*>_> *this,
          _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> param_1,
          _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> param_2)

{
  bool bVar1;
  GameObject **ppGVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar3;
  _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> _Var4;
  GameObject **in_stack_00000014;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Myptr = (GameObject **)this;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            ((_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *)param_1._padding_
             ,(GameObject **)param_2._padding_,(_Container_base_aux *)this);
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_c,in_stack_00000014,(_Container_base_aux *)this);
  bVar1 = _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                    ((_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *)
                     param_1._padding_,&local_c);
  uVar3 = extraout_EDX;
  if (!bVar1) {
    ppGVar2 = stdext::unchecked_copy<GameObject_*_*,GameObject_*_*>
                        (local_c._Myptr,this->_Mylast,*(GameObject ***)(param_1._padding_ + 4));
    this->_Mylast = ppGVar2;
    uVar3 = extraout_EDX_00;
  }
  _Var4._4_4_ = uVar3;
  _Var4._0_4_ = param_1._padding_;
  return _Var4;
}
