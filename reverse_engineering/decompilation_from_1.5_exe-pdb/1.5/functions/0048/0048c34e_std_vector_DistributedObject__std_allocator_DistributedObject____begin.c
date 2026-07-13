/*
 * Entry: 0048c34e
 * Name: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::begin
 * Namespace: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> begin(vector<DistributedObject_*,std::allocator<DistributedObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> __thiscall
std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::begin
          (vector<DistributedObject_*,std::allocator<DistributedObject_*>_> *this)

{
  undefined4 extraout_EDX;
  _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> _Var1;
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
  *in_stack_00000004;
  
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
            (in_stack_00000004,this->_Myfirst,(_Container_base_aux *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = in_stack_00000004;
  return _Var1;
}
