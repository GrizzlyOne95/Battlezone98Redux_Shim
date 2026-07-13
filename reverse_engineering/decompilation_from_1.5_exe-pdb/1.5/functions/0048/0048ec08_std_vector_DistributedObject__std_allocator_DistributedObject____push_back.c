/*
 * Entry: 0048ec08
 * Name: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::push_back
 * Namespace: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: void push_back(vector<DistributedObject_*,std::allocator<DistributedObject_*>_> * this, DistributedObject * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::push_back
          (vector<DistributedObject_*,std::allocator<DistributedObject_*>_> *this,
          DistributedObject **param_1)

{
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> _Var1;
  uint uVar2;
  DistributedObject **ppDVar3;
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> local_c;
  
  ppDVar3 = this->_Mylast;
  local_c._padding_ = (int)this;
  local_c._Myptr = (DistributedObject **)this;
  uVar2 = capacity(this);
  if ((uint)((int)ppDVar3 - (int)this->_Myfirst >> 2) < uVar2) {
    ppDVar3 = _Ufill(this,ppDVar3,1,param_1);
    this->_Mylast = ppDVar3;
  }
  else {
    _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
    _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
              (&local_c,ppDVar3,(_Container_base_aux *)this);
    _Var1._Myptr = (DistributedObject **)local_c._padding_;
    _Var1._padding_ = (int)&local_c;
    insert(this,_Var1,local_c._Myptr);
  }
  return;
}
