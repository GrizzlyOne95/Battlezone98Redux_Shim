/*
 * Entry: 0048aefb
 * Name: std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::_Checked_iterator_assign_from_base
 * Namespace: std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: void _Checked_iterator_assign_from_base(_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> * this, DistributedObject * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
_Checked_iterator_assign_from_base
          (_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> *this,
          DistributedObject **param_1)

{
  *(DistributedObject ***)&this->field_0x4 = param_1;
  return;
}
