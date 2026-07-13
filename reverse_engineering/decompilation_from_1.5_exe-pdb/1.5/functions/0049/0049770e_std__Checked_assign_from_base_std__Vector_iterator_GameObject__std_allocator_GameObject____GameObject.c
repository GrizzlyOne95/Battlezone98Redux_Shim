/*
 * Entry: 0049770e
 * Name: std::_Checked_assign_from_base<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,GameObject_*_*>
 * Namespace: std
 * Signature: void _Checked_assign_from_base<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,GameObject_*_*>(_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> * param_1, GameObject * * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Checked_assign_from_base<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,GameObject_*_*>
          (_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> *param_1,
          GameObject ***param_2)

{
  *(GameObject ***)&param_1->field_0x4 = *param_2;
  return;
}
