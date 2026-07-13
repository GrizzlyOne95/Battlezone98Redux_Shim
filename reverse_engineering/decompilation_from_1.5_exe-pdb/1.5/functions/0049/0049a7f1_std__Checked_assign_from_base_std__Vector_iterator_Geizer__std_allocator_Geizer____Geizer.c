/*
 * Entry: 0049a7f1
 * Name: std::_Checked_assign_from_base<std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>,Geizer_*_*>
 * Namespace: std
 * Signature: void _Checked_assign_from_base<std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>,Geizer_*_*>(_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> * param_1, Geizer * * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Checked_assign_from_base<std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>,Geizer_*_*>
          (_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> *param_1,Geizer ***param_2)

{
  *(Geizer ***)&param_1->field_0x4 = *param_2;
  return;
}
