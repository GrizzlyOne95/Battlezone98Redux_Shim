/*
 * Entry: 0048909b
 * Name: std::_Checked_assign_from_base<std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>,Craft_*_*>
 * Namespace: std
 * Signature: void _Checked_assign_from_base<std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>,Craft_*_*>(_Vector_iterator<Craft_*,std::allocator<Craft_*>_> * param_1, Craft * * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Checked_assign_from_base<std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>,Craft_*_*>
          (_Vector_iterator<Craft_*,std::allocator<Craft_*>_> *param_1,Craft ***param_2)

{
  *(Craft ***)&param_1->field_0x4 = *param_2;
  return;
}
