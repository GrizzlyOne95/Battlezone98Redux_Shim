/*
 * Entry: 004e690d
 * Name: std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::erase
 * Namespace: std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
 * Signature: _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> erase(vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * this, _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> param_1, _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> __thiscall
std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::erase
          (vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *this,
          _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> param_1,
          _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> param_2)

{
  bool bVar1;
  SpawnPoint **ppSVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar3;
  _Vector_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> _Var4;
  SpawnPoint **in_stack_00000014;
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Myptr = (SpawnPoint **)this;
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
            ((_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)param_1._padding_
             ,(SpawnPoint **)param_2._padding_,(_Container_base_aux *)this);
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::
  _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
            (&local_c,in_stack_00000014,(_Container_base_aux *)this);
  bVar1 = _Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator==
                    ((_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)
                     param_1._padding_,&local_c);
  uVar3 = extraout_EDX;
  if (!bVar1) {
    ppSVar2 = stdext::unchecked_copy<SpawnPoint_*_*,SpawnPoint_*_*>
                        (local_c._Myptr,this->_Mylast,*(SpawnPoint ***)(param_1._padding_ + 4));
    this->_Mylast = ppSVar2;
    uVar3 = extraout_EDX_00;
  }
  _Var4._4_4_ = uVar3;
  _Var4._0_4_ = param_1._padding_;
  return _Var4;
}
