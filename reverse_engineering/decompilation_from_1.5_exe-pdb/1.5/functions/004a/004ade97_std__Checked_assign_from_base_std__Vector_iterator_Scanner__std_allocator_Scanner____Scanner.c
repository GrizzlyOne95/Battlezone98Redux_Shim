/*
 * Entry: 004ade97
 * Name: std::_Checked_assign_from_base<std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>,Scanner_*_*>
 * Namespace: std
 * Signature: void _Checked_assign_from_base<std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>,Scanner_*_*>(_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> * param_1, Scanner * * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Checked_assign_from_base<std::_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_>,Scanner_*_*>
          (_Vector_iterator<Scanner_*,std::allocator<Scanner_*>_> *param_1,Scanner ***param_2)

{
  *(Scanner ***)&param_1->field_0x4 = *param_2;
  return;
}
