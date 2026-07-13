/*
 * Entry: 0047ca86
 * Name: std::_Vector_val<DistributedObject_*,std::allocator<DistributedObject_*>_>::~_Vector_val<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Namespace: std::_Vector_val<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: void ~_Vector_val<DistributedObject_*,std::allocator<DistributedObject_*>_>(_Vector_val<DistributedObject_*,std::allocator<DistributedObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<DistributedObject_*,std::allocator<DistributedObject_*>_>::
~_Vector_val<DistributedObject_*,std::allocator<DistributedObject_*>_>
          (_Vector_val<DistributedObject_*,std::allocator<DistributedObject_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
