/*
 * Entry: 0048d3fc
 * Name: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::reserve
 * Namespace: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: void reserve(vector<DistributedObject_*,std::allocator<DistributedObject_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::reserve
          (vector<DistributedObject_*,std::allocator<DistributedObject_*>_> *this,uint param_1)

{
  DistributedObject **ppDVar1;
  DistributedObject **ppDVar2;
  _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> _Var3;
  _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> _Var4;
  uint uVar5;
  DistributedObject **ppDVar6;
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> local_14;
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> local_c;
  
  if (param_1 < 0x40000000) {
    uVar5 = capacity(this);
    if (uVar5 < param_1) {
      ppDVar6 = _Allocate<DistributedObject_*>(param_1,(DistributedObject **)0x0);
      _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
      _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
                (&local_c,this->_Mylast,(_Container_base_aux *)this);
      _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
      _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
                (&local_14,this->_Myfirst,(_Container_base_aux *)this);
      _Var3._4_4_ = local_14._Myptr;
      _Var3._0_4_ = local_14._padding_;
      _Var4._4_4_ = local_c._Myptr;
      _Var4._0_4_ = local_c._padding_;
      _Umove<std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>_>
                (this,_Var3,_Var4,ppDVar6);
      ppDVar1 = this->_Myfirst;
      ppDVar2 = this->_Mylast;
      if (ppDVar1 != (DistributedObject **)0x0) {
        operator_delete(ppDVar1);
      }
      this->_Myend = ppDVar6 + param_1;
      this->_Myfirst = ppDVar6;
      this->_Mylast = ppDVar6 + ((int)ppDVar2 - (int)ppDVar1 >> 2);
    }
  }
  else {
    _Xlen();
  }
  return;
}
