/*
 * Entry: 00496b91
 * Name: std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>::_Checked_iterator_assign_from_base
 * Namespace: std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: void _Checked_iterator_assign_from_base(_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> * this, GameObject * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>::
_Checked_iterator_assign_from_base
          (_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> *this,GameObject **param_1)

{
  *(GameObject ***)&this->field_0x4 = param_1;
  return;
}
