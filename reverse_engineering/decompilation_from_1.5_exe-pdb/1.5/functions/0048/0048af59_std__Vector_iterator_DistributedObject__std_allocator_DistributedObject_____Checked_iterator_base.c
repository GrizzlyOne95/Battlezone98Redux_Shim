/*
 * Entry: 0048af59
 * Name: std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::_Checked_iterator_base
 * Namespace: std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: DistributedObject * * _Checked_iterator_base(_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DistributedObject ** __thiscall
std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
_Checked_iterator_base
          (_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> *this)

{
  return *(DistributedObject ***)&this->field_0x4;
}
