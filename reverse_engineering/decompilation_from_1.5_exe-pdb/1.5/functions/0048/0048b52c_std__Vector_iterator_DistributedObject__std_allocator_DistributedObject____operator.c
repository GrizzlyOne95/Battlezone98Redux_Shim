/*
 * Entry: 0048b52c
 * Name: std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::operator+=
 * Namespace: std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> * operator+=(_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> * __thiscall
std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::operator+=
          (_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> *this,
          int param_1)

{
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::operator+=
            ((_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> *)
             this,param_1);
  return this;
}
