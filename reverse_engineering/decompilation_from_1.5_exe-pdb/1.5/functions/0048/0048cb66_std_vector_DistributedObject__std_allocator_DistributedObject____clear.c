/*
 * Entry: 0048cb66
 * Name: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::clear
 * Namespace: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: void clear(vector<DistributedObject_*,std::allocator<DistributedObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::clear
          (vector<DistributedObject_*,std::allocator<DistributedObject_*>_> *this)

{
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> _Var1;
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> _Var2;
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> local_14;
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> local_c;
  
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
            (&local_c,this->_Mylast,(_Container_base_aux *)this);
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
            (&local_14,this->_Myfirst,(_Container_base_aux *)this);
  _Var1._Myptr = (DistributedObject **)local_14._padding_;
  _Var1._padding_ = (int)&local_14;
  _Var2._Myptr = (DistributedObject **)local_c._padding_;
  _Var2._padding_ = (int)local_14._Myptr;
  erase(this,_Var1,_Var2);
  return;
}
