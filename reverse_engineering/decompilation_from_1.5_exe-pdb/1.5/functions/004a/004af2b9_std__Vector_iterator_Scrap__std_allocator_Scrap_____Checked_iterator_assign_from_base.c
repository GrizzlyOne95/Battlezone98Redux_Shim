/*
 * Entry: 004af2b9
 * Name: std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>::_Checked_iterator_assign_from_base
 * Namespace: std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: void _Checked_iterator_assign_from_base(_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> * this, Scrap * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>::_Checked_iterator_assign_from_base
          (_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> *this,Scrap **param_1)

{
  *(Scrap ***)&this->field_0x4 = param_1;
  return;
}
