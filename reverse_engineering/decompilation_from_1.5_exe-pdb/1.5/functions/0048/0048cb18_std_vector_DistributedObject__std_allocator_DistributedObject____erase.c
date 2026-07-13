/*
 * Entry: 0048cb18
 * Name: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::erase
 * Namespace: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> erase(vector<DistributedObject_*,std::allocator<DistributedObject_*>_> * this, _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_1, _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> __thiscall
std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::erase
          (vector<DistributedObject_*,std::allocator<DistributedObject_*>_> *this,
          _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_1,
          _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_2)

{
  bool bVar1;
  DistributedObject **ppDVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar3;
  _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> _Var4;
  DistributedObject **in_stack_00000014;
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Myptr = (DistributedObject **)this;
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
            ((_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> *)
             param_1._padding_,(DistributedObject **)param_2._padding_,(_Container_base_aux *)this);
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
            (&local_c,in_stack_00000014,(_Container_base_aux *)this);
  bVar1 = _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
          operator==((_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
                      *)param_1._padding_,&local_c);
  uVar3 = extraout_EDX;
  if (!bVar1) {
    ppDVar2 = stdext::unchecked_copy<DistributedObject_*_*,DistributedObject_*_*>
                        (local_c._Myptr,this->_Mylast,
                         *(DistributedObject ***)(param_1._padding_ + 4));
    this->_Mylast = ppDVar2;
    uVar3 = extraout_EDX_00;
  }
  _Var4._4_4_ = uVar3;
  _Var4._0_4_ = param_1._padding_;
  return _Var4;
}
