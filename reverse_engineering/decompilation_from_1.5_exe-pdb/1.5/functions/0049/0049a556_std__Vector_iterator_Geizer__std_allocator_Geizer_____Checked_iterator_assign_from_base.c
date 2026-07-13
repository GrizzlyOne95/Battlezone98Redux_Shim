/*
 * Entry: 0049a556
 * Name: std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>::_Checked_iterator_assign_from_base
 * Namespace: std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>
 * Signature: void _Checked_iterator_assign_from_base(_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> * this, Geizer * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>::_Checked_iterator_assign_from_base
          (_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> *this,Geizer **param_1)

{
  *(Geizer ***)&this->field_0x4 = param_1;
  return;
}
