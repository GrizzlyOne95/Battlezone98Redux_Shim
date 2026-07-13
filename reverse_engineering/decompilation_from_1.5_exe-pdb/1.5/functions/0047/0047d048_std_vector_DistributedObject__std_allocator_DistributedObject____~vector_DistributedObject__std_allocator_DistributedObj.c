/*
 * Entry: 0047d048
 * Name: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::~vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Namespace: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: void ~vector<DistributedObject_*,std::allocator<DistributedObject_*>_>(vector<DistributedObject_*,std::allocator<DistributedObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::
~vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
          (vector<DistributedObject_*,std::allocator<DistributedObject_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
