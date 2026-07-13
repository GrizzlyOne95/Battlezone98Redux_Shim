/*
 * Entry: 004a80f2
 * Name: std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::_Checked_iterator_assign_from_base
 * Namespace: std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>
 * Signature: void _Checked_iterator_assign_from_base(_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> * this, PowerPlant * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::
_Checked_iterator_assign_from_base
          (_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> *this,PowerPlant **param_1)

{
  *(PowerPlant ***)&this->field_0x4 = param_1;
  return;
}
