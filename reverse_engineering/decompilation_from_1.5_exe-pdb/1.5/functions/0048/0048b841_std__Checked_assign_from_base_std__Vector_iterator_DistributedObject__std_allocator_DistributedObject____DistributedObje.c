/*
 * Entry: 0048b841
 * Name: std::_Checked_assign_from_base<std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,DistributedObject_*_*>
 * Namespace: std
 * Signature: void _Checked_assign_from_base<std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,DistributedObject_*_*>(_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> * param_1, DistributedObject * * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Checked_assign_from_base<std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,DistributedObject_*_*>
          (_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> *param_1,
          DistributedObject ***param_2)

{
  *(DistributedObject ***)&param_1->field_0x4 = *param_2;
  return;
}
