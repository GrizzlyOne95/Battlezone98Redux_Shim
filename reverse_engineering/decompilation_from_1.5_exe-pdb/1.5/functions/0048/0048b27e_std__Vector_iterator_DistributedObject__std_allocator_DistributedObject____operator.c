/*
 * Entry: 0048b27e
 * Name: std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::operator++
 * Namespace: std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> * operator++(_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> * __thiscall
std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::operator++
          (_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> *this)

{
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::operator++
            ((_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> *)
             this);
  return this;
}
