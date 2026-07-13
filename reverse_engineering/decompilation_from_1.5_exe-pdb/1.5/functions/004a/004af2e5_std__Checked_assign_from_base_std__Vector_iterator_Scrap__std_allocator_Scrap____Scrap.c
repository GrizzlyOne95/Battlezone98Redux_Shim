/*
 * Entry: 004af2e5
 * Name: std::_Checked_assign_from_base<std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,Scrap_*_*>
 * Namespace: std
 * Signature: void _Checked_assign_from_base<std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,Scrap_*_*>(_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> * param_1, Scrap * * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Checked_assign_from_base<std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,Scrap_*_*>
          (_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> *param_1,Scrap ***param_2)

{
  *(Scrap ***)&param_1->field_0x4 = *param_2;
  return;
}
