/*
 * Entry: 0049771c
 * Name: std::_Checked_base<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,std::_Different_checked_iterator_base_type_tag>
 * Namespace: std
 * Signature: GameObject * * _Checked_base<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,std::_Different_checked_iterator_base_type_tag>(_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> * param_1, _Different_checked_iterator_base_type_tag param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __cdecl
std::
_Checked_base<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,std::_Different_checked_iterator_base_type_tag>
          (_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> *param_1,
          _Different_checked_iterator_base_type_tag param_2)

{
  return *(GameObject ***)&param_1->field_0x4;
}
