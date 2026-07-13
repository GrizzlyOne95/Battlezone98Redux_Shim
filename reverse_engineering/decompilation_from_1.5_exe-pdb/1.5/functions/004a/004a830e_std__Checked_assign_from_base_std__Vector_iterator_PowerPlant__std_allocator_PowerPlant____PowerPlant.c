/*
 * Entry: 004a830e
 * Name: std::_Checked_assign_from_base<std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>,PowerPlant_*_*>
 * Namespace: std
 * Signature: void _Checked_assign_from_base<std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>,PowerPlant_*_*>(_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> * param_1, PowerPlant * * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Checked_assign_from_base<std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>,PowerPlant_*_*>
          (_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> *param_1,
          PowerPlant ***param_2)

{
  *(PowerPlant ***)&param_1->field_0x4 = *param_2;
  return;
}
